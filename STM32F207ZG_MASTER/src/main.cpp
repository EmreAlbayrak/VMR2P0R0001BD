#include <Arduino.h>
#include <EEPROM.h>
#include <HardwareSerial.h>
#include <defines.h>
#include <packagecontrol.h>
#include <motorcontrolcalculator.h>
#include <parameters.h>

EthernetUDP Udp;
HardwareSerial Serial6(PG9, PG14);

void print_ethernet(String message){
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  Udp.print(message);
  Udp.endPacket();
}
void print_all(String message){
  Serial.println(message);
  print_ethernet(message);
}
void set_parameters(uint8_t slave_ID, uint8_t parameter_ID, uint32_t parameter_value){
  set_parameters_matrix[slave_ID][parameter_ID][1] = parameter_value;
  EEPROM.put(set_parameters_matrix[slave_ID][parameter_ID][2], set_parameters_matrix[slave_ID][parameter_ID][1]);
  calculated_parameters_matrix[slave_ID][1] = speed_calculator_pulley(set_parameters_matrix[slave_ID][9][1], set_parameters_matrix[slave_ID][4][1], set_parameters_matrix[slave_ID][2][1], set_parameters_matrix[slave_ID][6][1], set_parameters_matrix[slave_ID][3][1]);
  calculated_parameters_matrix[slave_ID][2] = acceleration_calculator_pulley(calculated_parameters_matrix[slave_ID][1],set_parameters_matrix[slave_ID][9][1], set_parameters_matrix[slave_ID][4][1], set_parameters_matrix[slave_ID][6][1], set_parameters_matrix[slave_ID][3][1], set_parameters_matrix[slave_ID][7][1]);
}
void get_parameters_EEPROM(uint8_t joint_number){ 
  Serial.println("---------------------------------------------------------Service Info Start\n");
  Serial.print("Compile Date: ");
  Serial.println(compile_date);    
  for(int parameter_number = 1; parameter_number <= number_of_set_parameters; parameter_number++){
    uint8_t eeprom_address = set_parameters_matrix[joint_number][parameter_number][2];
    uint32_t parameter = EEPROM.read(eeprom_address);
    set_parameters_matrix[joint_number][parameter_number][1] = parameter;
    String serial_package = "Joint ID: " + String(joint_number) + " / Set Parameter ID: " + String(parameter_number) + " / Parameter Value: " + String(parameter);
    Serial.println(serial_package);
    print_ethernet(serial_package);
  }
  for(int parameter_number = 1; parameter_number <= number_of_calculated_parameters; parameter_number++){
    uint32_t parameter = calculated_parameters_matrix[joint_number][parameter_number];
    String serial_package = "Joint ID: " + String(joint_number) + " / Calculated Parameter ID: " + String(parameter_number) + " / Parameter Value: " + String(parameter);
    Serial.println(serial_package);
    print_ethernet(serial_package);
  }
}
void get_points_EEPROM(){
  for(uint8_t counter1 = 1; counter1 <= 99; counter1++){                                        //|
    for(uint8_t counter2 = 1; counter2 <= 2; counter2++){                                       //|
      points_matrix[counter1][counter2][1] = EEPROM.read(points_matrix[counter1][counter2][2]); //|------> update points from eeprom
    }                                                                                           //|
  }                                                                                             //|
}
void create_points_EEPROM(){
  uint16_t eeprom_address_counter = 100;                                                       //|
  for(uint8_t counter1 = 1; counter1 <= 99; counter1++){                                       //|
    for(uint8_t counter2 = 1; counter2 <= 2; counter2++){                                      //|
      points_matrix[counter1][counter2][2] = eeprom_address_counter + 4;                       //|------> eeprom address creator for points memory
    }                                                                                          //|
  }                                                                                            //|
}                                                                                              //|
void print_point(uint8_t point_ID){
  uint16_t point_x = points_matrix[point_ID][1][1];  
  uint16_t point_y = points_matrix[point_ID][2][1];
  String message = "Point ID: " + String(point_ID) + " / " + "X: " + String(point_x) + " / Y: " + String(point_y);
  print_all(message);                                                                                     
}
void package_analyser(String package_input){
  if(package_format_controller(package_input, 11)){ // Checking the package size and packe format
    if(isDigit(package_input[1])){ //Checking the command structure to analyze is the command directly going to SLAVE 
      Serial6.println(package_input);
    }
    else{
      char command_type = package_input[1];
      uint8_t slave_ID = package_input.substring(2,3).toInt();
      switch (command_type) {
        case 'S':{ // Set parameters
          uint8_t parameter_ID = package_input.substring(3,5).toInt();
          uint32_t parameter_value = package_input.substring(5,12).toInt();
          set_parameters(slave_ID, parameter_ID, parameter_value);//                                                                  
          push_set_joint(String(slave_ID),"04",String(set_parameters_matrix[slave_ID][4][1])); //Push microstep_coeff               |
          push_set_joint(String(slave_ID),"02",String(set_parameters_matrix[slave_ID][9][1])); //Push step_time_speed_min           |
          push_set_joint(String(slave_ID),"01",String(calculated_parameters_matrix[slave_ID][1])); //Push step_time_speed_steady    |-------------------> sync parameters with relevant slave
          push_set_joint(String(slave_ID),"03",String(calculated_parameters_matrix[slave_ID][2])); //Push step_count_acceleration   |
          break;
        }
        case 'M':{ // Move joint
          char motion_type = package_input[3];
          char direction_of_rotation = package_input[4]; 
          switch(motion_type){
            case 'S':{ // With step input
              uint32_t steps = package_input.substring(5,11).toInt();
              push_move_command(slave_ID, direction_of_rotation, steps);
              break;
            }
            case 'R':{ // With degree input
              uint32_t degree = package_input.substring(5,11).toInt();
              uint32_t steps = degree_to_step_conv(degree, set_parameters_matrix[slave_ID][3][1], set_parameters_matrix[slave_ID][4][1]);
              push_move_command(slave_ID, direction_of_rotation, steps);
              break;
            }
            case 'L':{ // With linear input
              uint32_t distance = package_input.substring(5,11).toInt();
              float degrees = linear_to_rotational_conv(distance, set_parameters_matrix[slave_ID][2][1]);
              uint32_t steps = degree_to_step_conv(degrees, set_parameters_matrix[slave_ID][3][1], set_parameters_matrix[slave_ID][4][1]);
              push_move_command(slave_ID, direction_of_rotation, steps);
              if(direction_of_rotation == 'P'){
                current_position_matrix[slave_ID] = current_position_matrix[slave_ID] + distance;
              } 
              else if(direction_of_rotation == 'N'){
                current_position_matrix[slave_ID] = current_position_matrix[slave_ID] - distance;
              }
              break;
            }
          }
          break;
        }
        case 'G':{ // Get feedback
          char get_type = package_input[2];
          switch(get_type){
            case 'S':{
              uint8_t get_joint_ID = package_input.substring(3,4).toInt();
              get_parameters_EEPROM(get_joint_ID);
              break;
            }
            case 'D':{
              print_all("---------------------------------------------------------Service Info Start\n");
              for(uint8_t counter = 1; counter <= 99; counter++){
                print_point(counter);
              }
              print_all("---------------------------------------------------------Service Info End\n");
              break;
            }
          }
          get_parameters_EEPROM(slave_ID);
          break;
        }
        case 'D':{ // Destination Point TODO: UPDATE README
          uint16_t point_x;
          uint16_t point_y;
          char destination_type = package_input[2];
          switch(destination_type){
            case 'P':{
              uint16_t point_ID = package_input.substring(4,7).toInt();
              point_x = points_matrix[point_ID][1][1];
              point_y = points_matrix[point_ID][2][1];
              break;
            }
            case 'I':{
              point_x = package_input.substring(2,6).toInt();
              point_y = package_input.substring(6,10).toInt();
              break;
            }
          }
          uint32_t delta_x = abs(point_x - current_position_matrix[1]);
          uint32_t delta_y = abs(point_y - current_position_matrix[2]);
          float degrees_x = linear_to_rotational_conv(delta_x, set_parameters_matrix[1][2][1]);
          float degrees_y = linear_to_rotational_conv(delta_y, set_parameters_matrix[2][2][1]);
          uint32_t steps_x = degree_to_step_conv(degrees_x, set_parameters_matrix[1][3][1], set_parameters_matrix[1][4][1]);
          uint32_t steps_y = degree_to_step_conv(degrees_y, set_parameters_matrix[2][3][1], set_parameters_matrix[2][4][1]);
          if(point_x > current_position_matrix[1]){
            push_move_command(1,'P',steps_x);
          }
          else if(point_x < current_position_matrix[1]){
            push_move_command(1,'N',steps_x);
          }
          if(point_y > current_position_matrix[2]){
            push_move_command(2,'P',steps_y);
          }
          else if(point_x < current_position_matrix[2]){
            push_move_command(2,'N',steps_y);
          }
          current_position_matrix[1] = point_x;
          current_position_matrix[2] = point_y;
          break;
        }
        case 'C':{ // IO Control
          String IO_ID = package_input.substring(3.4);
          String IO_value = package_input.substring(4,5);
          push_IO_joint(String(slave_ID), IO_ID, IO_value);
          break;
        }
        case 'P':{ // To save points to EEPROM
          uint8_t point_ID = package_input.substring(3,6).toInt();
          points_matrix[point_ID][1][1] = current_position_matrix[1];
          points_matrix[point_ID][2][1] = current_position_matrix[2];
          EEPROM.put(points_matrix[point_ID][1][2], points_matrix[point_ID][1][1]);
          EEPROM.put(points_matrix[point_ID][2][2], points_matrix[point_ID][2][1]);
          break;
        }
        case 'H':{ // Allign home command
          push_home_command(String(slave_ID));
          current_position_matrix[slave_ID] = 0;
          break;
        }
      }
    }
  }
}
void setup(){
  Serial.begin(115200);
  Serial6.begin(9600);
  uint16_t index = millis() % NUMBER_OF_MAC;
  char16_t package_buffer[255]; // buffer to hold incoming packet
  Ethernet.begin(mac[index], ip); // Use Static IP
  Udp.begin(localPort);
  set_parameters_matrix[1][1][2] = address_thread_distance_1;            
  set_parameters_matrix[1][2][2] = address_pulley_perimeter_1;           
  set_parameters_matrix[1][3][2] = address_motor_fullcycle_step_1;       
  set_parameters_matrix[1][4][2] = address_microstep_coeff_1;            
  set_parameters_matrix[1][6][2] = address_input_speed_steady_1;
  set_parameters_matrix[1][7][2] = address_input_acceleration_1;
  set_parameters_matrix[1][8][2] = address_driving_mechanism;
  set_parameters_matrix[1][9][2] = address_step_time_speed_min_1;
  set_parameters_matrix[2][1][2] = address_thread_distance_2;
  set_parameters_matrix[2][2][2] = address_pulley_perimeter_2;
  set_parameters_matrix[2][3][2] = address_motor_fullcycle_step_2;
  set_parameters_matrix[2][4][2] = address_microstep_coeff_2;
  set_parameters_matrix[2][6][2] = address_input_speed_steady_2;
  set_parameters_matrix[2][7][2] = address_input_acceleration_2;
  set_parameters_matrix[2][8][2] = address_driving_mechanism;
  set_parameters_matrix[2][9][2] = address_step_time_speed_min_2;
  create_points_EEPROM;
  get_points_EEPROM();
  for(uint8_t counter = 1; counter <= number_of_joints; counter++){ //|
    get_parameters_EEPROM(counter);                                 //|---------> update paramters from EEPROM
  }                                                                 //|        
}
void loop(){
  int package_size = Udp.parsePacket();
  if(package_size){
    int len = Udp.read(package_buffer, 255);
    if(len>0){
      package_buffer[len] = 0;
    }
    package_analyser(package_buffer);
  }
  if(Serial.available() > 0){
    String serial_package = Serial.readString();
    package_analyser(serial_package);
  }
  if(Serial6.available() > 0){
    String slave_feedback_package = Serial6.readString();
    print_all(slave_feedback_package);
  }
}
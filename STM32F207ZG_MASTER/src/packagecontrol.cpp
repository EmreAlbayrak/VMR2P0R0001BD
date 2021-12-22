#include <packagecontrol.h>

bool package_format_controller(String package, uint8_t package_length){
    uint32_t package_length_calculated = package.length();
    if(package_length_calculated = package_length && package[0] == '>'){
        return true;
    }
    return false;
}
String zero_padding_string(String command_value, uint8_t expacted_digit_number){
    uint8_t number_of_zeros = expacted_digit_number - command_value.length();
    for(uint8_t counter = 0; counter < number_of_zeros; counter++){
        command_value = "0" + command_value;
    }
    return command_value;
}
void push_set_joint(String slave_ID, String parameter_ID, String parameter_value){
    parameter_value = zero_padding_string(parameter_value, 6);
    String command = ">" + slave_ID + "S" + parameter_ID + parameter_value;
    Serial6.println(command);
    delay(1);
}
void push_move_joint(String slave_ID, String direction_of_rotation, String command_value){
    command_value = zero_padding_string(command_value, 7);
    String command = ">" + slave_ID + "M" + direction_of_rotation + command_value;
    Serial6.println(command);
}
void push_IO_joint(String slave_ID, String IO_ID, String IO_value){
    String package = ">" + slave_ID + "C" + IO_ID + IO_value + "NNNNNN";
    Serial6.println(package);
}
void push_home_command(String slave_ID){
    String command = ">" + slave_ID + "H" + "NNNNNNNN";
    Serial6.println(command);
}
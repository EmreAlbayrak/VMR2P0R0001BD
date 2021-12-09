#include "packagecontrol.h"
#include <Arduino.h>

void package_address_control(){

}
char package_length_control(String package, uint8_t expected_package_length){
    uint8_t length_of_package = package.length(); 
    if(length_of_package = expected_package_length){
        return 'T';
    }
    else{
        return 'F';
    }
}
void send_error_feedback(String slave_ID, String error_type, String feedback_ID){
    String feedback_package = ">" + slave_ID + "E" + error_type + feedback_ID; //String concatenation
    Serial.println(feedback_package);
}
void send_confirm_feedback(String slave_ID, String confirm_type, String feedback_ID){
    String feedback_package = ">" + slave_ID + "F" + confirm_type + feedback_ID; //String concatenation
    Serial.println(feedback_package);
}
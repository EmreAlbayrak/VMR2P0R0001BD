#include <packagecontrol.h>
#include <Arduino.h>

bool package_size_controller(String package, uint8_t package_length){
    uint32_t package_length_calculated = package.length();
    if(package_length_calculated = package_length){
        return true;
    }
}
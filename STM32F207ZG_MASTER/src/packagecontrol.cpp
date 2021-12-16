#include <packagecontrol.h>

bool package_format_controller(String package, uint8_t package_length){
    uint32_t package_length_calculated = package.length();
    if(package_length_calculated = package_length && package[0] == '>'){
        return true;
    }
    return false;
}
void sync_parameters(uint8_t slave_ID, uint8_t parameter_value){

}
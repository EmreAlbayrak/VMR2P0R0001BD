#include <Arduino.h>
const char compile_date[] = __DATE__ " " __TIME__; 

void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Compile Date: ");
  Serial.println(compile_date);
  delay(1000);
}
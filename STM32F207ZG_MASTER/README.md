# **Visiomex VMR2P0R0001BD-MASTER Documentation**

*Visiomex Industrial Image Processing Solutions Inc. 2021*

*This project is in development process. Some parts of the code migth not work as expected.*   

# Protocol Information

## 1. UART Communication 

The system has an option to communicate over UART protocol, 115200 baud rate, 8-bit, no handshake.

The current verion tested on ST Nucleo STM32F207ZG Board With on-board ST-Link V2 UART Converter.
Driver requred to communicate over on-board ST-Link V2 UART converter.

Driver could be found at: *https://www.st.com/en/development-tools/stsw-link009.html*

## 2. Ethernet Socket Communication

The system has another option to communicate over Ethernet UDP messaging on port 1883. The pre-defined IP address of the system is "192.168.0.2" where it can be set in the file "defines.h", line 179.

# Package Structures

## 1. Commands (Computer to MASTER)

### 1.1. Set Commands (Computer to MASTER):

In set commands, the package starts with standart package beginning digit ">" and the following digit is the command type ("S" for set commands). Second digit is the slave ID to set the parameters for the relevant joint (DOF). The third digit and fourt digits indicates the parameter ID. The parameter value starts from digit five and takes following 6 digit. The package size is standart and it is 11 digits for all commands from comnputer to MASTER device.

**Example Package: >SNXX######**

*List of set parameters and IDs:*

| Example Slave ID | Parameter ID | Parameter Name | Parameter Unit | Example Package | Parameter Type | Usage |
| ---------------- | ---------- | -------------- | -------------- | --------------- | -------------- | ----- |
| 1 | 01 | thread_distance | *mm* | *15mm Thread Distance:* >S101000015 | Input | Service |
| 1 | 02 | pulley_perimeter | *mm* | *120mm perimeter:* >S102000120 | Input |Service |
| 1 | 03 | motor_fullcycle_step | *# of steps* | *400 Steps per cycle:* >S103000400 | Input | Service |
| 1 | 04 | microstep_coeff | *Coeff* | *1/32 microstep:* >S104000032 | Input | Service |
| 1 | 05 | max_speed | *mm/s* | *10 (mm/s):* >S105000010 | Input | Service |
| 1 | 06 | input_speed_steady | *mm/s* | *100 mm/s:* >S106000100 | Input | Service |
| 1 | 07 | input_acceleration | *mm/s^2* | *50 mm/s^2:* >S107000050 | Input | Service |
| 1 | 08 | driving_mechanism | 0 -> Pulley, 1 -> Lead Screw | *Pulley System:* >S108000000 | Input | Service |
| 1 | 09 | step_time_speed_min | *microseconds* | *400 us:* >S109000400 | Input | Test* |
| 1 | 10 | step_time_speed_steady | *microseconds* | *4000 us:* >S110004000 | Calculated | Test |
| 1 | 11 | step_time_instantaneous | *microseconds* | *1000 us:* >S111001000 | Calculated | Test |
| 1 | 12 | step_time_acceleration_avg | *microseconds* | *500 us:* >S112000500 | Calculated | Test |
| 1 | 13 | step_count_acceleration | *# of steps* | *400 Steps:* >S113000400 | Calculated | Test |
| 1 | 14 | delta_t | *seconds* | *2 s:* >S114000002 | Calculated | Test |

### 1.2. Move Commands (Computer to MASTER)

The move commands packages starts with standart package beginning symbol ">" and the next digit is the command type ("M" for move commands). Second digit is the slave ID to send the move command to relevent joint (DOF). The third digit is the motion type. The MASTER device can take three different motion type input where they are "R" for rotational inputs in units of degrees, "S" Number of steps to turn and "L" for linear distance input in units of millimeters. The fourth digit is *"direction of motion"* where it can take "P" for positive and "N" for negative directions. From digit five to ten (last 6 digits) are the delta motion. Fixed package size: 11 element string.

**Example Package: >MNTD######**

*Example Move Command:*

**>M1LP000382** -> *382mm positive direction on x-axis*

**>M1RN000360** -> *360 degrees counter clockwise on x-axis*

**>M1SP000400** -> *400 steps clockwise on x-axis*

***Note:** "P" Positive direction of motion means clockwise (CW), "N" Negative direction of motion means counter clockwise (CCW) on rotational inputs.*

### 1.3. IO Commands (Computer to MASTER)

As the other commands, the package starts with ">" symbol and fist digit is the "C" for IO control command type. The second digit is the slave ID (Joint ID / DOF ID). The following digit indicates the IO ID and fourth digit keeps the IO value. Following six digits are Null digits to match the package size for a standard package procedure.

**Example Package: >C1M0NNNNNN** -> *Set the "Motor Enable IO" to "0 / LOW"*

### 1.4. Save Point Command (Computer to MASTER)

The "Save Point" command package starts with ">" and it continues with "P" as a command type. The second element is the "C" for current position. Digit number three to six (following 3 digits) are point ID to save. In the current version point ID 000 is the home position.

**Example Package: >PC###NNNNN**

### 1.5. Destination Command (Computer to MASTER)

There are two types of "Destination" command available in current version according to the destination type and it indicated in the second digit of the string. For a pre-defined / saved destination, the second element should be "P" and the following three element contains the Point ID. For coordinat destination inputs, the second digit of the string should be "I". In coordinat inputs, digit number three to seven (4 digits) contains x-axis point and last four digits contains y-axis points as a destination.

**Example Package: >DP003NNNNN** -> *Go to destination point number 003.*
**Example Package: >DIXXXXYYYY** -> *Go to destination point input XXXX,YYYY coordinates in units of millimeters*

### 1.6. Get Command (Computer to MASTER)

According to standard package structure, Get Commands starts with ">" symbol and continues with "G" letter. There are two type of Get Commands available in the system where they are "Get Parameters" "S" and "Get Point Data" "D" and indicated in the second digit of the string.

**Example Package: >GS#NNNNNNN** -> *Get #'th Joint parameters*

**Example Package: >GD###NNNNN** -> *Get Point ID ### values*

### 1.7. Transparent Commands (Computer to MASTER to SLAVE)

Transparent commands are aimed to send commands directly to the SLAVE devices. When a SLAVE command (available in VMR2P0R0001BD-SLAVE Documentation) comes from computer side to MASTER device, MASTER directly forwards the package to relevant SLAVE. 

## 2. Feedbacks (MASTER to Computer) 
*Not activated in current version*
Every feedback package starts with ">" character as an indicator. Computer software should just tooks the feedback packages starting with ">" character (FeedbackString[0]). MCU sends different kind of informations as a feedback (calculation results, status information etc.) for service monitoring. Computer software should only took the packages starting with ">" to avoid problems.

*Full list of feedback packages:*

| Example Slave ID | Feedback Type | Relevant Command | Example Feedback | Description |
| ---------------- | ------------- | ---------------- | ---------------- | ----------- |
| 1 | Confirm | Set Command | >F1S01 | thread_distance succesfully set |
| 1 | Confirm | Set Command | >F1S02 | pulley_diameter succesfully set |
| 1 | Confirm | Set Command | >F1S03 | motor_fullcycle_step succesfully set |
| 1 | Confirm | Set Command | >F1S04 | input_microstep_coeff succesfully set |
| 1 | Confirm | Set Command | >F1S05 | max_speed succesfully set |
| 1 | Confirm | Set Command | >F1S06 | input_speed_steady succesfully set |
| 1 | Confirm | Set Command | >F1S07 | input_acceleration succesfully set |
| 1 | Confirm | Set Command | >F1S08 | driving_mechanism succesfully set |
| 1 | Confirm | Set Command | >F1S09 | step_time_speed_min succesfully set |
| 1 | Confirm | Move Command | >F1M01 | Move Linear command confirmed |
| 1 | Confirm | Move Command | >F1M02 | Move Rotational command confirmed |
| 1 | Confirm | Move Command | >F1M03 | Move Steps command confirmed |
| 1 | Confirm | IO Command | >F1C01 | IO Control command confirmed |
| 1 | Confirm | IO Command | >F1C00 | Motor power on command confirmed | 
| 1 | Confirm | IO Command | >F1C00 | Motor power off command confirmed | 
| 1 | Confirm | Get Command | >F1G01 | Get command confirmed |
| 1 | Confirm | Home Command | >F1H01 | Home position command confirmed |
| 1 | Done | Move Action | >F1A01 | Action Accomplished |
| 1 | Error | Package - General | >E1P01 | Package length mismatch |
| 1 | Error | Package - General | >E1P02 | Invalid command type |
| 1 | Error | Package - Move Command | >E1P03 | Invalid direction of rotation |
| 1 | Error | Package - Set Command | >E1P04 | Invalid parameter ID |
| 1 | Error | Package - IO Command | >E1P05 | Invalid IO ID | 

# EEPROM Adress List of Parameters

Some parameters are available to set from user, and those parameters requires to store in the EEPROM to enable to use them after reset.

*List of EEPROM adresses*

| Parameter | Variable Type | EEPROM Address |
| --------- | ------------- | -------------- |
| thread_distance_x | uint16_t | 0 |
| thread_distance_y | uint16_t | 2 |
| pulley_diameter_x | float_t | 4 |
| pulley_diameter_y | float_t | 8 |
| motor_fullcycle_step_x | uint16_t | 12 |
| motor_fullcycle_step_y | uint16_t | 14 |
| microstep_coeff_x | uint8_t | 16 |
| microstep_coeff_y | uint8_t | 17 |
| input_speed_steady_x | uint16_t | 18 |
| input_speed_steady_y | uint16_t | 20 |
| input_acceleration_x | uint8_t | 22 |
| input_acceleration_y | uint8_t | 23 |
| driving_mechanism | char16_t | 24 |
| step_delay_speed_min_x | uint32_t | 26 |
| step_delay_speed_min_y | uint32_t | 30 |
# **Visiomex VMR2P0R0001BD Motor Controller (Slave) Documentation**

*Visiomex Industrial Image Processing Solutions Inc. 2021*

*This project is ın development process. Some parts and functions might not work as expected*.

# Protocol Information

The current version of the system uses RS485 communication protocol for "in robot communication". There are one controller device (STM32F207ZG) where it acts like bridge between computer and robotic system and it makes the relevant calculations and sequences the tasks in the system. The STM32F207ZG device is the "Master Device" and sends the "Slave Devices" relevant commands and paramters. The other modules (Motor Drivers, Sensor Modules etc.) are Slaves parts of the system where they structured on STM32F103C8 board. 

From hardware side, each slave devices connected to UART-RS485 converter. ( STM32F103C8 (SLAVE) -> Serial (UART) -> UART-RS485 Converter -> RS485 -> MASTER / SLAVE(S) / ... ).

This document focuces on the "Slave Device" structure of the system. 

- >MASTER IC: STM32F207ZG (current version)
- >SLAVE(S) IC: STM32F103C8 (current version)
- >Communication Protocol: RS485 (with UART-RS485 converter)

# Package Structures

Slave devices listens the serial port in a loop to catch the packages coming from MASTER device. There are different type of command / feedback packages available in the system. From structure perspective, each package starts with angle bracket symbol ">" where both MASTER and SLAVE devices accepts the packages starting with it.

## 1. Commands (MASTER to SLAVE)

### 1.1. Set Commands (MASTER to SLAVE):

Slave device requires some parameters to accomlish the the given task where they comes from Master. After the standard beggining of the commands (zeroth element of the string arr[0]), first element of the string is slave number where it is represented with "A" in the example structure (arr[1]). The second digit is an indicator of the command type where it is "S" in the set comands (arr[2]). The next two digits are parameter ID (arr[3] to arr[4]) where it is represented "CC" in the example structure below. The continues 6 digits (arr[5] to arr[10]) are parameter value represented with "######" in the following example. 

***Example:***

- >**Command Structure:** ">ABCC######"

- >**Size of Command:** 11 elements char array (string, including ">" symbol)

***Full List of Set Commands***

| Example Slave ID | Parameter ID | Parameter Name | Parameter Unit | Example Package | Expacted Confirm Feedback from Slave |
| ---------------- | ---------- | -------------- | -------------- | --------------- | ------------------------------------ |
| 1 | 01 | input_step_time_speed_steady | *microseconds* | *3000 microseconds:* >1S01003000 | >1FS01 |
| 1 | 02 | input_step_time_speed_min | *microseconds* | *9500 microseconds:* >1S02009500 | >1FS02 |
| 1 | 03 | input_step_count_acceleration | *# of steps* | *300 steps:* >1S03000300 | >1FS03 |
| 1 | 04 | input_microstep_coeff | *Coeff* | *1/4 microsteps:* >1S04000004 | >1FS04 |

### 1.2. Move Commands (MASTER to SLAVE):

As mentioned in the general command structure info, move commands starts with ">" symbol (arr[0]), the first element of the array (arr[1]) is slave ID and second element (commant type, arr[2]) is "M" where it indicates it is a Move Command. The following element of the string (arr[3]) is direction of rotation where it is represented with "C". Direction of rotation digit can get "P" for positive direction and "N" for negative directions where ositive direction is CW (clockwise) and negative direction is CCW (counter clockwise). The digits from arr[4] to arr[10] (represented by #### in example command structure) is the number of steps to move.

***Example:***

- >**Command Structure:** ">ABC#######"

- >**Size of Command:** 11 elements string (including ">" symbol)

***Example List of Move Commands***

| Example Slave ID | Move Type | Direction of Rotation | Example Package | Expacted Confirm Feedback from Slave |
| ---------------- | --------- | --------------------- | --------------- | ------------------------------------ |
| 1 | Steps | Positive | *400 steps:* >1MP0000400 | >1FM01 |
| 1 | Steps | Negative | *800 steps:* >1MN0000800 | >1FM01 |


Reminding:

- Positive: *CW*
- Negative: *CCW*

### 1.3. Enable / Disable Commands

As the other commands, The package starts with ">" symbol and Slave ID follows on the next digit. The second element (arr[2]) of the string is command type where it is "C" in Enable / Disable commands. The third element of the string (arr[3]) is the ID of the GPIO. In current version, there is only motors ID available ("M") for power up and power off the motors. The following digit (arr[4}]) is the boolean value of the pin condition ("0" or "1"). The following 6 digits are not important but the package should contain 11 digits to match the package length. 

**Enable / Disable Motors

| Example Slave ID | GPIO ID | GPIO Value | Description | Example Package | Expacted Confirm Feedback from Slave |
| ---------------- | ------- | ---------- | ----------- | --------------- | ------------------------------------ |
| 1 | M | 1 | Power on motor | >1CM1NNNNNN | >1FC01 |
| 1 | M | 0 | Power off motor | >1CM1NNNNNN | >1FC02 |


## 2. Feedback (SLAVE to MASTER) 

As mentioned in the "*Full List of Set Commands*" and "*Example List of Move Commands*", the feedback commands starts with ">" symbols and following digit indicates the Slave ID. The second element (arr[2]) of the package is indicates that it is a feedback or error package ("F" letter for feedback, "E" letter for error), third element (arr[3]) is command type to approve and could take "S" for set, "M" for move commands. The following digits (arr[4] and arr[5]) are Feedback ID.

***Example:***

- >**Command Structure:** ">ABCDD"

- >**Size of Command:** 6 elements string (including ">" symbol)

***Full List of Feedback Packages***

| Example Slave ID | Feedback Type | Relevant Command | Example Feedback | Description |
| ---------------- | ------------- | ---------------- | ---------------- | ----------- |
| 1 | Confirm | Set Command | >1FS01 | input_step_time_speed_steady succesfully set |
| 1 | Confirm | Set Command | >1FS02 | input_step_time_speed_min succesfully set |
| 1 | Confirm | Set Command | >1FS03 | input_step_count_acceleration succesfully set |
| 1 | Confirm | Set Command | >1FS04 | input_microstep_coeff succesfully set |
| 1 | Confirm | Set Command | >1FS05 | input_system_cycle_linear_coeff succesfully set |
| 1 | Confirm | Move Command | >1FM01 | Move Step Command confirmed |
| 1 | Confirm | GPIO Command | >1FC01 | Motor power on command confirmed | 
| 1 | Confirm | GPIO Command | >1FC02 | Motor power off command confirmed | 
| 1 | Done | Move Action | >1FA01 | Action Accomplished |
| 1 | Error | Package - General | >1EP01 | Package length mismatch |
| 1 | Error | Package - General | >1EP02 | Invalid command type |
| 1 | Error | Package - Move Command | >1EP03 | Invalid direction of rotation |
| 1 | Error | Package - Set Command | >1EP04 | Invalid parameter ID |


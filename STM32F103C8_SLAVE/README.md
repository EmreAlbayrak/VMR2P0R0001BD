# **Visiomex VMR2P0R0001BD Motor Controller (Slave) Documentation**

*Visiomex Industrial Image Processing Solutions Inc. 2021*
*This project is ın development process. Some parts and functions might not work as expected.

## Protocol Information

The current version of the system uses RS485 communication protocol for "in robot communication". There are one controller device (STM32F207ZG) where it acts like bridge between computer and robotic system and it makes the relevant calculations and sequences the tasks in the system. The STM32F207ZG device is the "Master Device" and sends the "Slave Devices" relevant commands and paramters. The other modules (Motor Drivers, Sensor Modules etc.) are Slaves parts of the system where they structured on STM32F103C8 board. 

From hardware side, each slave devices connected to UART-RS485 converter. ( STM32F103C8 (SLAVE) -> Serial (UART) -> UART-RS485 Converter -> RS485 -> MASTER / SLAVE(S) / ... ).

This document focuces on the "Slave Device" structure of the system. 

- >MASTER IC: STM32F207ZG (current version)
- >SLAVE(S) IC: STM32F103C8 (current version)
- >Communication Protocol: RS485 (with UART-RS485 converter)

## Package Structures

Slave devices listens the serial port in a loop to catch the packages coming from MASTER device. There are different type of command / feedback packages available in the system. From structure perspective, each package starts with angle bracket symbol ">" where both MASTER and SLAVE devices accepts the packages starting with it.



### 1. Set Commands (MASTER to SLAVE):

Slave device requires some parameters to accomlish the the given task where they comes from Master. After the standard beggining of the commands (zeroth element of the string arr[0]), first element of the string is slave number where it is represented with "A" in the example structure (arr[1]). The second digit is an indicator of the command type where it is "S" in the set comands (arr[2]). The next two digits are parameter ID (arr[3] to arr[4]) where it is represented "CC" in the example structure below. The continues 6 digits (arr[5] to arr[10]) are parameter value represented with "######" in the following example. 

***Example:***

- **Command Structure:** ">ABCC######"

- **Size of Command:** 11 elements char array (string, including ">" symbol)

Full List of set commands available in the table below.

| Package ID | Parameter Name | Paarameter Unit | Example Package | Expacted Confirm Feedback from Slave |
| ---------- | -------------- | --------------- | --------------- | ------------------------------------ |
| 01 | input_step_time_speed_steady | *microseconds* | *3000 microseconds:* >1S01003000 | >FS01 |
| 02 | input_step_time_speed_min | *microseconds* | *9500 microseconds:* >1S02009500 | >FS02 |
| 03 | input_step_count_acceleration | *# of steps* | *300 steps:* >1S03000300 | >FS03 |
| 04 | input_microstep_coeff | *Coeff* | *1/4 microsteps:* >1S04000004 | >FS04 |
| 05 | input_system_cycle_linear_coeff | *mm\*10* | *137.5mm per cycle:* >1S05001375 | >FS05 |

### 2. Move Commands (MASTER to SLAVE):


As mentioned in the general command structure info, move commands starts with ">" symbol (arr[0]), the first element of the array (arr[1]) is number of the slave and second element (commant type, arr[2]) is "M" where it indicates a Move Command. The following element of the string (arr[3]) is rotation type and it can get "R" for rotational, "L" for linear and "S" for step inputs. The next element represented in the example "D" (arr[4]) is the direction of rotation and it can get "P" for positive direction and "N" for negative direction. For rotational use, positive direction is CW (clockwise) and negative direction is CCW (counter clockwise). The digits from arr[5] to arr[8] (represented by #### in example command structure) is the input distance in units of "degrees" for rotational use, "mm" for linear use and "steps" for step inputs. The element arr[9] and arr[10] are null digits to match the package size to "11 element" to keep standard package size for all commands.


***Example:***

- **Command Structure:** ">ABCD####NN"

- **Size of Command:** 11 elements char array (string, including ">" symbol)


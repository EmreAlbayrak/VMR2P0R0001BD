# **Visiomex VMR2P0R0001BD (Master) Documentation**

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

## 1. Commands (Computer to Master)

### 1.1. Set Commands:

Where first and second element of the array ("S" is the zeroth element) is the parameter ID represented by "XX".

Continues following 6 digits are the parameter values represented by "######".

Following nine digits are null digits to match the package size expected from robot's controller.

**Example Package: SXX######NNN**   

*List of set parameters and IDs:*

| Package ID | Parameter Name | Parameter Unit | Example Package | Parameter Type | Usage |
| ---------- | -------------- | -------------- | --------------- | -------------- | ----- |
| 01 | thread_distance_x | *mm* | *15mm Thread Distance:* >S01000015NNN | Input | Service |
| 02 | thread_distance_y | *mm* | *20mm Thread Distance:* >S01000020NNN | Input |Service |
| 03 | pulley_diameter_x | *mm\*10* | *38.2mm diameter:* >S03000382NNN | Input |Service |
| 04 | pulley_diameter_y | *mm\*10* | *42.6mm diameter:* >S04000426NNN | Input |Service |
| 05 | motor_fullcycle_step_x | *# of steps* | *400 Steps per cycle:* >S05000400NNN | Input | Service |
| 06 | motor_fullcycle_step_y | *# of steps* | *200 Steps per cycle:* >S06000200NNN | Input | Service |
| 07 | microstep_coeff_x | *Coeff* | *1/32 microstep:* >S07000032NNN | Input | Service |
| 08 | microstep_coeff_y | *Coeff* | *1/16 microstep:* >S08000016NNN | Input | Service |
| 09 | max_speed_x | *mm/s* | *10 (mm/s):* >S09000010NNN | Input | Service |
| 10 | max_speed_y | *mm/s* | *20 (mm/s):* >S10000020NNN | Input | Service |
| 11 | step_delay_speed_steady_x | *microseconds* | *4000 us:* >S11004000NNN | Output | Test |
| 12 | step_delay_speed_steady_y | *microseconds* | *5000 us:* >S12005000NNN | Output | Test |
| 13 | step_delay_speed_min_x | *microseconds* | *400 us:* >S13000400NNN | Input | Service |
| 14 | step_delay_speed_min_y | *microseconds* | *500 us:* >S14000500NNN | Input | Service |
| 15 | step_delay_instantaneous_x | *microseconds* | *1000 us:* >S15001000NNN | Output | Test |
| 16 | step_delay_instantaneous_y | *microseconds* | *1300 us:* >S16001300NNN | Output | Test |
| 17 | step_delay_acceleration_avg_x | *microseconds* | *500 us:* >S17000500NNN | Output | Test |
| 18 | step_delay_acceleration_avg_y | *microseconds* | *700 us:* >S18000700NNN | Output | Test |
| 19 | step_count_acceleration_x | *# of steps* | *400 Steps:* >S19000400NNN | Output | Test |
| 20 | step_count_acceleration_y | *# of steps* | *800 Steps:* >S20000800NNN | Output | Test |
| 21 | input_speed_steady_x | *mm/s* | *100 mm/s:* >S21000100NNN | Input | Service |
| 22 | input_speed_steady_y | *mm/s* | *120 mm/s:* >S22000120NNN | Input | Service |
| 23 | input_acceleration_x | *mm/s^2* | *50 mm/s^2:* >S23000050NNN | Input | Service |
| 24 | input_acceleration_y | *mm/s^2* | *60 mm/s^2:* >S24000060NNN | Input | Service |
| 25 | delta_t_x | *seconds* | *2 s:* >S25000002NNN | Output | Test |
| 26 | delta_t_y | *seconds* | *2 s:* >S26000002NNN | Output | Test |
| 27 | driving_mechanism | 0 -> Pulley, 1 -> Lead Screw | *Pulley System:* >S27000000NNN | Input | Service |

### 1.2. Move Commands 
#### Command ID and structure:
#### Example Package: MXX####X####

Fix package size: 12 element string

Where the zeroth element of the array (array[0]) is command type ("M" for move).

The first element of the array (array[1]) is the motion input type ("L" for linear, "R" for rotational, "S" for step).

The second element of the array (array[2]) is the direction of motion on x-axis ("P" for positive, "N" for negative).

Element number three to six are delta motion on x-axis in units of millimeters for linear, degrees for rotational, steps for step inputs..

The seventh element of the array (array[7]) is the direction of montion on y-axis ("P" for positive, "N" for negative).

Element number eight to eleven are delta motion on y-axis in units of millimeters for linear, degrees for rotational, steps for step inputs.

####*Example Move Command:*

**MLP0382N0382** -> *382mm positive direction on x-axis, 382mm negative direction on y-axis.*

**MRP0360N0360** -> *360 degrees clockwise on x-axis, 360 degrees counter clockwise on y-axis.*

**MSP0400N0400** -> *400 steps clockwise on x-axis, 400 steps counter clockwise on y-axis.*

***Note:** "P" Positive direction of motion means clockwise (CW), "N" Negative direction of motion means counter clockwise (CCW) on rotational inputs.*

### 1.3. "Go To Destination" Command

In the current version, system goes to home position if it receives "D" command as a zeroth element of the array (array[0]). To fill the package to make it suitable for expacted array size (where it is 12 digits), the package should contains null characters.

####*Example:* 

**DNNNNNNNNNNN**
## 2. Feedbacks (Master to Computer)

Every feedback package starts with ">" character as an indicator. Computer software should just tooks the feedback packages starting with ">" character (FeedbackString[0]). MCU sends different kind of informations as a feedback (calculation results, status information etc.) for service monitoring. Computer software should only took the packages starting with ">" to avoid problems.

- #### Error Package Structure and IDs:
  #### Example Package: EPXXXX

	Where the zeroth element of the array (array[0]) is command type ("E" for errors).

	The first element of the array (array[1]) is the return type (P for package, F for functions).

	*List of Package Errors:*

	| Package | Description |
	| ------- | ----------- |
	| >EP0001 | Package size mismatch |
	| >EP0002 | Invalid command type (array[0] error) |
	| >EP0003 | Invalid motion type (array[1] error) |
	| >EP0004 | Invalid direction of rotation for x-axis (array[2]) |
	| >EP0005 | Invalid direction of rotation for y-axis (array[10]) |
	| >EP0006 | Invalid set parameter ID (array[1], array[2]) |

	*List of Funtion Errors:*
	| Package | Description |
	| ------- | ----------- |
	| >EF0001 | "Parse Distance" Function error |
	| >EF0002 | Invalid Driving Mechanism |
	| >EF0003 | Invalid Axis Input Function |

- #### Feedback Package Structure and IDs:
  #### Example Package: FSXXXX

	Where the zeroth element of the array (array[0]) is  the return type ("F" for feedback).

	The first element of the array (array[1]) is the feedback type ("S" for set feedback).

	Next four element of the array is the feedback ID.

	*List of Feedback Packages:*

	| Package | Description |
	| ------- | ----------- |
	| >FS0001 | threat_distance_x set done. |
	| >FS0002 | threat_distance_y set done. |
	| >FS0003 | pulley_diameter_x set done. |
	| >FS0004 | pulley_diameter_y set done. |
	| >FS0005 | motor_fullcycle_step_x set done. |
	| >FS0006 | motor_fullcycle_step_y set done. |
	| >FS0007 | microstep_coeff_x set done. |
	| >FS0008 | microstep_coeff_y set done. |
	| >FS0009 | max_speed_x set done. |
	| >FS0010 | max_speed_y set done. |
	| >FS0011 | step_delay_speed_steady_x set done. |
	| >FS0012 | step_delay_speed_steady_y set done. |
	| >FS0013 | step_delay_speed_min_x set done. |
	| >FS0014 | step_delay_speed_min_y set done. |
	| >FS0015 | step_delay_instantaneous_x set done. |
	| >FS0016 | step_delay_instantaneous_y set done. |
	| >FS0017 | step_delay_acceleration_avg_x set done. |
	| >FS0018 | step_delay_acceleration_avg_y set done. |
	| >FS0019 | step_count_acceleration_x set done. |
	| >FS0020 | step_count_acceleration_y set done. |
	| >FS0021 | input_speed_steady_x set done. |
	| >FS0022 | input_speed_steady_y set done. |
	| >FS0023 | input_acceleration_x set done. |
	| >FS0024 | input_acceleration_y set done. |
	| >FS0025 | delta_t_x set done. |
	| >FS0026 | delta_t_y set done. |
	| >FS0027 | driving_mechanism_x set done. |
	| >FS0028 | driving_mechanism_y set done. |
	| | |
	| >FP0001 | Move Command Confirmed |
	| >FP0002 | Move Home Command Confirmed |
	| | |
	| >FA0001 | Action Accomplished |

## EEPROM Adress List of Parameters

Some parameters are available to set from user, and those parameters requires to store in the EEPROM to enable to use them after reset.

*List of EEPROM adresses*

| Parameter | Variable Type | EEPROM Address |
| --------- | ------------- | ------- |
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

# Hardware Connections 

The required hardware connections had been given in the table below.

***List of pin connections between ST Nucleo STM32F303RE board and external devices:***

| External Device Name | External Device Pin Name | STM32F303RE Nucleo Pin Number |
| -------------------- | ------------------------ | ----------------------------- |
| CWD556 Motor Driver (x-axis 1) | DIR+ | D2 (PA10) |
| CWD556 Motor Driver (x-axis 1) | PUL+ | D3 (PB3) |
| CWD556 Motor Driver (x-axis 1) | ENA+ | D8 (PA9) |
| CWD556 Motor Driver (x-axis 1) | DIR- PUL- ENA- | GND |
| CWD556 Motor Driver (x-axis 2) | DIR+ | D4 (PB5) |
| CWD556 Motor Driver (x-axis 2) | PUL+ | D5 (PB4) |
| CWD556 Motor Driver (x-axis 2) | ENA+ | D9 (PA9) |
| CWD556 Motor Driver (x-axis 2) | DIR- PUL- ENA- | GND |
| CWD556 Motor Driver (y-axis) | DIR+ | D7 (PA8) |
| CWD556 Motor Driver (y-axis) | PUL+ | D6 (PB10) |
| CWD556 Motor Driver (y-axis) | ENA+ | D10 (PB6) |
| CWD556 Motor Driver (y-axis) | DIR- PUL- ENA- | GND |

***List of pin connection between motors and motor drivers:***

| Motor's Original Cable Colour | Color of Extention Cable | GX16 Socket Pin Number | Motor Driver Pin Name |
| ----------------------------- | ------------------------ | ---------------------- | --------------------- |
| RED | BROWN | 1 | A+ |
| YELLOW | SC to BLUE | NC | NC |
| BLUE | SC to YELLOW | NC | NC |
| BLACK | YELLOW | 3 | A- |
| WHITE | WHITE | 2 | B+ |
| ORANGE | SC to BROWN | NC | NC |
| BROWN | SC to ORANGE | NC | NC |
| GREEN | GREEN | 4 | B- |

*NC: Not Connected* 
*SC: Short Circuit* 

***Note:** All the connetions between motors and motor drivers are same in the device (x-axis 1, x-axis 2 and y-axis). In the current version of the product, motor drivers runs at 24V and requires at least 4 ampers power supply per driver.*
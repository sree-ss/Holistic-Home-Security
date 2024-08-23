# Holistic-Home-Security
Abstract
The project focuses on designing a comprehensive Home Security System using the ESP32 DevKit V1 microcontroller. This microcontroller serves as the central control unit, managing various integrated devices. The system includes a 16x2 LCD display, Servo Motor, PIR Sensor, Battery, Buzzer, 4x4 Keypad, and GSM module, all interfaced with the ESP32 DevKit V1 controller.

When the PIR Sensor detects motion, the system prompts the user to enter a PIN within a specified time. Failure to enter the PIN triggers the ESP32 DevKit V1 to send an alert SMS via the GSM module. If the correct PIN is entered, the system generates and sends an OTP to the user, which must be entered within a given period. Incorrect PIN or OTP entries trigger an alert notification and a warning sound from the Buzzer. If the OTP matches the generated one, the system grants access by unlocking the door. The ESP32 DevKit V1 microcontroller remains the primary control device throughout this process.

Pros
Cost-Effective: The ESP32 DevKit V1 is relatively inexpensive compared to other microcontrollers and security systems, making it a budget-friendly option.
Versatility: This microcontroller is capable of handling various tasks like sensor interfacing, communication, and control functions, making it adaptable to different security needs.
Low Power Consumption: It is power-efficient, which is beneficial for battery-powered operations or minimizing energy consumption.
Expandable: The microcontroller’s capabilities allow for future upgrades and expansion of the home security system.
Description
The system is equipped with several integrated components to ensure security and efficient operation:

PIR Sensor: Detects motion by measuring changes in infrared radiation, triggering the system to take action when movement is detected.
ESP32 DevKit V1 Controller: Orchestrates the entire system, managing inputs and outputs.
4x4 Keypad: Allows users to input a security code to activate or deactivate the system, maintaining security by restricting access to unauthorized users.
Servo Motor: Controls physical components like locking or unlocking doors or activating an alarm in response to sensor input.
One-Time Password (OTP) System: Generates a unique password for each access attempt, sent to the user's phone via SMS, ensuring authorized access.
LCD Display: Offers real-time feedback, displaying information such as system status, alerts, or instructions, aiding user interaction.
GSM Module: Facilitates bidirectional communication via SMS, enabling the system to send alerts or notifications to the user's mobile phone and receive commands.
Buzzer: Acts as an audible alert, sounding in case of potential intrusions or system malfunctions, providing immediate warnings and deterring intruders.
Salient Features in Workflow
Writing user-defined functions (customized functions).
Replacing library functions with user-programmed functions wherever needed.
Using controllers not typically included in academics.
PCB design using EasyEDA (open source).
PCB fabrication.
Controllers used: ESP32 DevKit V1.
Specifications
Software Details
Development Environment: Arduino IDE
Hardware Details
ESP32 DevKit V1
PIR Sensor
4x4 Keypad
16x2 LCD Display
Servo Motor
GSM Module
Buzzer

# Flow of Operation 



Initially, the system's PIR sensor will be in a standby mode, waiting to detect motion. Once motion is detected, the system will trigger an alert, the LCD backlight will turn on, and the display will show "Enter the PIN."

As the user enters the PIN on the 4x4 keypad, each character will be displayed on the LCD one after the other. If the entered PIN does not match the predefined PIN "9876," the LCD will display "Wrong Password." After three unsuccessful attempts, the system will send an SMS with the message "Unauthorized Access" to the specified Indian mobile number via the GSM module, and the Buzzer will activate.

If the entered PIN matches the predefined PIN "9876," the LCD will display "Success" and, after 1 second, will change to "Sending OTP" while the GSM module sends an SMS containing a random 4-digit OTP to the mobile number. After the OTP is sent, the LCD will display "Enter OTP: ".

If the OTP entered through the keypad matches the OTP sent via GSM, the LCD will display "Door Unlocked," and the Servo motor will rotate by 90 degrees. If the OTP does not match, the LCD will display "Wrong OTP." After three unsuccessful attempts, the system will send an SMS with the message "Unauthorized Access" to the specified Indian mobile number via the GSM module, and the Buzzer will activate.

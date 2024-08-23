#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include <Keypad.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>
// Pin Definitions
#define PIR_PIN 34
#define SERVO_PIN 4
#define BUZZER_PIN 23

// Predefined PIN and variables
String predefinedPIN = "XXXX";  //set your predefined PIN
String enteredPIN = "";
String receivedOTP = "";
String enteredOTP = "";
int incorrectAttempts = 0;

// Initialize components
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Change the I2C address if needed
Servo myServo;
SoftwareSerial SIM900(16, 17);  // RX2, TX2
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {32, 33, 25, 26};
byte colPins[COLS] = {27, 14, 12, 13};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  
  // Initialize the PIR sensor pin
  pinMode(PIR_PIN, INPUT);
  
  // Initialize the buzzer pin
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW); // Turn off the buzzer initially
  
  // Initialize the servo motor
  myServo.attach(SERVO_PIN);
  myServo.write(0); // Initial position (locked)
  
  // Initialize GSM module
  SIM900.begin(9600);
  delay(1000); // Allow GSM module to initialize
}

void loop() {
  // Check for motion detected by PIR sensor
  if (digitalRead(PIR_PIN) == HIGH) {
    handleMotionDetected();
  }
}

void handleMotionDetected() {
  lcd.clear();
  lcd.print("Enter the PIN:");
  lcd.setCursor(0, 1);
  enteredPIN = "";
  
  // Wait for the user to enter the PIN
  while (enteredPIN.length() < 4) {
    char key = keypad.getKey();
    if (key) {
      enteredPIN += key;
      lcd.print("*"); // Display * for each character entered
    }
  }
  
  checkPIN();
}

void checkPIN() {
  if (enteredPIN == predefinedPIN) {
    lcd.clear();
    lcd.print("Success");
    delay(1000);
    lcd.clear();
    lcd.print("Sending OTP...");
    sendOTP();
  } else {
    incorrectAttempts++;
    lcd.clear();
    lcd.print("INVALID PIN");
    delay(1000);
    if (incorrectAttempts >= 3) {
      triggerAlarm("Unauthorized Access");
    } else {
      lcd.clear();
      handleMotionDetected();
    }
  }
}

// Additional functions like sendOTP, checkOTP, and triggerAlarm will be added here.

void sendOTP() {
  // Generate a random 4-digit OTP
  int otp = random(1000, 9999);
  receivedOTP = String(otp);

  // Send the OTP via GSM module
  SIM900.print("AT+CMGF=1\r");  // Set SMS to text mode
  delay(1000);
  SIM900.print("AT+CMGS=\"+XXXXXXXXXXXX\"\r"); // Replace with the correct mobile number
  delay(1000);
  SIM900.print("Your OTP is: " + receivedOTP + "\r");
  delay(1000);
  SIM900.write(26); // ASCII code for CTRL+Z to send the SMS
  delay(1000);

  lcd.clear();
  lcd.print("Enter OTP :");
  lcd.setCursor(0, 1);
  enteredOTP = "";

  // Wait for the user to enter the OTP
  while (enteredOTP.length() < 4) {
    char key = keypad.getKey();
    if (key) {
      enteredOTP += key;
      lcd.print("*"); // Display * for each character entered
    }
  }

  checkOTP();
}

void checkOTP() {
  if (enteredOTP == receivedOTP) {
    lcd.clear();
    lcd.print("Door Unlocked");
    myServo.write(90); // Rotate servo to unlock position
    delay(2000); // Keep the door unlocked for 2 seconds
    myServo.write(0); // Return to locked position
    lcd.clear();
  } else {
    incorrectAttempts++;
    lcd.clear();
    lcd.print("INVALID OTP");
    delay(1000);
    if (incorrectAttempts >= 3) {
      triggerAlarm("Unauthorized Access");
    } else {
      lcd.clear();
      sendOTP();
    }
  }
}

void triggerAlarm(String message) {
  // Send Unauthorized Access SMS via GSM module
  SIM900.print("AT+CMGF=1\r");  // Set SMS to text mode
  delay(1000);
  SIM900.print("AT+CMGS=\"+XXXXXXXXXXXX\"\r"); // Replace with the correct mobile number
  delay(1000);
  SIM900.print(message + "\r");
  delay(1000);
  SIM900.write(26); // ASCII code for CTRL+Z to send the SMS
  delay(1000);

  // Activate the buzzer
  digitalWrite(BUZZER_PIN, HIGH);
  delay(5000); // Sound the buzzer for 5 seconds
  digitalWrite(BUZZER_PIN, LOW);

  incorrectAttempts = 0; // Reset attempts
  lcd.clear();
}

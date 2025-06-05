#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// === Object Initialization ===
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD at I2C address 0x27
Servo servo1;  // Sorter 
Servo servo2;  // Flap gate

// === Pin Definitions ===
const int moistSensorPin = A0;
const int irSensorPin = 7;

// === Servo Positions ===
const int flapOpen = 180;
const int wetPosition = 60;
const int dryPosition = 0;
const int metalPosition = 180;

// === Setup ===
void setup() {
  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Attach servos to PWM pins
  servo1.attach(5);
  servo2.attach(6);

  // Setup IR pin
  pinMode(irSensorPin, INPUT);

  // Initialize Serial Monitor
  Serial.begin(9600);
}

// === Display Functions ===
void showIdleMessage() {
  lcd.setCursor(0, 0);
  lcd.print("Smart Garbage");
  lcd.setCursor(2, 1);
  lcd.print("Segregation");
}

// === Waste Handling Functions ===

// --- Wet Waste ---
void handleWetWaste() {
  Serial.println("WET WASTE");
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("WET WASTE");

  servo1.write(wetPosition);  // Position for wet waste
  delay(1000);
  servo2.write(flapOpen);     // Open flap
  delay(100);
}

// --- Dry Waste ---
void handleDryWaste() {
  Serial.println("DRY WASTE");
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("DRY WASTE");

  servo1.write(dryPosition);  // Position for dry waste
  delay(100);
  servo2.write(flapOpen);     // Open flap
  delay(100);
}

// --- Metal Waste ---
void handleMetalWaste() {
  Serial.println("METAL WASTE");
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("METAL WASTE");

  servo1.write(metalPosition);  // Position for metal waste
  delay(1000);
  servo2.write(flapOpen);       // Open flap
  delay(100);
}

// === Main Loop ===
void loop() {
  // Read sensor values
  int moistureLevel = analogRead(moistSensorPin);
  int irStatus = digitalRead(irSensorPin);

  // Debug logs
  Serial.print("Moisture level: ");
  Serial.println(moistureLevel);
  Serial.print("IR sensor: ");
  Serial.println(irStatus);

  delay(200);

  // === Waste Type Detection ===
  if (moistureLevel < 1000 && moistureLevel > 100 && irStatus == 0) {
    handleWetWaste();
  } else if (moistureLevel > 1000 && irStatus == 0) {
    handleDryWaste();
  } else if (moistureLevel < 100 && irStatus == 0) {
    handleMetalWaste();
  } else {
    // Idle state
    servo1.write(dryPosition);  // Reset to default
    servo2.write(dryPosition);
    showIdleMessage();
  }
}

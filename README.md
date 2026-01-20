# ♻️ Smart Garbage Segregation System

An Arduino-based project that automatically detects and segregates waste into **Wet**, **Dry**, and **Metal** categories using sensors and servo motors.

## 📦 Features

- Automatic detection of waste type
- Segregates waste into three types:
  - Wet Waste
  - Dry Waste
  - Metal Waste
- LCD display shows waste type
- Easy to implement and low-cost design

---

## 🛠️ Hardware Components

| Component              | Quantity |
|------------------------|----------|
| Arduino UNO/Nano       | 1        |
| Moisture Sensor        | 1        |
| IR Sensor              | 1        |
| Servo Motor (SG90/others) | 2    |
| LCD Display (16x2 I2C) | 1        |
| Jumper Wires           | As needed |
| Breadboard             | 1        |
| Power Supply           | 1        |

---

## 🔌 Circuit Connections

- **Moisture Sensor** → A0  
- **IR Sensor** → D7  
- **Servo Motor 1 (Sorter)** → D5  
- **Servo Motor 2 (Flap Gate)** → D6  
- **I2C LCD** → SDA/SCL (A4/A5 on UNO)  
- **Power** → 5V and GND

---

## LCD configration

- LiquidCrystal_I2C lcd(0x27, 16, 2);

---

## 💡 Working Logic

1. **IR Sensor** detects the presence of waste.
2. **Moisture Sensor** determines moisture content:
   - `Moisture < 100` → Metal Waste
   - `100 < Moisture < 1000` → Wet Waste
   - `Moisture > 1000` → Dry Waste
3. **Servo 1** rotates to respective bin.
4. **Servo 2** opens flap to drop waste.
5. **LCD** displays the identified waste type.

---

## 📟 LCD Display

- **Idle State**:
Smart Garbage Segregation System

- **Detection State**:
1. WET WASTE
2. DRY WASTE
3. METAL WASTE

---
## Basic Logic

<pre>
if (moistureLevel < 1000 && moistureLevel > 100 && irStatus == 0) {
  handleWetWaste();
} else if (moistureLevel > 1000 && irStatus == 0) {
  handleDryWaste();
} else if (moistureLevel < 100 && irStatus == 0) {
  handleMetalWaste();
} else {
  servo1.write(dryPosition);  
  servo2.write(dryPosition);
  showIdleMessage();
}
</pre>

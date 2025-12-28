#include <ESP32Servo.h>

// Service Feeder Servo Pin Configuration
const int FEEDER_SERVO_PIN = 6;

//Service Hatch Angle Configuration
const int FEEDER_POS1_Angle  = 180;
const int FEEDER_POS0_Angle = 0;

int FEEDER_LAST_POS = 0;

// Servo instance
Servo feederServo;

// Initialize service hatch
void feederInit() {
    feederServo.attach(FEEDER_SERVO_PIN);
    feederServo.write(FEEDER_POS0_Angle);
    Serial.println("SERVICE HATCH SERVO Online");
}

// Open service hatch
void setfeederPosition1() {
    feederServo.write(FEEDER_POS1_Angle);
    FEEDER_LAST_POS = 1;
}

// Close service hatch
void setfeederPosition0() {
    feederServo.write(FEEDER_POS0_Angle);
    FEEDER_LAST_POS = 0;
}

int getFeederPOS() {
  return FEEDER_LAST_POS;
}
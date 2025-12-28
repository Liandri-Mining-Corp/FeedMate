// Service Hatch Servo Library Configuration
#include <ESP32Servo.h>

// Service Hatch Servo Pin Configuration
const int SERVICE_HATCH_SERVO_PIN = 2;

//Service Hatch Angle Configuration
const int HATCH_OPEN_ANGLE  = 90;
const int HATCH_CLOSED_ANGLE = 0;

// Servo instance
Servo serviceHatchServo;

// Hatch state
bool is_service_hatch_open = false; //default is closed

// Initialize service hatch
void serviceHatchInit() {
    serviceHatchServo.attach(SERVICE_HATCH_SERVO_PIN);
    serviceHatchServo.write(HATCH_CLOSED_ANGLE);
    is_service_hatch_open = false;
    Serial.println("SERVICE HATCH SERVO Online");
}

bool getServiceHatchState() {return is_service_hatch_open;}

// Open service hatch
void openServiceHatch() {
    serviceHatchServo.write(HATCH_OPEN_ANGLE);
    is_service_hatch_open = true;
}

// Close service hatch
void closeServiceHatch() {
    serviceHatchServo.write(HATCH_CLOSED_ANGLE);
    is_service_hatch_open = false;
}


//TODO remove Debug funtion if not required

//DEBUG: Toggle service hatch state
void toggleServiceHatch() {
    if (is_service_hatch_open) {
        closeServiceHatch();
    } else {
        openServiceHatch();
    }
}
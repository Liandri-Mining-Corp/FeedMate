// Ultrasonic Sensor Pin Configuration
const int TRIGGER_PIN = 5;
const int ECHO_PIN    = 4;


// Initialize ultrasonic sensor
void ultrasonicInit() {
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    Serial.println("Ultrasonic Sensor Online");
}

// Returns distance in centimeters
long getDistance() {
    long pulse_duration_us;
    long distance_cm;

    // Send trigger pulse
    digitalWrite(TRIGGER_PIN, HIGH);
    delay(10);               // Short trigger pulse
    digitalWrite(TRIGGER_PIN, LOW);

    // Measure echo pulse duration
    pulse_duration_us = pulseIn(ECHO_PIN, HIGH);

    // Calculate distance
    distance_cm = (pulse_duration_us / 2) * 0.03432;

    return distance_cm;
}
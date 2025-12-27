// LED and Ultrasonic Sensor Pins
// LED pins
int red_led_pin = 15;
int yellow_led_pin = 16;
int green_led_pin = 17;
// Ultrasonic sensor pins
int trigger_pin = 5; // Trigger pin to send the ultrasonic pulse
int echo_pin = 4;    // Echo pin to receive the reflected pulse

// Variables for distance calculation
long dauer = 0;      // Duration of the pulse in microseconds
long entfernung = 0; // Calculated distance in centimeters

// Initialize LEDs and Ultrasonic Sensor
void ultraAmpelInit() {
  // Set ultrasonic pins as input/output
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  // Set LED pins as outputs
  pinMode(red_led_pin, OUTPUT);    // Red LED
  pinMode(yellow_led_pin, OUTPUT); // Yellow LED
  pinMode(green_led_pin, OUTPUT);  // Green LED

  // Ensure all LEDs are off initially
  allLightsOff();
}

// Send ultrasonic pulse and calculate distance
void pulse() {
  Serial.println("Pulse");

  // Send a 10-microsecond HIGH pulse
  digitalWrite(trigger_pin, HIGH);
  delay(10); // Wait 10ms
  digitalWrite(trigger_pin, LOW);

  Serial.println("Done");
  Serial.println("");

  // Measure the duration of the echo pulse
  dauer = pulseIn(echo_pin, HIGH);
  Serial.println(dauer);
  Serial.println("");

  // Calculate distance in cm (speed of sound = 343.2 m/s)
  // entfernung = (duration / 2) * 0.03432
  entfernung = (dauer / 2) * 0.03432;
  Serial.print(entfernung);
  Serial.println(" cm");
}

// Change LED based on distance
void changeLight() {
  if (entfernung > 11) {
    allLightsOff();
    digitalWrite(red_led_pin, HIGH); // Red LED ON
    Serial.println("Red Light");
  }
  else if (entfernung > 5 && entfernung <= 11) {
    allLightsOff();
    digitalWrite(yellow_led_pin, HIGH); // Yellow LED ON
    Serial.println("Yellow Light");
  }
  else if (entfernung <= 5) {
    allLightsOff();
    digitalWrite(green_led_pin, HIGH); // Green LED ON
    Serial.println("Green Light");
  }
}

// Turn off all LEDs
void allLightsOff() {
  digitalWrite(red_led_pin, LOW);
  digitalWrite(yellow_led_pin, LOW);
  digitalWrite(green_led_pin, LOW);
}
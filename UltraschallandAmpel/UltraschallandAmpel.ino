// Declare LED Pins
int red_led_pin = 15;
int yellow_led_pin = 16;
int green_led_pin= 17;

// Declare Ultraschall Pins & Varibles
int trigger_pin = 5;
int echo_pin = 4;

// Declare Variables for distance Calculation
long dauer = 0;
long entfernung = 0;

void setup() {
  Serial.begin(115200); //Start Serial
  
  // Declare Ultraschall Pins function
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  
  // Declare LEDs Pins function
  pinMode(red_led_pin, OUTPUT); // Pin 5 ist ein Ausgang.
  pinMode(yellow_led_pin, OUTPUT); // Pin 6 ist ein Ausgang.
  pinMode(green_led_pin,OUTPUT); // Pin 7 ist ein Ausgang.
}

void loop() {
 pulse();
 changeLight();
 delay(1200);
}

void pulse() {
  //Send Pulse
  Serial.println("Pulse");
  digitalWrite(trigger_pin, HIGH);
  delay(10);
  digitalWrite(trigger_pin, LOW);
  Serial.println("Done");
  Serial.println("");

  //get time for the pulse to return
  dauer = pulseIn(echo_pin, HIGH);
  Serial.println(dauer);
  Serial.println("");

  //calculate the distance
  entfernung = (dauer/2) * 0.03432;
  Serial.print(entfernung);
  Serial.println(" cm");
}

void changeLight() {  //change light based on the distance
  if(entfernung > 11) {
    allLightsOff();
    digitalWrite(red_led_pin, HIGH);
    Serial.println("Red Light");
  }
  if(entfernung > 5 && entfernung < 11){
    allLightsOff();
    digitalWrite(yellow_led_pin, HIGH);
    Serial.println("Yellow Light");
  }
  if(entfernung < 5) {
    allLightsOff();
    digitalWrite(green_led_pin, HIGH);
    Serial.println("Green Light");
  }
}

void allLightsOff() { //turn off all LEDs
  digitalWrite(red_led_pin, LOW);
  digitalWrite(yellow_led_pin, LOW);
  digitalWrite(green_led_pin, LOW);
}
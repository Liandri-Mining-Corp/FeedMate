#include <ESP32Servo.h> //This Libery contains the everything to control the Servo
Servo myservo; //Create a Servo object

int servopin = 32; //declare the Pin where the Servo is

void setup() {
  Serial.begin(115200); //Start Serial output
  
  myservo.attach(servopin); // attach the Servo pin with the Servo Object
  Serial.println("Servo Online");
  
  myservo.write(0);   //set Servo to position 0°
}
void loop() {
  myservo.write(90);  //set Servo to position 90°
  delay(300);
  myservo.write(0);   //set Servo to position 0°
}
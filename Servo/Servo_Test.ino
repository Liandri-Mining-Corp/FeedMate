#include <ESP32Servo.h>
Servo myservo;

int servopin = 32;

void setup() {
  Serial.begin(115200);
  
  myservo.attach(servopin);
  Serial.println("Servo Online");
  
  myservo.write(0);
}
void loop() {
  //myservo.write(0);
  //delay(300);

}
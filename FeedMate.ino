#include <WiFi.h>
#include "time.h"
#include <ESP32Servo.h>

//Add Servo objects
Servo Servo_1;
Servo Servo_2;

//Define Servo Data pins
//int servopin = 32;
//int servopin = 32;

//Sensor pins
//int moisture_data_pin = ;

//int trigger_pin = 27;
//int echo_pin = 14;

//WLAN Settings
const char* ssid     = "WoomyOS Network";
const char* password = "Inkling-Queen";

//NTP Settings
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

void setup(){
  //Enable Serial and set Baudrate
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);0
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

}

void loop(){
}


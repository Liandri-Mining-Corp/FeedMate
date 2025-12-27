// include the Wire and LiquidCrystal Library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Define the SDA and SCL Pin for the LCD
#define SDA_PIN 8
#define SCL_PIN 9

//Create a LiquidCrystal Object for the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
 Wire.begin(SDA_PIN, SCL_PIN); //start Wire on the SDA and SCL Pin

 //Start LCD and Backlight (No Backlight possible but very difficult to read)
 lcd.init();
 lcd.backlight();

 // set the starting point of the Text and print the text on the LCD
 lcd.setCursor(0, 0);
 lcd.print("LCD laeuft");
 lcd.setCursor(0, 1);
 lcd.print("ESP32-S3");
}

void loop() {}

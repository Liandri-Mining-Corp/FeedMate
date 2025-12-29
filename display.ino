// Include Libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD Configuration
#define SDA_PIN 8
#define SCL_PIN 9
const uint8_t LCD_ADDRESS = 0x27;
const int LCD_COLS    = 16;
const int LCD_ROWS    = 2;

// Create LiquidCrystal_I2C object
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);

// Initialize LCD
void displayInit() {
    Wire.begin(SDA_PIN, SCL_PIN); // Initialize I2C on specified pins

    lcd.init();       // Initialize LCD
    lcd.backlight();  // Enable backlight

    // Display initial text
    lcd.setCursor(0, 0);
    lcd.print("WoomyOS");
    lcd.setCursor(0, 1);
    lcd.print("Booting!");
}

// Show boot completion message
void displayBootDone() {
    delay(1800);        // Wait before showing message
    clearDisplay();

    lcd.setCursor(0, 0);
    lcd.print("WoomyOS");
    lcd.setCursor(0, 1);
    lcd.print("Boot Done!");

    delay(3600);        // Keep message on screen
}

// Clear LCD display
void clearDisplay() {
    lcd.clear();
}

// Write text to line 1
void writeLine1(const String &text) {
    lcd.setCursor(0, 0);
    lcd.print(text);
}

// Write text to line 2
void writeLine2(const String &text) {
    lcd.setCursor(0, 1);
    lcd.print(text);
}
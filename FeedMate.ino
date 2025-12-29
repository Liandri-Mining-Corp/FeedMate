
// Forward declarations

bool getServiceHatchState();
float getHumidity();
float getTemperature();

// Feeding Time Configuration
// Defines the daily automatic feeding time
const int FEEDING_TIME_HOUR   = 14;
const int FEEDING_TIME_MINUTE = 1;
// const int FEEDING_TIME_SECOND = 0; // Optional second-level control

// Arduino Setup
void setup() {
  // Enable serial communication for debugging and status output
  Serial.begin(115200);

  // Initialize LCD display (I2C, welcome text, backlight)
  displayInit();

  // Initialize RFID reader (SPI + MFRC522)
  rfidInit();

  // Initialize service hatch servo and set default position (closed)
  serviceHatchInit();

  // Initialize LED controller (traffic-light style food level indicator)
  ledControllerInit();

  // Initialize ultrasonic sensor for distance / food level measurement
  ultrasonicInit();

  // Initialize moisture and temperature sensor (DHT)
  moistureSensorInit();

  // Initialize feeder motor / mechanism
  feederInit();

  // Initialize system time via NTP and timezone
  timerInit();

  // Initialize Wi-Fi and start the embedded web server
  webServerInit();

  // Display boot completion message on the LCD
  displayBootDone();
}

// Arduino Main Loop
void loop() {
  // Scheduled feeding logic
  // Triggers the feeder once per day at the configured feeding time
  if (isTime(FEEDING_TIME_HOUR, FEEDING_TIME_MINUTE, 0)) {
    runFeedingCycle();
  }

  // RFID-controlled service hatch
  // Toggles the service hatch when an authorized RFID card is detected
  // The hatch opens if currently closed, and closes if currently open
  if (isAuthorizedCardDetected() && !getServiceHatchState()) {
    Serial.println("opening");
    openServiceHatch();
    delay(1600); // Allow servo movement to complete
  }
  else if (isAuthorizedCardDetected() && getServiceHatchState()) {
    Serial.println("closing");
    closeServiceHatch();
    delay(1600); // Allow servo movement to complete
  }

  // Web server handling
  // Process incoming HTTP requests
  webServerLoop();

  // Food level indicator update
  // Measure distance and update LED status accordingly
  updateLedByDistance(getDistance());
}

// Execute feeding cycle
void runFeedingCycle() {
  // Perform multiple feeder movements to dispense food
  for (int cycle_index = 0; cycle_index < 4; cycle_index++) {

    // Toggle feeder position to release food
    if (getFeederPOS() == 0) {
      setFeederPosition1();
      delay(4000); // Allow feeder to complete movement
    } else {
      setFeederPosition0();
      delay(4000); // Allow feeder to complete movement
    }
  }

  // Update LED indicator after feeding
  updateLedByDistance(getDistance());
}
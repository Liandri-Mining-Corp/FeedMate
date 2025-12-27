// Libraries for RFID communication
#include <SPI.h>        // SPI bus library
#include <MFRC522.h>    // Library for MFRC522 RFID reader

// RFID reader pin definitions
#define SS_PIN 10   // SDA (Slave Select) pin for RFID reader
#define RST_PIN 14  // Reset pin for RFID reader

// Servo control
#include <ESP32Servo.h>   // Library used to control servo motors on ESP32
Servo service_hatch_servo; // Create a Servo object for the service hatch

int service_hatch_servopin = 2; // GPIO pin connected to the servo signal wire

// RFID configuration
int rfid_salt = 10; // Salt value used to modify the UID for simple obfuscation

// Create an MFRC522 object for the RFID reader
MFRC522 RFID(SS_PIN, RST_PIN);

// Service hatch state tracking
// false = closed (default)
// true  = open
bool service_hatch_state = false;


// // Emtpy Arduino setup function as this is not the main sketch file
// void setup() {
// }

// // Emtpy Arduino loop function as this is not the main sketch file
// void loop() {
// }

// Initialize RFID reader and servo
void initRFIDHatch()
{
  SPI.begin();        // Start SPI communication
  RFID.PCD_Init();    // Initialize RFID reader hardware

  // Attach the servo to its control pin
  service_hatch_servo.attach(service_hatch_servopin);

  // Set servo to closed position (0 degrees)
  service_hatch_servo.write(0);

  Serial.println("RFID and Service Hatch Ready");
}


// Check for RFID card and handle access
void checkCard()
{
  long code = 0;   // Variable used to store the salted UID value

  // Check if a new RFID card is present
  if (!RFID.PICC_IsNewCardPresent()) {
    // No card detected
    return;
  }

  // Check if the card UID can be read
  if (!RFID.PICC_ReadCardSerial()) {
    // Failed to read card
    return;
  }

  // Output UID information
  Serial.print("The ID of the RFID-Tag is: ");

  // Read each byte of the UID
  for (byte i = 0; i < RFID.uid.size; i++) {
    // Print UID byte in hexadecimal format
    Serial.print(RFID.uid.uidByte[i], HEX);
    Serial.print(" ");

    // Combine UID bytes into a single value and apply salt
    code = ((code + RFID.uid.uidByte[i]) * rfid_salt);
  }

  Serial.println(); // Line separator

  // Print calculated UID code
  Serial.println(code);

  // Print current service hatch state
  Serial.print("Service Hatch State: ");
  Serial.print(service_hatch_state);
  Serial.println();

  // Check if UID matches the authorized value
  if (code == 1435580) {
    if (service_hatch_state == false) {
      openservicehatch();   // Open hatch if currently closed
    } else {
      closeservicehatch(); // Close hatch if currently open
    }
  }
}

// Open the service hatch
void openservicehatch()
{
  service_hatch_servo.write(90); // Rotate servo to open position
  service_hatch_state = true;    // Update hatch state
  Serial.println("Service Hatch OPENED");
}

// Close the service hatch
void closeservicehatch()
{
  service_hatch_servo.write(0);  // Rotate servo to closed position
  service_hatch_state = false;   // Update hatch state
  Serial.println("Service Hatch CLOSED");
}

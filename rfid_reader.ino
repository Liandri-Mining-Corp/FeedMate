// RFID Reader Library Configuration
#include <SPI.h>
#include <MFRC522.h>

// RFID pin definitions
const int RFID_SS_PIN  = 10;
const int RFID_RST_PIN = 14;

// Salt used to obfuscate UID
const int RFID_SALT = 10;

// Authorized UID code
const long AUTHORIZED_CODE = 1435580;

// RFID reader instance
MFRC522 rfidReader(RFID_SS_PIN, RFID_RST_PIN);

// Initialize RFID reader
void rfidInit() {
    SPI.begin();
    rfidReader.PCD_Init();
    Serial.println("RFID Online");
}

// Check for authorized RFID card
// Returns true if an authorized card is detected
bool isAuthorizedCardDetected() {
    long uid_code = 0;

    if (!rfidReader.PICC_IsNewCardPresent()) {
        return false;
    }

    if (!rfidReader.PICC_ReadCardSerial()) {
        return false;
    }

    // Calculate salted UID code
    for (byte i = 0; i < rfidReader.uid.size; i++) {
        uid_code = (uid_code + rfidReader.uid.uidByte[i]) * RFID_SALT;
    }

    return uid_code == AUTHORIZED_CODE;
}
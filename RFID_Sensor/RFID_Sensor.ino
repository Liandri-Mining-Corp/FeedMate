//Libraries for RFID
#include <SPI.h>
#include <MFRC522.h>

// Define RFID-Reader pin
#define SS_PIN 10 // SDA Pin
#define RST_PIN 9 // RST Pin

// Create a MFRC522 Object as the RFID Scanner with SDA Pin and RST Pin as Paremetar
MFRC522 RFID(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200); // Start Serial output in Monitor
  Serial.println("Booted");
  SPI.begin(); // Start SPI connection
  RFID.PCD_Init(); // Initslise RFID Scanner

}

void loop() {
  long code = 0; // variable for saving the UID
  long code1 = 0; // variable for saving the UID1
  
  // check if a RFID Card is present, if not repeat
  if (!RFID.PICC_IsNewCardPresent()){
    Serial.println("card not found");
    return;
  }

  //if a RFID-Sender is selected, repeat
  if (! RFID.PICC_ReadCardSerial()){
      return;
  }

  //print one line on Serial
  Serial.print("The ID of the RFID-Tag is:");

  //get the UID
  for (byte i = 0; i < RFID.uid.size; i++) {
    Serial.print(RFID.uid.uidByte[i], HEX); //Read the UID, which is in seperated in 4 blocks, and send block on postion i them to the Serial Terminal as HEX
    Serial.print(" "); //Block seperator
    code = ((code+RFID.uid.uidByte[i])*10); //read the block in position i, add it to code varible and strech it by factor 10
    code1 = ((code+RFID.uid.uidByte[i])); //read the block in position i, add it to code varible 
  }
  Serial.println(); // line Seperator
  
  //print the code variables
  Serial.println(code);
  Serial.println(code1);
}

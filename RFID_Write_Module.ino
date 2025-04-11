#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5
#define RST_PIN 4

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

String inputString = "";
bool stringComplete = false;

void setup() {
  Serial.begin(115200);
  while (!Serial);  // Wait for Serial Monitor

  SPI.begin();  // Init SPI bus
  rfid.PCD_Init();  // Init MFRC522

  Serial.println("Enter text (max 16 chars) to write to RFID card:");

  // Prepare the default key
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
}

void loop() {
  // Read Serial input
  if (Serial.available()) {
    inputString = Serial.readStringUntil('\n');
    inputString.trim();  // Remove trailing \r or spaces
    stringComplete = true;
  }

  // Wait for card
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  if (stringComplete) {
    // Format string into 16 bytes
    byte buffer[16] = { 0 };
    int len = inputString.length();
    if (len > 16) len = 16;
    inputString.getBytes(buffer, len + 1);  // +1 for null terminator

    byte block = 4;  // You can change this
    MFRC522::StatusCode status;

    // Authenticate
    status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(rfid.uid));
    if (status != MFRC522::STATUS_OK) {
      Serial.print("Authentication failed: ");
      Serial.println(rfid.GetStatusCodeName(status));
      return;
    }

    // Write data
    status = rfid.MIFARE_Write(block, buffer, 16);
    if (status != MFRC522::STATUS_OK) {
      Serial.print("Write failed: ");
      Serial.println(rfid.GetStatusCodeName(status));
    } else {
      Serial.println("✅ Write successful!");
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    stringComplete = false;
  }
}

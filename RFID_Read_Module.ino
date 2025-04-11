#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5    // SDA pin on RFID module
#define RST_PIN 4   // Reset pin

MFRC522 rfid(SS_PIN, RST_PIN);  // Create MFRC522 instance
MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(115200);
  while (!Serial);  // Wait for Serial Monitor to open

  SPI.begin();      // Init SPI bus
  rfid.PCD_Init();  // Init RFID reader
  Serial.println("RFID Reader Initialized");

  // Prepare the default key (factory default is 0xFF 6 times)
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}

void loop() {
  // Check if a card is present
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Print UID
  Serial.print("Card UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // Authenticate block 4 (change if needed)
  byte block = 4;
  byte buffer[18];  // To hold read data
  byte size = sizeof(buffer);

  MFRC522::StatusCode status;

  status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(rfid.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Auth failed: ");
    Serial.println(rfid.GetStatusCodeName(status));
    return;
  }

  // Read the block
  status = rfid.MIFARE_Read(block, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Read failed: ");
    Serial.println(rfid.GetStatusCodeName(status));
  } else {
    Serial.print("Data from block ");
    Serial.print(block);
    Serial.print(": ");

    for (int i = 0; i < 16; i++) {
      if (buffer[i] >= 32 && buffer[i] <= 126) {
        Serial.print((char)buffer[i]);  // Printable ASCII
      } else {
        Serial.print(".");  // Non-printable
      }
    }
    Serial.println();
  }

  // Halt card and stop crypto
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

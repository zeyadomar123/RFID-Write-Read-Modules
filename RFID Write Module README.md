# RFID Write Module – Arduino IDE 2.3.5

This sketch enables writing user-defined text data to a passive RFID card using the MFRC522 RFID module and an Arduino-compatible microcontroller (e.g., ESP32-WROOM). Users can input up to 30 characters via UART to the serial monitor, which will be stored in a specified block of the RFID card.

---

## Hardware Requirements

- **MFRC522 RFID Reader/Writer Module**
- **RFID Cards or Tags** (13.56 MHz)
- **Microcontroller** (tested on ESP32-wroom)
- **Connections**:
  - `SDA/SS` → GPIO5  
  - `RST` → GPIO4  
  - `MOSI`, `MISO`, `SCK` → Connected to SPI pins

---

## How It Works

1. Open the Serial Monitor at **115200 baud**.
2. write up to 30 characters.
3. Tap a blank or previously written RFID card.
4. The data is written to **Block 4** of the RFID tag.

The sketch uses the `MFRC522` library to handle low-level RFID communication and authenticates the tag using a default key (`0xFF` bytes). If authentication is successful, the input string is written to block 4 using `MIFARE_Write`.

---

##  Serial Output Example

```text
Enter text (max 30 chars) to write to RFID card:
>>03/04 12:00 CO2:430,TVOC:22
Write successful!

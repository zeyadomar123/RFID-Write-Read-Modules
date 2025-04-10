# ESP32 RFID Reader with MFRC522

This demonstrates how to use an **ESP32** microcontroller with the **MFRC522 RFID reader** to read data stored on **MIFARE Classic 1K** cards. It reads the card’s UID and extracts stored data from a specific memory block, displaying the output in the **Serial Monitor**.

---


---

## Code Features

- Initializes SPI and RFID reader
- Detects a nearby RFID card
- Reads and prints the UID (serial number)
- Authenticates a specific data block (default: Block 4)
- Reads 16 bytes of data from the block and prints printable characters
- Gracefully halts and exits communication after each read

---

## How to Use

1. Wire the hardware as per the table above.
2. Open this code in the Arduino IDE.
3. Select the correct ESP32 board and COM port.
4. Upload the sketch to your ESP32.
5. Open the Serial Monitor at 115200 baud.
6. Tap a MIFARE card on the reader and observe:
   - Card UID
   - Data from block 4 (if any)

---

## Library Dependencies

Install the following via Library Manager:

- [MFRC522 by Miguel Balboa](https://github.com/miguelbalboa/rfid)
- SPI (built-in with Arduino)

---

##  Example Output


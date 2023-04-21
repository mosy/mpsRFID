// RST --> 22
// SDA --> 21
// SCK --> 18
// MOSI --> 23
// MISO --> 19
#include <SPI.h>
#include <MFRC522.h>
#include "NfcAdapter.h"

#define CS_PIN 21 

MFRC522 mfrc522(CS_PIN, UINT8_MAX); // Create MFRC522 instance

NfcAdapter nfc = NfcAdapter(&mfrc522);

void setup() {
    Serial.begin(115200);
    Serial.println("NDEF writer\nPlace a formatted Mifare Classic or Ultralight NFC tag on the reader.");
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522
    nfc.begin();
}

void loop() {
    if (nfc.tagPresent()) {
        Serial.println("Writing record to NFC tag");
        NdefMessage message = NdefMessage();
        message.addUriRecord("def");
        bool success = nfc.write(message);
        if (success) {
          Serial.println("\tSuccess. Try reading this tag with your phone.");        
          delay(10000);
        } else {
          Serial.println("\tWrite failed.");
        }
    }
    delay(5000);
}


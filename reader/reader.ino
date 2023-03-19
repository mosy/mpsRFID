#include <SPI.h>
#include <MFRC522.h>
#include "NfcAdapter.h"

#include <WiFi.h>
#include <ModbusIP_ESP8266.h>
#include "arduino_secrets.h"

#define CS_PIN 21

//MCRC522 related
MFRC522 mfrc522(CS_PIN, UINT8_MAX); // Create MFRC522 instance
NfcAdapter nfc = NfcAdapter(&mfrc522);

//Modbus related

ModbusIP mb;
void setup(void) 
{
	Serial.begin(115200);
	//Wifi
	WiFi.begin(SECRET_SSID, SECRET_PASS);
	while (WiFi.status() != WL_CONNECTED) 
	{
		delay(500);
		Serial.println("WiFi Connectin");
	}
	Serial.println("");
	Serial.println("WiFi connected");  
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());

	//MFRC522 
	Serial.println("Extended NDEF Reader\nPlace an unformatted Mifare Classic tag on the reader to show contents.");
	SPI.begin();        // Init SPI bus
	mfrc522.PCD_Init(); // Init MFRC522
	nfc.begin();
	//Modbus
	mb.server();
	mb.addIreg(1,0,2);
}

void loop(void) 
{
	mb.task();
	if (nfc.tagPresent())
	{
		Serial.println("Reading NFC tag");
		NfcTag tag = nfc.read();
    
		if (tag.hasNdefMessage()) // every tag won't have a message
		{
    
			NdefMessage message = tag.getNdefMessage();

			NdefRecord record = message.getRecord(1);
			int payloadLength = record.getPayloadLength();
			const byte *payload = record.getPayload();
			//PrintHexChar(payload, payloadLength);
			String payloadAsString = "";
			for (int c = 0; c < payloadLength; c++) 
			{
			      payloadAsString += (char)payload[c];
			}
			Serial.print("  Payload (as String): ");
			Serial.println(payloadAsString);
			Serial.println(payload[1]);
			Serial.println(record.getPayloadLength());
			for (int c = 0; c < payloadLength; c++) 
			{
				Serial.print(payload[c]);
				Serial.print(",");
			}
			mb.Ireg(1, payload[1]);
			mb.Ireg(2, payload[2]);
		}
	}
	delay(5000);
}

// RST --> 22
// SDA --> 21
// SCK --> 18
// MOSI --> 23
// MISO --> 19

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
	mb.addIreg(1,0,30);
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

			NdefRecord record = message.getRecord(0);
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
			mb.Ireg(1, (payload[4] << 8) | payload[3]);
			mb.Ireg(2, (payload[6] << 8) | payload[5]);
			mb.Ireg(3, (payload[8] << 8) | payload[7]);
			mb.Ireg(4, (payload[10] << 8) | payload[9]);
			mb.Ireg(5, (payload[12] << 8) | payload[11]);
			mb.Ireg(6, (payload[14] << 8) | payload[13]);
			mb.Ireg(7, (payload[16] << 8) | payload[15]);
			mb.Ireg(8, (payload[18] << 8) | payload[17]);
			mb.Ireg(9, (payload[20] << 8) | payload[19]);
			mb.Ireg(10, (payload[22] << 8) | payload[21]);
			mb.Ireg(11, (payload[24] << 8) | payload[23]);
			mb.Ireg(12, (payload[26] << 8) | payload[25]);
			mb.Ireg(13, (payload[28] << 8) | payload[27]);
			mb.Ireg(14, (payload[30] << 8) | payload[29]);
			
			NdefRecord record2= message.getRecord(1);
			const byte *payload2 = record2.getPayload();
			mb.Ireg(15, (payload2[4] << 8) | payload2[3]);
			mb.Ireg(16, (payload2[6] << 8) | payload2[5]);
			mb.Ireg(17, (payload2[8] << 8) | payload2[7]);
			mb.Ireg(18, (payload2[10] << 8) | payload2[9]);
			mb.Ireg(19, (payload2[12] << 8) | payload2[11]);
			mb.Ireg(20, (payload2[14] << 8) | payload2[13]);
			mb.Ireg(21, (payload2[16] << 8) | payload2[15]);
			mb.Ireg(22, (payload2[18] << 8) | payload2[17]);
			mb.Ireg(23, (payload2[20] << 8) | payload2[19]);
			mb.Ireg(24, (payload2[22] << 8) | payload2[21]);
			mb.Ireg(25, (payload2[24] << 8) | payload2[23]);
			mb.Ireg(26, (payload2[26] << 8) | payload2[25]);
			mb.Ireg(27, (payload2[28] << 8) | payload2[27]);
			mb.Ireg(28, (payload2[30] << 8) | payload2[29]);
			
			NdefRecord record3= message.getRecord(2);
			const byte *payload3 = record3.getPayload();
			mb.Ireg(29, (payload3[4] << 8) | payload3[3]);
			mb.Ireg(30, (payload3[6] << 8) | payload3[5]);
			mb.Ireg(31, (payload3[8] << 8) | payload3[7]);
			mb.Ireg(32, (payload3[10] << 8) | payload3[9]);
			mb.Ireg(33, (payload3[12] << 8) | payload3[11]);
			mb.Ireg(34, (payload3[14] << 8) | payload3[13]);
			mb.Ireg(35, (payload3[16] << 8) | payload3[15]);
			mb.Ireg(36, (payload3[18] << 8) | payload3[17]);
			mb.Ireg(37, (payload3[20] << 8) | payload3[19]);
			mb.Ireg(38, (payload3[22] << 8) | payload3[21]);
			mb.Ireg(39, (payload3[24] << 8) | payload3[23]);
			mb.Ireg(40, (payload3[26] << 8) | payload3[25]);
			mb.Ireg(41, (payload3[28] << 8) | payload3[27]);
			mb.Ireg(42, (payload3[30] << 8) | payload3[29]);
		}
	}
	delay(50);
}

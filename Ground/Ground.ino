#include <SPI.h>
#include <LoRa.h>

#define  LoRa_SCK   13
#define  LoRa_MISO  12
#define  LoRa_MOSI  11
#define  LoRa_CS    10
#define  LoRa_RST   9
#define  DI0        2
#define  BAND    915E6
#define  Select    LOW   //  Low CS means that SPI device Selected
#define  DeSelect  HIGH  //  High CS means that SPI device Deselected

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  pinMode(LoRa_CS, OUTPUT);
  digitalWrite(LoRa_CS, DeSelect);
  SPI.begin();
  LoRa.setPins( LoRa_CS, LoRa_RST, DI0 );
  digitalWrite(LoRa_CS, Select);   //  SELECT (low) LoRa SPI
  //Serial.println("LoRa Sender");
  if (!LoRa.begin(BAND))
  {
    Serial.println("Starting LoRa failed!");
  }
  else
  {
    Serial.println("LoRa Initial OK!");
    delay(1000);
  }
}

void loop()
{
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    Serial.print("Received: ");
    // read packet
    while (LoRa.available())
    {
      Serial.print((char)LoRa.read());
    }
  }
}
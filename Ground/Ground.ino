#include <SPI.h>
#include <LoRa.h>

#define LORA_SCK 5
#define LORA_MISO 19
#define LORA_MOSI 27
#define LORA_SS 18
#define LORA_RST 23
#define LORA_DIO0 26
// #define BAND 921925000
#define BAND 922525000
#define LORA_BW 125E3
#define LORA_SF 9

int co = 0;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(BAND))
  {
    Serial.println("LoRa init failed!");
    while (1)
      ;
  }
  LoRa.setSignalBandwidth(LORA_BW);
  LoRa.setSpreadingFactor(LORA_SF);
  Serial.println("LoRa Initial OK!");
  // LoRa.setSyncWord(0x6D);
  LoRa.receive();
}

void loop()
{
  int packetSize = LoRa.parsePacket();
  if (packetSize > 0)
  {
    co++;
    // Serial.println("-------------");
    while (LoRa.available())
    {
      Serial.print((char)LoRa.read());
    }
    Serial.print("RSSI : ");
    Serial.println(LoRa.packetRssi());
    Serial.println("-------------");
    LoRa.receive();
  }
  // else
  // {
  //   Serial.println("wait data...");
  //   delay(1000);
  // }
}

#include <SPI.h>
#include <LoRa.h>

#define LORA_SCK 5
#define LORA_MISO 19
#define LORA_MOSI 27
#define LORA_SS 18
#define LORA_RST 23
#define LORA_DIO0 26
#define BAND 915E6

void setup()
{
  Serial.begin(115200);
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
  Serial.println("LoRa Initial OK!");
  LoRa.setSyncWord(0x6D)
  LoRa.receive();
}

void loop()
{
  int packetSize = LoRa.parsePacket();
  if (packetSize > 0)
  {
    Serial.print("Received: ");
    while (LoRa.available())
    {
      Serial.print((char)LoRa.read());
    }
    Serial.print("  RSSI=");
    Serial.println(LoRa.packetRssi());
    LoRa.receive();
  }
}

#include <Servo.h>
#define PIN_SERVO 5

Servo myservo;
int H = 100;

void setup()
{
  Serial.begin(9600);
  myservo.attach(PIN_SERVO);
}

void loop()
{
  if (H >= 400)
  {
    Serial.println("Starting Servo");
    myservo.write(180);
  }
  delay(1000);
}
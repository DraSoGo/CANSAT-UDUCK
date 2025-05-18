#include <Servo.h>
#define PIN_SERVO 9

Servo myservo;

void setup()
{
  Serial.begin(9600);
  myservo.attach(PIN_SERVO);
}

void loop()
{
  Serial.println("Starting Servo");
  myservo.write(180);
  delay(1000);
}
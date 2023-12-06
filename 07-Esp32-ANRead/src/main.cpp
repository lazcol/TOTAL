#include <Arduino.h>

void setup()
{
    Serial.begin(BAUD);
}

void loop()
{
    int temp=0;

    temp = analogRead(27);
    Serial.print("read: ");
    Serial.println(temp);
    delay(100);
}


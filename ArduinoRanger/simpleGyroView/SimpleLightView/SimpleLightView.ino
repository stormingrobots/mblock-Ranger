#include <Arduino.h>
#include <MeAuriga.h>

MeLightSensor lightsensor_12(12);

float see = 0;

void setup() {
    Serial.begin(9600);
}

void loop() {
  see = lightsensor_12.read();
  Serial.print("See: ");
  Serial.println(see);
  delay(500);
}



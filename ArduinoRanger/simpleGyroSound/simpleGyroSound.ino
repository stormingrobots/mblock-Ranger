#include <Arduino.h>
#include <MeAuriga.h>

MeSoundSensor soundsensor_14(14);
float loud = 0;

void setup() {
}

void loop() {
  loud = soundsensor_14.strength();
  delay(.5);

  str =  "Loudness: " + String(loud);
  Serial.print(str);
}

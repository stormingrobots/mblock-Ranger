#include <Arduino.h>
#include <MeAuriga.h>

MeSoundSensor soundsensor_14(14);
float loud = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  String str;
  loud = soundsensor_14.strength();
  delay(500);

  str =  "Loudness: " + String(loud);
  Serial.println(str);
}


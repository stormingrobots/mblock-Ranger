// generated by mBlock5 for mBot Ranger
// codes make you happy

#include <Arduino.h>
#include <MeAuriga.h>

MeLightSensor lightsensor_12(12);         // init light sensor on D12
MeBuzzer buzzer;

void setup() {
  buzzer.setpin(45);
}

void loop() {
  float ls = lightsensor_12.read();       // read in the value    
  if (ls < 400) {                         // if dark then play a  tone
    buzzer.tone(262, 0.25 * 1000);
    delay(2);
  } else {
    buzzer.tone(110, 0.25 * 1000);        // else play a different
  }

}
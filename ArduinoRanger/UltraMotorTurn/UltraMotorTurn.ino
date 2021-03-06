#include <Arduino.h>
#include <MeAuriga.h>

MeEncoderOnBoard Encoder_1(SLOT1);
MeEncoderOnBoard Encoder_2(SLOT2);
MeUltrasonicSensor ultrasonic_10(10);

void initPWM8kHz() {
  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);
}

void setup() {
  initPWM8kHz();
  Encoder_1.setTarPWM(-40.0 / 100.0 * 255);
  Encoder_2.setTarPWM(40.0 / 100.0 * 255);
}

void loop() {
  Encoder_1.loop();
  Encoder_2.loop();

  if(ultrasonic_10.distanceCm() < 12){
    Encoder_1.setTarPWM(40.0 / 100.0 * 255);
    Encoder_2.setTarPWM(40.0 / 100.0 * 255); 
  } else {
    Encoder_1.setTarPWM(-40.0 / 100.0 * 255);
    Encoder_2.setTarPWM(40.0 / 100.0 * 255);
  }
}

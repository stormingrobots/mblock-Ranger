#include <Arduino.h>
#include <MeAuriga.h>

MeLineFollower linefollower_9(9);
MeEncoderOnBoard Encoder_1(SLOT1);
MeEncoderOnBoard Encoder_2(SLOT2);

#define LW_RW  S1_OUT_S2_OUT
#define LB_RW  S1_IN_S2_OUT
#define LW_RB  S1_OUT_S2_IN
#define LB_RB  S1_IN_S2_IN

void initPWM8kHz() {
  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);
}

void setup() {
  initPWM8kHz();
  Serial.begin(9600);
  Encoder_1.setTarPWM(-40.0 / 100.0 * 255);
  Encoder_2.setTarPWM(40.0 / 100.0 * 255);
}

void loop() {
  Encoder_1.loop();
  Encoder_2.loop();

  uint8_t line_value = linefollower_9.readSensors();
  /*
    readSensors() returns one of the following values:
    (0x00)-S1_IN_S2_IN: sensor1 and sensor2 are both inside of black line
    (0x01)-S1_IN_S2_OUT: sensor1 is inside of black line and sensor2 is outside of black line
    (0x02)-S1_OUT_S2_IN: sensor1 is outside of black line and sensor2 is inside of black line
    (0x03)-S1_OUT_S2_OUT: sensor1 and sensor2 are both outside of black line
  */
  char doing[50];

  switch (line_value) {
    case  LB_RB:                         // both sensors see black
      // Encoder_1.setTarPWM(-40.0 / 100.0 * 255);
      //Encoder_2.setTarPWM(-40.0 / 100.0 * 255);
      break;
    case LW_RB:                          // S1 sees white , S2 sees black
      Encoder_1.setTarPWM(0);
      Encoder_2.setTarPWM(40 / 100.0 * 255);
      strcpy(doing, "turning right!");
      break;
    case LB_RW:                          // S1 sees black , S2 sees white
      Encoder_1.setTarPWM(-40 / 100.0 * 255);
      Encoder_2.setTarPWM(0);
      strcpy(doing, "turning left!");
      break;
    case LW_RW:                         // both sensors see white
      Encoder_1.setTarPWM(40 / 100.0 * 255);
      Encoder_2.setTarPWM(40 / 100.0 * 255);
      strcpy(doing, "turning forwardt!");
      break;
  }
  Serial.println(doing);
}



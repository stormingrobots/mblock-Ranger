#include <Arduino.h>
#include <MeAuriga.h>

MeEncoderOnBoard RightMotor(SLOT1);            // RIGHT motor
MeEncoderOnBoard LeftMotor(SLOT2);            // LEFT motor

/*
 * Inits the PWM signal for motors to 8kHz
 */
void initPWM8kHz() {
  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);
}

/*
 * takes a percent, returns the value required for setTarPWM()
 */
double speedval(double percent){
  return percent / 100.0 * 255;
}

/*
 * It seems odd to write our own delay but the MeEncoderOnBoard DEMANDS 
 * that the motor loop functions NEVER BE BLOCKED (they need to always be called).
 * 
 * See http://learn.makeblock.com/en/Makeblock-library-for-Arduino/class_me_encoder_on_board.html#a40a21255f01a568dbdbdcbfe9236070c
 * for more information.
 */
void _delay(float seconds) {                    
  if(seconds < 0.0){
    seconds = 0.0;
  }
  
  long endTime = millis() + seconds * 1000;
  while(millis() < endTime) {                     // loop until we hit the time limit
    RightMotor.loop();                            // constantly call the loop functions
    LeftMotor.loop();
  }
}

void setup() {
  initPWM8kHz();                                // inits PWM to 8kHz
  RightMotor.setTarPWM(speedval(-50));          // runs right motor at 50% backwards (which means forwards for the robot)
  LeftMotor.setTarPWM(speedval(50));            // runs left motor 50% forwards.
}

void loop() {
  RightMotor.loop();                              // must always call loop (especially in loop())
  LeftMotor.loop();
  
  RightMotor.setTarPWM(speedval(-50));            // forwards
  LeftMotor.setTarPWM(speedval(50));
  _delay(5);

  RightMotor.setTarPWM(speedval(-50));            // left
  LeftMotor.setTarPWM(speedval(-50));
  _delay(5);

  RightMotor.setTarPWM(speedval(50));             // right
  LeftMotor.setTarPWM(speedval(50));
  _delay(5);

  RightMotor.setTarPWM(speedval(50));             // backwards
  LeftMotor.setTarPWM(speedval(-50));
  _delay(5);
 
}

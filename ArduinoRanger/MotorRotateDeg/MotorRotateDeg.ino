/*
 * This code simply runs forward for 5 seconds however it uses 
 * the encoders to keep the speeds of both motors the same (180 RPM)
 */

#include <Arduino.h>
#include <MeAuriga.h>

MeEncoderOnBoard RightMotor(SLOT1);            // RIGHT motor
MeEncoderOnBoard LeftMotor(SLOT2);             // LEFT motor

void isr_process_rightmotor(void)
{
  if(digitalRead(RightMotor.getPortB()) == 0){
    RightMotor.pulsePosMinus();
  }else{
    RightMotor.pulsePosPlus();
  }
}
void isr_process_leftmotor(void)
{
  if(digitalRead(LeftMotor.getPortB()) == 0){
    LeftMotor.pulsePosMinus();
  }else{
    LeftMotor.pulsePosPlus();
  }
}

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
  initPWM8kHz();                                  // inits PWM to 8kHz
  attachInterrupt(RightMotor.getIntNum(), 
    isr_process_rightmotor, 
    RISING);
  RightMotor.setPulse(9);
  RightMotor.setRatio(39.267);
  RightMotor.setPosPid(1.8,0,1.2);
  RightMotor.setSpeedPid(0.18,0,0);
  attachInterrupt(LeftMotor.getIntNum(), 
    isr_process_leftmotor, 
    RISING);
  LeftMotor.setPulse(9);
  LeftMotor.setRatio(39.267);
  LeftMotor.setPosPid(1.8,0,1.2);
  LeftMotor.setSpeedPid(0.18,0,0);
 
  double rotdeg = 3600;
  LeftMotor.move(-rotdeg,abs(180));
  RightMotor.move( rotdeg,abs(180));
}

void loop() {
  RightMotor.loop();                              // remember the loop methods for the motors can never be blocked
  LeftMotor.loop();
}

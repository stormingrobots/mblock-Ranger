
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeAuriga.h>

#define print(a,b)   prtLine(__LINE__, a, b)

MeEncoderOnBoard LMotor(SLOT2);
MeEncoderOnBoard RMotor(SLOT1);

enum eMotors {  rightMotor, leftMotor };
enum eDir { none, fwd, right, left, back };

long Enc[2] = {0};
long Pulse[2] = {0};

//-----------------------------------------------
// generic motor move routines
void move(eDir direction, int speed)
{
  int leftSpeed = 0;
  int rightSpeed = 0;
  speed = ((float)speed / 100.0) * 255;

  switch ( direction ) {
    case fwd :
      leftSpeed = -speed;
      rightSpeed = speed;
      break;
    case back:
      leftSpeed = speed;
      rightSpeed = -speed;
      break;
    case right:
      leftSpeed = -speed;
      rightSpeed = -speed;
      break;
    case left:
      leftSpeed = speed;
      rightSpeed = speed;
      break;
  }
  LMotor.setTarPWM(leftSpeed);
  RMotor.setTarPWM(rightSpeed);
}

//-----------------------------------------------
// enforce internal motor structure update
// by calling motor.loop() <- NOT the same as the loop() for arduino
// motor  

void _delay(float seconds) {
  if (seconds < 0.0) {
    seconds = 0.0;
  }
  long endTime = millis() + seconds * 1000;
  while (millis() < endTime) {
    RMotor.loop();
    LMotor.loop();
  }
}


//-----------------------------------------------
// customized printing function
void prtLine(int nline, const char *name, long val = 0) {
  char line[80] = {0};
  sprintf(line, "(%d) %s: %ld", nline, name, val);
  Serial.println(line);
}

//---------------------------------------------------------
// reset the encoder value to 0. 
void resetEncoder() {
  RMotor.setPulsePos(0);
  LMotor.setPulsePos(0);
}

//---------------------------------------------------------
void stopMoving() {
  LMotor.setTarPWM(0);
  RMotor.setTarPWM(0);
  _delay(0.5); // to delay and update the motor data
}

//*********************************************************
//*********************************************************

//-----------------------------------------------
//important: do not change these interrupt service routines...

// motor interrupt service routines
void isr_LMotorEncoder(void)
{
  if (digitalRead(LMotor.getPortB()) == 0) {
    LMotor.pulsePosMinus();
  } else {
    LMotor.pulsePosPlus();
  }
}

void isr_RMotorEncoder(void)
{
  if (digitalRead(RMotor.getPortB()) == 0) {
    RMotor.pulsePosMinus();
  } else {
    RMotor.pulsePosPlus();
  }
}


//-----------------------------------------------
void setup() {
  // motor setup---------------------------
  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);

  // motor Encoder interrupt setup---------------------------
  attachInterrupt(LMotor.getIntNum(), isr_LMotorEncoder, RISING);
  attachInterrupt(RMotor.getIntNum(), isr_RMotorEncoder, RISING);
  //randomSeed((unsigned long)(lightsensor_12.read() * 123456));

  Serial.begin(9600);

  print("\n====Time: ", millis());
  resetEncoder();
}

//*********************************************************

//-------------------------------------
// will run for 5 wheels rotations
// Continuously display the encoder value

void loop() {

  Enc[rightMotor] = 0;
  RMotor.loop();
  LMotor.loop();

  print( "----------------", 0);
  do
  {
    RMotor.loop();  // update the motor data
    LMotor.loop();
    move(fwd, 30);  // should test out for various speed to check out the overshooting
    Enc[rightMotor] = RMotor.getCurPos();
    Pulse[rightMotor] = RMotor.getPulsePos();

  } while (Enc[rightMotor] < 3600);
  
  stopMoving();
  print( "---------stop", 0);
  print( "Pulse: ", Pulse[rightMotor]);
  print( "Enc: ", Enc[rightMotor]);
  delay(1500);  // allow the motor to come to a full stop
  print( "---------overshoot", 1);
  int diffpos = RMotor.getCurPos() - Enc[rightMotor];
  int diffpulse = RMotor.getPulsePos() - Pulse[rightMotor];
  print( "O-Pulse: ", diffpos);
  print( "O-Enc", diffpulse);
  resetEncoder();
}

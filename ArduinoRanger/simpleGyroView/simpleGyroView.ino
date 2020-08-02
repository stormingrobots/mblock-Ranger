
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeAuriga.h>

MeGyro gyro_0(0, 0x69);

const int X = 1;
const int Y = 2;
const int Z = 2;

void setup() {
  Serial.begin(9600);
  gyro_0.begin();
}

void loop() {
  float x = 0;
  float y = 0;
  float z = 0;
  String str;
  
  gyro_0.update();

  x = gyro_0.getAngle(X);
  y = gyro_0.getAngle(Y);
  z = gyro_0.getAngle(Z);

//Serial.sprintf(str, "X=%.2f;  Y=%.2f; Z=%.2f", x, y, z);
  str =  "X = " + String(x) + "; Y= " + String(y) + "; Z=" + String(z);
  Serial.print(str);
  Serial.println(x );
}

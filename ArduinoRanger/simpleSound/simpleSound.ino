
#include <Arduino.h>
#include <MeAuriga.h>

MeGyro gyro_0(0, 0x69);
MeLightSensor lightsensor_12(12);

const int X = 1;
const int Y = 2;
const int Z = 2;


void setup() {
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

  Serial.sprintf(str, "X=%.2f;  Y=%.2f; Z=%.2f", x, y, z);
  Serial.print(str);
  Serial.println(x );
}

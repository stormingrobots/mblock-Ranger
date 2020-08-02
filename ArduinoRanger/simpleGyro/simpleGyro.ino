/*
 * Always shine LED light in direction of origin 
 * Run it and then spin it on it's Z axis
 */
#include <Arduino.h>
#include <Wire.h>
#include <MeAuriga.h>

MeGyro gyro_0(0, 0x69);      
// Init Gyro i2c addr 0x69
void setup() {
  gyro_0.begin();                                         // init gyro for reading
} 

void loop() {
  gyro_0.update();                                        // get the gyro value into internal buffer
  double z_rotation = gyro_0.getAngleZ();                 // read in the Z axis angle in degrees
  print("Gyro Read: ");
  print(z_rotation);
}

/*
 * Always shine LED light in direction of origin 
 * Run it and then spin it on it's Z axis
 */
#include <Arduino.h>
#include <Wire.h>
#include <MeAuriga.h>

MeGyro gyro_0(0, 0x69);                                 // Init Gyro i2c addr 0x69
MeRGBLed rgbled_0(0, 12);                               // init 12 pixel leds

const double deg_per_light = 360 / 12;                  // 30 degrees per light
/*
 * takes the angle and returns which light should shine.  
 * led 3 is in 0 position, led 9 is 180
 * angles 0 -> -180  maps to leds 3 -> 9
 * angles 0 ->  180  maps to leds 2,1,12->9
 * SO... we need to do some crazy stuff to calc it right.
 */
int DetermineLight (double angle) {
  int shine = 0;
  
  if (angle < 0) {                                        // we turned left
    shine = round(((3 + abs(angle) / deg_per_light)));    // simple map to leds 3 - 9
  } else {                                                // else we turned right
    shine = round(((3 - abs(angle) / deg_per_light)));    // so we subtract from 3 the angle/30 
    if (shine < 1) {                                      // if we are less than 1, 
      shine = shine + 12;                                 // remap to 12 -> 9 by adding 12
    }
  }
  return shine;
}

void setup() {
  gyro_0.begin();                                         // init gyro for reading
  rgbled_0.setpin(44);                                    // rgbled to pin D44
} 

void loop() {
  static int old_shine = 0;                               // this is the old led value
  gyro_0.update();                                        // get the gyro value into internal buffer
  double z_rotation = gyro_0.getAngleZ();                 // read in the Z axis angle in degrees
  int shine = DetermineLight(z_rotation);                 // get which LED to shine
  if (shine != old_shine) {                               // If new led then 
    rgbled_0.setColor(old_shine, 0, 0, 0);                //   unshine old value
    rgbled_0.setColor(shine, 255, 0, 0);                  //   shine new value RED
    rgbled_0.show();                                      //   update RGB LED display
  }
}

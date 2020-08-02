#include <Arduino.h>
#include <MeAuriga.h>

MeRGBLed rgbled_0(0, 12);                           // Create RGBLed Object (0-12 lights)

void setup() {
  Serial.begin(9600);                   
  rgbled_0.setpin(44);                              // init rgbled on pin 44
}

void loop() {
    rgbled_0.setColor(1, 255, 0, 0);                // set Pix light #1 to RED
    rgbled_0.show();
    delay(1000);
    rgbled_0.setColor(1, 0, 0, 255);                // set Pix light #1 to BLUE
    rgbled_0.show();
    delay(1000);
}



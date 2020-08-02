#include <Arduino.h>
#include <MeAuriga.h>

MeOnBoardTemp onboard_temp(PORT_13);                // Create Temp Sensor Object
MeRGBLed rgbled_0(0, 12);                           // Create RGBLed Object (0-12 lights)

void setup() {
  Serial.begin(9600);                   
  rgbled_0.setpin(44);                              // init rgbled on pin 44
}

void loop() {
  float temperature = 0;
  temperature = onboard_temp.readValue();           // get temp
  Serial.println(temperature);      
  if (temperature > 25) {                           
    rgbled_0.setColor(1, 255, 0, 0);                // set Pix light #1 to RED
    rgbled_0.show();
  } else {
    rgbled_0.setColor(1, 0, 0, 255);                // set Pix light #1 to BLUE
    rgbled_0.show();
  }
  delay(1000);
}

#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <SmartLightBulbLibrary.h> // Replace with your home automation library

/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_600MS, TCS34725_GAIN_1X);

SmartLightBulb bulb; // Replace with your smart light bulb instance

void setup(void) {
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  // Initialize your smart light bulb here
  bulb.begin();
}

void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux;
  r = 255;   // Set maximum intensity for red
  g = 0;     // Set no intensity for green
  b = 0;     // Set no intensity for blue

  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

  // Adjust your home automation actions based on color readings
  if (colorTemp > 5000) {
    // If color temperature is higher than 5000K (cool white), turn on the light
    bulb.turnOn();
  } else {
    // If color temperature is lower than or equal to 5000K (warm white), turn off the light
    bulb.turnOff();
  }

  // Print color readings to serial monitor
  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");
  
  delay(1000); // Delay for 1 second before taking the next reading
}

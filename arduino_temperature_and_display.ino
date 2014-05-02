// Do not remove the include below
#include "arduino_temperature_and_display.h"

#include <SPI.h>
#include <SPI7Segment.h>

const int temperature_pin = 0;
const float voltage_factor = (float)3300/(float)1024;

//The setup function is called once at startup of the sketch
void setup() {
  analogReference(EXTERNAL);
  Serial.begin(9600);

  SPI.begin(); //Start the SPI hardware
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV64); //Slow down the master 1/64

  SPI7Segment.command(0x7A, 0x80); // brightness setup (will wear out the flash or eeprom with every write).
  //Send the reset command to the display - this forces the cursor to return to the beginning of the display
  SPI7Segment.command('v', ' '); //Reset command
  delay(3000); // wait for initialization
}

// The loop function is called in an endless loop
void loop() {
  int voltage = analogRead(temperature_pin);

  float millivolts = voltage * voltage_factor;
  Serial.print("millivolts: ");
  Serial.println(millivolts);

  Serial.print("temperature: ");
  Serial.println((millivolts - 500 )/10, 6); // Offset of 500mV at 0 (750mV at 25, from table).
  SPI7Segment.command('v', ' '); //Reset command

  SPI7Segment.number(int((millivolts - 500 )/10), 10);
  delay(5000);
}

/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/library/led/example/arduino-led-blink

   This example blinks LED:
     + blink led
     + without using delay() function. This is a non-blocking example
*/

#include <ezLED.h> // ezLED library

ezLED led(9);  // create a LED object that attach to pin 9

void setup() {
  Serial.begin(9600);
  led.blink(250, 750);         // 250ms ON, 750ms OFF, blink immediately
  //led.blink(250, 750, 1000); // 250ms ON, 750ms OFF, blink after 1 second
}

void loop() {
  led.loop(); // MUST call the led.loop() function in loop()

  if (led.getState() == LED_BLINKING)
    Serial.println("BLINKING");
  else if (led.getState() == LED_IDLE)
    Serial.println("BLINK ENDED");

  // To stop blinking immediately, call led.cancel() function
}
/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/library/led/example/arduino-led-fade-in-fade-out

   This example fade LED:
     + fade in LED in 3 seconds
     + fade out LED in 3 seconds
     + without using delay() function. This is a non-blocking example
*/

#include <ezLED.h> // ezLED library

ezLED led(9);  // create a LED object that attach to pin 9
bool isFadedIn = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  led.loop(); // MUST call the led1.loop() function in loop()

  if (led.getState() == LED_IDLE) {
    if (isFadedIn == false) {
      Serial.println("FADING IN");
      led.fade(0, 255, 3000);         // fade in from 0 to 255 in 3000ms, fade immediately
      //led.fade(0, 255, 3000, 1000); // fade in from 0 to 255 in 3000ms, fade after 1 second
      isFadedIn = true;
    } else {
      Serial.println("FADING OUT");
      led.fade(255, 0, 3000);          // fade out from 255 to 0 in 3000ms, fade immediately
      //led.fade(255, 0, 3000, 1000);  // fade out from 255 to 0 in 3000ms, fade after 1 second
      isFadedIn = false;
    }
  }

  // To stop fading immediately, call led.cancel() function
}
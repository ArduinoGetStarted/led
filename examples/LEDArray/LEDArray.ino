/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/library/led/example/arduino-led-array

   This example blinks 3 LED:
   + blink one LED forever
   + blink one LED in 5 seconds
   + blink one LED in 10 times
   + without using delay() function. This is a non-blocking example
*/

#include <ezLED.h> // ezLED library

#define NUM_LED 3 // three LEDs

#define PIN_LED_1 7
#define PIN_LED_2 8
#define PIN_LED_3 9

ezLED ledArray[NUM_LED] = {
  ezLED(PIN_LED_1),  // create ezLED object that attach to pin PIN_LED_1
  ezLED(PIN_LED_2),  // create ezLED object that attach to pin PIN_LED_2
  ezLED(PIN_LED_3)   // create ezLED object that attach to pin PIN_LED_3
};

void setup() {
  Serial.begin(9600);

  ledArray[0].blink(500, 500);                  // 500ms ON, 500ms OFF, blink immediately
  ledArray[1].blinkInPeriod(100, 100, 5000);    // 100ms ON, 100ms OFF, blink in 5 seconds, blink immediately
  ledArray[2].blinkNumberOfTimes(250, 750, 10); // 250ms ON, 750ms OFF, repeat 10 times, blink immediately
}

void loop() {
  for (int i = 0; i < NUM_LED; i++)
    ledArray[i].loop(); // MUST call the led.loop() function in loop()

  // print the operation state
  for (int i = 0; i < NUM_LED; i++) {
    Serial.print("LED ");
    Serial.print(i + 1);

    if (ledArray[i].getState() == LED_DELAY)
      Serial.println(" DELAYING");
    else if (ledArray[i].getState() == LED_BLINKING)
      Serial.println(" BLINKING");
    else if (ledArray[i].getState() == LED_IDLE)
      Serial.println(" BLINK ENDED");
  }

  // DO SOMETHING HERE
}
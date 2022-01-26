/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/library/led/example/arduino-multiple-led

   This example blinks 3 LED:
   + with different blink time
   + blink one LED forever
   + blink one LED in 5 seconds
   + blink one LED in 10 times
   + without using delay() function. This is a non-blocking example
*/

#include <ezLED.h> // ezLED library

#define PIN_LED_1 7
#define PIN_LED_2 8
#define PIN_LED_3 9

ezLED led1(PIN_LED_1);  // create ezLED object that attach to pin PIN_LED_1
ezLED led2(PIN_LED_2);  // create ezLED object that attach to pin PIN_LED_2
ezLED led3(PIN_LED_3);  // create ezLED object that attach to pin PIN_LED_3

void setup() {
  Serial.begin(9600);

  led1.blink(500, 500); // 500ms ON, 500ms OFF, blink immediately
  led2.blinkInPeriod(100, 100, 5000); // 100ms ON, 100ms OFF, blink in 5 seconds, blink immediately
  led3.blinkNumberOfTimes(250, 750, 10); // 250ms ON, 750ms OFF, repeat 10 times, blink immediately
}

void loop() {
  led1.loop(); // MUST call the led1.loop() function in loop()
  led2.loop(); // MUST call the led2.loop() function in loop()
  led3.loop(); // MUST call the led3.loop() function in loop()

  Serial.print("LED 1");
  printState(led1.getState());

  Serial.print("LED 2");
  printState(led2.getState());

  Serial.print("LED 3");
  printState(led3.getState());

  // DO SOMETHING HERE
}

void printState(int state) {
  if (state == LED_DELAY)
    Serial.println(" DELAYING");
  else if (state == LED_BLINKING)
    Serial.println(" BLINKING");
  else if (state == LED_IDLE)
    Serial.println(" BLINK ENDED");
}
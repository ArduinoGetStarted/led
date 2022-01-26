/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/library/led/example/arduino-led-on-off

   This example turn ON/OFF led according to state of button.
*/

#include <ezLED.h> // ezLED library

#define BUTTON_PIN 7

ezLED led(3);  // create a LED object that attach to pin 3

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  led.loop(); // MUST call the led.loop() function in loop()

  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW) {
    led.turnON();       // turn on immediately
    //led.turnON(1000); // turn on after 1 second
  } else {
    led.turnOFF();       // turn off immediately
    //led.turnOFF(1000); // turn off after 1 second
  }

  if (led.getOnOff() == LED_ON)
    Serial.println("LED is ON");
  else
    Serial.println("LED is OFF");
}
/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/library/led/example/arduino-led-toggle

   This example turn ON/OFF led according to state of button.
*/

#include <ezButton.h> // ezButton library https://arduinogetstarted.com/tutorials/arduino-button-library
#include <ezLED.h> // ezLED library

ezButton button(7); // create a button object that attach to pin 7
ezLED led(3);       // create a LED object that attach to pin 3

void setup() {
  Serial.begin(9600);
  button.setDebounceTime(50); // set debounce time to 50ms
}

void loop() {
  button.loop(); // MUST call the loop() function first
  led.loop(); // MUST call the loop() function first

  if (button.isPressed()) {
    led.toggle(); // toggle immediately
    //led.toggle(1000); // toggle after 1 second
  }

  if (led.getOnOff() == LED_ON)
    Serial.println("LED is ON");
  else
    Serial.println("LED is OFF");
}
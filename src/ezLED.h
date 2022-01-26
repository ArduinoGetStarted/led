/*
 * Copyright (c) 2021, ArduinoGetStarted.com. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * - Neither the name of the ArduinoGetStarted.com nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ARDUINOGETSTARTED.COM "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ARDUINOGETSTARTED.COM BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ezLED_h
#define ezLED_h

#include <Arduino.h>

#define LED_OFF 0
#define LED_ON  1

#define LED_IDLE     0
#define LED_DELAY    1
#define LED_FADING   2
#define LED_BLINKING 3

#define CTRL_ANODE   0
#define CTRL_CATHODE 1

#define LED_MODE_OFF            0
#define LED_MODE_ON             1
#define LED_MODE_TOGGLE         2
#define LED_MODE_FADE           3
#define LED_MODE_BLINK_FOREVER  4
#define LED_MODE_BLINK_PERIOD   5
#define LED_MODE_BLINK_NUM_TIME 6

#define LED_STATE_IDLE   0
#define LED_STATE_DELAY  1
#define LED_STATE_ON_OFF 2
#define LED_STATE_FADE   3
#define LED_STATE_BLINK  4

class ezLED
{
	private:
		int _ledPin;
		unsigned char _ctrlMode; // CTRL_ANODE, CTRL_CATHODE
		unsigned char _ledMode;
		unsigned char _ledState;
		unsigned char _outputState; // LED_OFF, LED_ON
		int _brightness;  // 0 to 255

		unsigned char _fadeFrom = 0;
		unsigned char _fadeTo = 0;
		unsigned long _fadeTime;
		unsigned long _blinkOnTime;
		unsigned long _blinkOffTime;
		unsigned long _blinkTimePeriod;
		unsigned int  _blinkNumberOfTimes;
		unsigned long _delayTime;
		unsigned long _lastTime;
		unsigned long _blinkTimer;
		unsigned int  _blinkCounter;

		void setBlink(unsigned long onTime, unsigned long offTime, unsigned long delayTime);
		void updateAnalog();
		void updateDigital();

	public:
		ezLED(int pin, int mode = CTRL_ANODE);
		void turnON(unsigned long delayTime = 0);
		void turnOFF(unsigned long delayTime = 0);
		void toggle(unsigned long delayTime = 0);

		void fade(int fadeFrom, int fadeTo, unsigned long fadeTime, unsigned long delayTime = 0);

		void blink(unsigned long onTime, unsigned long offTime, unsigned long delayTime = 0);
		void blinkInPeriod(unsigned long onTime, unsigned long offTime, unsigned long blinkTime, unsigned long delayTime = 0);
		void blinkNumberOfTimes(unsigned long onTime, unsigned long offTime, unsigned int numberOfTimes, unsigned long delayTime = 0);

		void cancel(void);

		int getOnOff(void);
		int getState(void);
		void loop(void);
};

#endif

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

#include <ezLED.h>

ezLED::ezLED(int pin, int mode) {
	_ledPin      = pin;
	_ctrlMode    = mode; // CTRL_ANODE, CTRL_CATHODE
	_ledMode     = LED_MODE_OFF;
	_ledState    = LED_STATE_IDLE;
	_outputState = LED_OFF; // LED_OFF, LED_ON
	_brightness  = 0;  // 0 to 255

	_fadeFrom           = 0;
	_fadeTo             = 0;
	_fadeTime           = 0;
	_blinkOnTime        = 0;
	_blinkOffTime       = 0;
	_blinkTimePeriod    = 0;
	_blinkNumberOfTimes = 0;
	_delayTime          = 0;
	_lastTime           = 0;
	_blinkTimer         = 0;
	_blinkCounter       = 0;

	pinMode(_ledPin, OUTPUT);
}

void ezLED::setBlink(unsigned long onTime, unsigned long offTime, unsigned long delayTime) {
	_blinkOnTime  = onTime;
	_blinkOffTime = offTime;
	_delayTime    = delayTime;
	_lastTime     = millis();
}

void ezLED::updateAnalog() {
	if(_ctrlMode == CTRL_ANODE)
		analogWrite(_ledPin, _brightness);
	else
		analogWrite(_ledPin, 255 - _brightness);
}

void ezLED::updateDigital() {
	int state;
	if(_ctrlMode == CTRL_ANODE)
		state = (_outputState == LED_OFF) ? LOW : HIGH;
	else
		state = (_outputState == LED_OFF) ? HIGH : LOW;

	digitalWrite(_ledPin, state);
}

void ezLED::turnON(unsigned long delayTime) {
	_delayTime = delayTime;
	_ledMode   = LED_MODE_ON;

	if(delayTime > 0) {
		_ledState  = LED_STATE_DELAY;
		_lastTime  = millis(); 
	} else {
		_ledState = LED_STATE_ON_OFF;
	}

	loop();
}

void ezLED::turnOFF(unsigned long delayTime) {
	_delayTime = delayTime;
	_ledMode   = LED_MODE_OFF;

	if(delayTime > 0) {
		_ledState  = LED_STATE_DELAY;
		_lastTime  = millis(); 
	} else {
		_ledState = LED_STATE_ON_OFF;
	}

	loop();
}

void ezLED::toggle(unsigned long delayTime) {
	_delayTime = delayTime;
	_ledMode   = LED_MODE_TOGGLE;

	if(delayTime > 0) {
		_ledState  = LED_STATE_DELAY;
		_lastTime  = millis(); 
	} else {
		_ledState = LED_STATE_ON_OFF;
	}

	loop();

}


void ezLED::fade(int fadeFrom, int fadeTo, unsigned long fadeTime, unsigned long delayTime) {
	_fadeFrom  = fadeFrom;
	_fadeTo    = fadeTo;
	_fadeTime  = fadeTime;
	_delayTime = delayTime;
	_ledMode   = LED_MODE_FADE;
	_lastTime  = millis();

	if(delayTime > 0)
		_ledState  = LED_STATE_DELAY;
	else
		_ledState = LED_STATE_FADE;

	loop();
}

void ezLED::blink(unsigned long onTime, unsigned long offTime, unsigned long delayTime) {
	setBlink(onTime, offTime, delayTime);
	_ledMode      = LED_MODE_BLINK_FOREVER;

	if(_ledState == LED_STATE_IDLE) {
		if(delayTime > 0)
			_ledState  = LED_STATE_DELAY;
		else {
			_ledState = LED_STATE_BLINK;

			_outputState = LED_ON;
			_lastTime = millis();
		}
	}

	loop();
}

void ezLED::blinkInPeriod(unsigned long onTime, unsigned long offTime, unsigned long blinkTime, unsigned long delayTime) {
	setBlink(onTime, offTime, delayTime);
	_blinkTimePeriod = blinkTime;
	_ledMode   = LED_MODE_BLINK_PERIOD;

	if(_ledState == LED_STATE_IDLE) {
		if(delayTime > 0)
			_ledState  = LED_STATE_DELAY;
		else {
			_ledState = LED_STATE_BLINK;

			_outputState = LED_ON;
			_lastTime = millis();
			_blinkTimer = millis();
		}
	}

	loop();
}

void ezLED::blinkNumberOfTimes(unsigned long onTime, unsigned long offTime, unsigned int numberOfTimes, unsigned long delayTime) {
	setBlink(onTime, offTime, delayTime);
	_blinkNumberOfTimes = numberOfTimes;
	_ledMode   = LED_MODE_BLINK_NUM_TIME;

	if(_ledState == LED_STATE_IDLE) {
		if(delayTime > 0)
			_ledState  = LED_STATE_DELAY;
		else {
			_ledState = LED_STATE_BLINK;

			_outputState = LED_ON;
			_lastTime = millis();
			_blinkCounter = 1;
		}
	}

	loop();
}

void ezLED::cancel(void) {
	turnOFF();
}

int ezLED::getOnOff(void) {
	return _outputState;
}

int ezLED::getState(void) {
	switch(_ledState) {
		case LED_STATE_DELAY:
			return LED_DELAY;

		case LED_STATE_FADE:
			return LED_FADING;

		case LED_STATE_BLINK:
			return LED_BLINKING;

		default:
			return LED_IDLE;
	}
}

void ezLED::loop(void) {

	switch(_ledState) {
		case LED_STATE_IDLE:
			return;

		case LED_STATE_DELAY:
			if ((unsigned long)(millis() - _lastTime) >= _delayTime) {
				switch(_ledMode) {
					case LED_MODE_OFF:
					case LED_MODE_ON:
					case LED_MODE_TOGGLE:
						_ledState = LED_STATE_ON_OFF;
						break;

					case LED_MODE_FADE:
						_ledState = LED_STATE_FADE;
						break;

					case LED_MODE_BLINK_FOREVER:
					case LED_MODE_BLINK_PERIOD:
					case LED_MODE_BLINK_NUM_TIME:
						_ledState = LED_STATE_BLINK;
						_outputState = LED_ON;
						break;
				}

				_lastTime = millis();
			}

			break;

		case LED_STATE_ON_OFF:
			switch(_ledMode) {
				case LED_MODE_OFF:
					_outputState = LED_OFF;
					break;
				case LED_MODE_ON:
					_outputState = LED_ON;
					break;
				case LED_MODE_TOGGLE:
					_outputState = (_outputState == LED_ON) ? LED_OFF : LED_ON;
					break;
			}

			_ledState = LED_STATE_IDLE;
			break;

		case LED_STATE_FADE:
			if((millis() - _lastTime) <= _fadeTime) {
				unsigned long progress = millis() - _lastTime;
				_brightness = map(progress, 0, _fadeTime, _fadeFrom, _fadeTo);
			} else {
				_ledState = LED_STATE_IDLE;
				_outputState = LED_OFF;
			}
			break;

		case LED_STATE_BLINK:
			if(_outputState == LED_OFF && (unsigned long)(millis() - _lastTime) >= _blinkOffTime) {
				_outputState = LED_ON;
				_lastTime = millis();
				_blinkCounter++;
			} else if(_outputState == LED_ON && (unsigned long)(millis() - _lastTime) >= _blinkOnTime) {
				_outputState = LED_OFF;
				_lastTime = millis();
				_blinkCounter++;
			}

			switch(_ledMode) {
				case LED_MODE_BLINK_FOREVER:
					break;

				case LED_MODE_BLINK_PERIOD:
					if((unsigned long)(millis() -_blinkTimer) >= _blinkTimePeriod) {
						_outputState = LED_OFF;
						_ledState = LED_STATE_IDLE;
					}
					break;

				case LED_MODE_BLINK_NUM_TIME:
					if(_blinkCounter >= (2 * _blinkNumberOfTimes)) {
						_outputState = LED_OFF;
						_ledState = LED_STATE_IDLE;
					}
					break;
			}
			break;

		default:
			Serial.println(F("UNKNOW STATE"));
	}

	if(_ledState == LED_STATE_FADE)
		updateAnalog();
	else
		updateDigital();
}

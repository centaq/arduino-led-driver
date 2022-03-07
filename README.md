# arduino-led-driver
PWM LED Driver with ability to brighten and dimm fluently.

## Requirements
### Hardware
Library uses hardware PWM pins, please be sure that you are providing correct ones.

### Software
For this library to work you need to also install:
- Timers - https://github.com/centaq/arduino-simple-timers

##Examples
###Simple example
	#include "LEDDriver.h"

	uint8_t outputs[] = { 2, 3};
	LEDDriver ledDriver(outputs, 2);
	  
	void setup() {
	  ledDriver.init();
	  
	  ledDriver.set(1, 20000, 50);
	}

	void loop() {
	  ledDriver.process();
	}

As you can see this example is as straight-forward as it can be.
After providing which PWM outputs you want to use in the class constructor and initialization you can set proper channel.
To do so you have to specify channel number (starting from 1), time to achieve the goal power value (in ms) and power value (in %).

You have to remember about `process` function in your application loop.
	
### Full example
	#include "LEDDriver.h"

	uint8_t outputs[] = { 2, 3};
	LEDDriver ledDriver(outputs, 2);

	void logger(char *msg) {
	  Serial.println(msg);
	}

	void setup() {
	  ledDriver.init();
	  ledDriver.logger = *logger;
	  
	  ledDriver.set(1, 20000, 50);
	}

	void loop() {
	  ledDriver.process();
	  uint8_t currentChannelPower = ledDriver.getChannelValue(1);
	}
	
Additional function to be used are ability to read current channel power value and logging all of the library logs.

## Limitations
1. Maximum number of PWM channels library can handle is set to 20. But it can be easily changed in the library header file.
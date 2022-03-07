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

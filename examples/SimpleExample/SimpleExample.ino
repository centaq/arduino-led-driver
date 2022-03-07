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

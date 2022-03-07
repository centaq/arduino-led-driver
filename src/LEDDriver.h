#ifndef _LEDDriver_h
#define _LEDDriver_h

#include "Arduino.h"
#include "Timers.h"

#define MAX_LED_CHANNELS 12

class LEDDriver {
  private:
    uint8_t _lastTime;
    uint16_t _waitTime[MAX_LED_CHANNELS];
    uint8_t _startValue[MAX_LED_CHANNELS];
    uint8_t _destValue[MAX_LED_CHANNELS];
    double _currValue[MAX_LED_CHANNELS];
    uint8_t _currValueInt[MAX_LED_CHANNELS];
    uint8_t _outputs[MAX_LED_CHANNELS];
    uint8_t _activeOutputsCount;
    
    void log(char *msg);
    void log(String msg);
  public:
    LEDDriver(uint8_t *outputs, uint8_t count);
    void init();
    void process();
    void set(uint8_t channel, uint16_t waitTime, uint8_t value);
    uint8_t getChannelValue(uint8_t channel);
    void (*logger)(char *msg);
};
#endif

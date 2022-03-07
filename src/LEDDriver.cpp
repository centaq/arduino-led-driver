
#include "LEDDriver.h"

LEDDriver::LEDDriver(uint8_t *outputs, uint8_t count) {
  uint8_t i = 0;
  for (; i < count && i < MAX_LED_CHANNELS; i++) {
    _outputs[i] = outputs[i];
  }
  _activeOutputsCount = i;
}

void LEDDriver::init() {
  for (uint8_t i = 0; i < _activeOutputsCount; i++) {
    pinMode(_outputs[i], OUTPUT);
    analogWrite(_outputs[i], 0);
  }
  log("LEDDriver init OK");
  _lastTime = millis();
}

void LEDDriver::process() {
  unsigned long checkPeriod = 1;
  double allowedDoubleError = 0.0001;
  if (millis() - _lastTime > checkPeriod) {
    for (uint8_t i=0; i < _activeOutputsCount; i++) {
      if (_currValueInt[i] != _destValue[i]) {
        uint8_t setValue = 0;
        if (_waitTime[i] == 0) {
          setValue = _destValue[i];
        } else {
          if (_currValueInt[i] > _destValue[i]) {
            double changeStep = (double)(_startValue[i] - _destValue[i]) / (double)_waitTime[i] * checkPeriod;
            _currValue[i] = _currValue[i] - changeStep;
            setValue = max(_destValue[i], ceil(_currValue[i] - allowedDoubleError));
          } else {
            double changeStep = (double)(_destValue[i] - _startValue[i]) / (double)_waitTime[i] * checkPeriod;
            _currValue[i] = _currValue[i] + changeStep;
            setValue = min(_destValue[i], floor(_currValue[i] + allowedDoubleError)); 
          }
          
          _currValueInt[i] = setValue;
          
          if (setValue == _destValue[i]) {
            _currValue[i] = _destValue[i];
          }
        }
        uint8_t range_min = min(_startValue[i], _destValue[i]);
        uint8_t range_max = max(_startValue[i], _destValue[i]);
        if (range_min <= setValue && setValue <= range_max) {
          analogWrite(i + 2, setValue);
        }
      }
    }
  }
}

void LEDDriver::set(uint8_t channel, uint16_t waitTime, uint8_t value) {
  if (channel == 0 || channel > _activeOutputsCount) {
    log("Incorrect channel no selected");
    return;
  }

  uint8_t ch = channel - 1;
  uint16_t waitTimeCalculated = 0;
  if (waitTime > 0) {
    if (_currValue[ch] == _destValue[ch]) {
      waitTimeCalculated = waitTime;
    } else {
      uint8_t diff = value;
      double factor = (double)value / (double)waitTime;
      if (_currValue[ch] > value) {
        diff = _currValue[ch] - value;
      } else {
        diff = value - _currValue[ch];
      }
      waitTimeCalculated = ceil(factor * (double)diff);
    }
  }
  
  _startValue[ch] = _currValue[ch];
  _destValue[ch] = value;
  _waitTime[ch] = waitTimeCalculated;
}

uint8_t LEDDriver::getChannelValue(uint8_t channel) {
  if (channel == 0 || channel > _activeOutputsCount) {
    log("Incorrect channel no selected");
    return 0;
  }
  
  return (uint8_t)_currValue;
}

void LEDDriver::log(char *msg) {
  if (logger)
    logger(msg);
}

void LEDDriver::log(String msg) {
  if (logger)
    logger(msg.c_str());
}

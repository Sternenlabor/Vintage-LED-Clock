#ifndef _LED_CLOCK_CTRL_H_
#define _LED_CLOCK_CTRL_H_

#include <Arduino.h>

class LedClockControl
{
public:
   LedClockControl();
   ~LedClockControl();
   void begin();
   void digitalClockDisplay();

private:
   void updateDigits(uint8_t uiHourHigh, uint8_t uiHourLow, uint8_t uiMinHigh, uint8_t uiMinLow);
};

struct stcPin
{
   uint8_t pin_number;  //!< GPIO id
   uint8_t pin_state;   //!< GPIO state HIGH/LOW
};

#endif /* _LED_CLOCK_CTRL_H_ */
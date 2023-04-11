#ifndef _LED_CLOCK_CTRL_H_
#define _LED_CLOCK_CTRL_H_

#include <Arduino.h>

class LedClockControl
{
public:
   LedClockControl(bool bEnableDimming = false, uint8_t uiBrigthnessPercent = 50);
   ~LedClockControl();
   void begin();
   void digitalClockDisplay();
   void setBrightness(uint8_t uiBrigthnessPercent);

private:
   void updateDigits(uint8_t uiHourHigh, uint8_t uiHourLow, uint8_t uiMinHigh, uint8_t uiMinLow);
   void selectPwmForIO(uint8_t uiPin, uint8_t uiState);
   bool m_bEnableDimming;
   uint8_t m_uiBrigthnessPercent;
};

struct stcPin
{
   uint8_t pin_number; //!< GPIO id
   uint8_t pin_state;  //!< GPIO state HIGH/LOW
};

#endif /* _LED_CLOCK_CTRL_H_ */
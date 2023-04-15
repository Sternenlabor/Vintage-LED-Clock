#ifndef _LED_CLOCK_CTRL_H_
#define _LED_CLOCK_CTRL_H_

#include <Arduino.h>

#define NUM_OUTPUTS_PER_DIGIT 5
#define CHARS_PER_DIGIT  11
#define SEGMENT_OFF 10


enum eDIGIT
{
   DIG_FIRST,
   DIG_HOUR_HIGH = DIG_FIRST,
   DIG_HOUR_LOW,
   DIG_MINUTE_HIGH,
   DIG_MINUTE_LOW,
   DIG_LAST
};

struct stcPin
{
   uint8_t pin_number; //!< GPIO id
   uint8_t pin_state;  //!< GPIO state HIGH/LOW
};

typedef stcPin digitPinMapping_t[NUM_OUTPUTS_PER_DIGIT];
typedef digitPinMapping_t charMapping_t[CHARS_PER_DIGIT];

struct stcDigitData
{
   uint8_t uiDigit;
   uint8_t uiPwmChannel;
   uint8_t uiBrightness;
   charMapping_t* pPinData;
};



class LedClockControl
{
public:
   LedClockControl(bool bEnableDimming = false, uint8_t uiBrigthnessPercent = 50);
   ~LedClockControl();
   void begin();
   void digitalClockDisplay();
   void setBrightnessAll(uint8_t uiBrigthnessPercent);
   void setBrightness(uint8_t uiHourHigh, uint8_t uiHourLow, uint8_t uiMinHigh, uint8_t uiMinLow);
   void updateDigits(uint8_t uiHourHigh, uint8_t uiHourLow, uint8_t uiMinHigh, uint8_t uiMinLow);

private:
   void selectPwmForDigit(eDIGIT eDig, uint8_t uiChar);
   bool m_bEnableDimming;
   stcDigitData m_stcDigitData[DIG_LAST];
};





#endif /* _LED_CLOCK_CTRL_H_ */
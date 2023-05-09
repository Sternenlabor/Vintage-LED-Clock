
#include "ledclockctrl.h"
#include "time.h"

enum PWM_LED_CHANNELS
{
   PWM_LED_CHANNEL_OFF,
   PWM_LED_CHANNEL_1,
   PWM_LED_CHANNEL_2,
   PWM_LED_CHANNEL_3,
   PWM_LED_CHANNEL_4
};

#define PWM_LED_FREQUENCY 1000 //!< frequency in Hz
#define PWM_LED_RESOLUTION 8   //!< PWM resolution in bits

stcPin g_stcPinConfHourHigh[CHARS_PER_DIGIT][NUM_OUTPUTS_PER_DIGIT] = {
    {{13, LOW},
     {0, LOW},
     {32, LOW},
     {33, LOW},
     {23, HIGH}},
    {{13, HIGH},
     {0, LOW},
     {32, LOW},
     {33, LOW},
     {23, HIGH}},
    {{13, LOW},
     {0, HIGH},
     {32, LOW},
     {33, LOW},
     {23, HIGH}},
    {{13, HIGH},
     {0, HIGH},
     {32, LOW},
     {33, LOW},
     {23, HIGH}},
    {{13, LOW},
     {0, LOW},
     {32, HIGH},
     {33, LOW},
     {23, HIGH}},
    {{13, HIGH},
     {0, LOW},
     {32, HIGH},
     {33, LOW},
     {23, HIGH}},
    {{13, LOW},
     {0, HIGH},
     {32, HIGH},
     {33, LOW},
     {23, HIGH}},
    {{13, HIGH},
     {0, HIGH},
     {32, HIGH},
     {33, LOW},
     {23, HIGH}},
    {{13, LOW},
     {0, LOW},
     {32, LOW},
     {33, HIGH},
     {23, HIGH}},
    {{13, HIGH},
     {0, LOW},
     {32, LOW},
     {33, HIGH},
     {23, HIGH}},
    {{13, LOW}, // 11 all off
     {0, LOW},
     {32, LOW},
     {33, LOW},
     {23, LOW}}};

stcPin g_stcPinConfHourLow[CHARS_PER_DIGIT][NUM_OUTPUTS_PER_DIGIT] = {
    {{22, LOW},
     {21, LOW},
     {19, LOW},
     {18, LOW},
     {5, HIGH}},
    {{22, HIGH},
     {21, LOW},
     {19, LOW},
     {18, LOW},
     {5, HIGH}},
    {{22, LOW},
     {21, HIGH},
     {19, LOW},
     {18, LOW},
     {5, HIGH}},
    {{22, HIGH},
     {21, HIGH},
     {19, LOW},
     {18, LOW},
     {5, HIGH}},
    {{22, LOW},
     {21, LOW},
     {19, HIGH},
     {18, LOW},
     {5, HIGH}},
    {{22, HIGH},
     {21, LOW},
     {19, HIGH},
     {18, LOW},
     {5, HIGH}},
    {{22, LOW},
     {21, HIGH},
     {19, HIGH},
     {18, LOW},
     {5, HIGH}},
    {{22, HIGH},
     {21, HIGH},
     {19, HIGH},
     {18, LOW},
     {5, HIGH}},
    {{22, LOW},
     {21, LOW},
     {19, LOW},
     {18, HIGH},
     {5, HIGH}},
    {{22, HIGH},
     {21, LOW},
     {19, LOW},
     {18, HIGH},
     {5, HIGH}},
    {{22, LOW}, // 11 all off
     {21, LOW},
     {19, LOW},
     {18, LOW},
     {5, LOW}}};

stcPin g_stcPinConfMinHigh[CHARS_PER_DIGIT][NUM_OUTPUTS_PER_DIGIT] = {
    {{17, LOW},
     {16, LOW},
     {4, LOW},
     {2, LOW},
     {15, HIGH}},
    {{17, HIGH},
     {16, LOW},
     {4, LOW},
     {2, LOW},
     {15, HIGH}},
    {{17, LOW},
     {16, HIGH},
     {4, LOW},
     {2, LOW},
     {15, HIGH}},
    {{17, HIGH},
     {16, HIGH},
     {4, LOW},
     {2, LOW},
     {15, HIGH}},
    {{17, LOW},
     {16, LOW},
     {4, HIGH},
     {2, LOW},
     {15, HIGH}},
    {{17, HIGH},
     {16, LOW},
     {4, HIGH},
     {2, LOW},
     {15, HIGH}},
    {{17, LOW},
     {16, HIGH},
     {4, HIGH},
     {2, LOW},
     {15, HIGH}},
    {{17, HIGH},
     {16, HIGH},
     {4, HIGH},
     {2, LOW},
     {15, HIGH}},
    {{17, LOW},
     {16, LOW},
     {4, LOW},
     {2, HIGH},
     {15, HIGH}},
    {{17, HIGH},
     {16, LOW},
     {4, LOW},
     {2, HIGH},
     {15, HIGH}},
    {{17, LOW}, // 11 all off
     {16, LOW},
     {4, LOW},
     {2, LOW},
     {15, LOW}}};

stcPin g_stcPinConfMinLow[CHARS_PER_DIGIT][NUM_OUTPUTS_PER_DIGIT] = {
    {{25, LOW},
     {26, LOW},
     {27, LOW},
     {12, LOW},
     {14, HIGH}},
    {{25, HIGH},
     {26, LOW},
     {27, LOW},
     {12, LOW},
     {14, HIGH}},
    {{25, LOW},
     {26, HIGH},
     {27, LOW},
     {12, LOW},
     {14, HIGH}},
    {{25, HIGH},
     {26, HIGH},
     {27, LOW},
     {12, LOW},
     {14, HIGH}},
    {{25, LOW},
     {26, LOW},
     {27, HIGH},
     {12, LOW},
     {14, HIGH}},
    {{25, HIGH},
     {26, LOW},
     {27, HIGH},
     {12, LOW},
     {14, HIGH}},
    {{25, LOW},
     {26, HIGH},
     {27, HIGH},
     {12, LOW},
     {14, HIGH}},
    {{25, HIGH},
     {26, HIGH},
     {27, HIGH},
     {12, LOW},
     {14, HIGH}},
    {{25, LOW},
     {26, LOW},
     {27, LOW},
     {12, HIGH},
     {14, HIGH}},
    {{25, HIGH},
     {26, LOW},
     {27, LOW},
     {12, HIGH},
     {14, HIGH}},
    {{25, LOW}, // 11 all off
     {26, LOW},
     {27, LOW},
     {12, LOW},
     {14, LOW}}};

LedClockControl::LedClockControl(bool bEnableDimming, uint8_t uiBrigthnessPercent) : m_bEnableDimming(bEnableDimming)
{
   // fill in default data
   for (uint8_t i = DIG_FIRST; i < DIG_LAST; i++)
   {
      m_stcDigitData[i].uiDigit = i;
      m_stcDigitData[i].uiPwmChannel = i + PWM_LED_CHANNEL_1;
      m_stcDigitData[i].uiBrightness = (255 / 100.0) * uiBrigthnessPercent;
   }

   // set pin data
   m_stcDigitData[DIG_HOUR_HIGH].pPinData = &g_stcPinConfHourHigh;
   m_stcDigitData[DIG_HOUR_LOW].pPinData = &g_stcPinConfHourLow;
   m_stcDigitData[DIG_MINUTE_HIGH].pPinData = &g_stcPinConfMinHigh;
   m_stcDigitData[DIG_MINUTE_LOW].pPinData = &g_stcPinConfMinLow;
}

LedClockControl::~LedClockControl()
{
   // nothing to do
}

void LedClockControl::begin()
{
   if (!m_bEnableDimming)
   {
      // no dimming init GPIOs as normal outputs
      for (uint8_t j = DIG_FIRST; j < DIG_LAST; j++)
      {
         for (uint8_t i = 0; i < NUM_OUTPUTS_PER_DIGIT; i++)
         {
            charMapping_t *pTmp = m_stcDigitData[j].pPinData;
            pinMode((*pTmp)[0][i].pin_number, OUTPUT);
         }
      }
   }
   else
   {
      ledcSetup(PWM_LED_CHANNEL_OFF, PWM_LED_FREQUENCY, PWM_LED_RESOLUTION);
      ledcWrite(PWM_LED_CHANNEL_OFF, 0);

      for (uint8_t j = DIG_FIRST; j < DIG_LAST; j++)
      {
         ledcSetup(m_stcDigitData[j].uiPwmChannel, PWM_LED_FREQUENCY, PWM_LED_RESOLUTION);
         ledcWrite(m_stcDigitData[j].uiPwmChannel, m_stcDigitData[j].uiBrightness);
      };
   }

   updateDigits(SEGMENT_OFF, SEGMENT_OFF, SEGMENT_OFF, SEGMENT_OFF);
}

void LedClockControl::digitalClockDisplay()
{
   struct tm timeinfo;
   if (!getLocalTime(&timeinfo))
   {
      Serial.println("Failed to obtain time");
      return;
   }

   char h[3];
   strftime(h, 3, "%H", &timeinfo);

   char m[3];
   strftime(m, 3, "%M", &timeinfo);

   int hours = String(h).toInt();
   int minutes = String(m).toInt();

   int temp = hours;   // Get the hours and save to variable temp
   int h1 = temp / 10; // Split hours into two digits, tens and units
   int h2 = temp % 10;
   temp = minutes;     // Get the minutes and save to variable temp
   int m1 = temp / 10; // Split minutes into two digits, tens and units
   int m2 = temp % 10;

   //Serial.println(String(h1) + "-" + String(h2) + ":" + String(m1) + "-" + String(m2));
   updateDigits(h1, h2, m1, m2);
}

void LedClockControl::updateDigits(uint8_t uiHourHigh, uint8_t uiHourLow, uint8_t uiMinHigh, uint8_t uiMinLow)
{

   if (!m_bEnableDimming)
   {
      // no dimming just set IOs
      for (uint8_t i = 0; i < NUM_OUTPUTS_PER_DIGIT; i++)
      {
         digitalWrite(g_stcPinConfHourHigh[uiHourHigh][i].pin_number, g_stcPinConfHourHigh[uiHourHigh][i].pin_state);
         digitalWrite(g_stcPinConfHourLow[uiHourLow][i].pin_number, g_stcPinConfHourLow[uiHourLow][i].pin_state);
         digitalWrite(g_stcPinConfMinHigh[uiMinHigh][i].pin_number, g_stcPinConfMinHigh[uiMinHigh][i].pin_state);
         digitalWrite(g_stcPinConfMinLow[uiMinLow][i].pin_number, g_stcPinConfMinLow[uiMinLow][i].pin_state);
      }
   }
   else
   {
      selectPwmForDigit(DIG_HOUR_HIGH, uiHourHigh);
      selectPwmForDigit(DIG_HOUR_LOW, uiHourLow);
      selectPwmForDigit(DIG_MINUTE_HIGH, uiMinHigh);
      selectPwmForDigit(DIG_MINUTE_LOW, uiMinLow);
   }
}

void LedClockControl::selectPwmForDigit(eDIGIT eDig, uint8_t uiChar)
{
   charMapping_t *pTmp = m_stcDigitData[eDig].pPinData;
   for (uint8_t i = 0; i < NUM_OUTPUTS_PER_DIGIT; i++)
   {
      // Serial.print("Setting PWM pin: ");
      // Serial.println((*pTmp)[uiChar][i].pin_number);
      if ((*pTmp)[uiChar][i].pin_state == LOW)
      {
         ledcAttachPin((*pTmp)[uiChar][i].pin_number, PWM_LED_CHANNEL_OFF);
      }
      else
      {
         ledcAttachPin((*pTmp)[uiChar][i].pin_number, m_stcDigitData[eDig].uiPwmChannel);
      }
   }
}

void LedClockControl::setBrightnessAll(uint8_t uiBrigthnessPercent)
{
   if (m_bEnableDimming)
   {
      for (uint8_t i = DIG_FIRST; i < DIG_LAST; i++)
      {
         m_stcDigitData[i].uiBrightness = (255 / 100.0) * uiBrigthnessPercent;
         ledcWrite(m_stcDigitData[i].uiPwmChannel, m_stcDigitData[i].uiBrightness);
      }
   }
}

void LedClockControl::setBrightness(uint8_t uiHourHigh, uint8_t uiHourLow, uint8_t uiMinHigh, uint8_t uiMinLow)
{

   m_stcDigitData[DIG_HOUR_HIGH].uiBrightness = (255 / 100.0) * uiHourHigh;
   ledcWrite(m_stcDigitData[DIG_HOUR_HIGH].uiPwmChannel, m_stcDigitData[DIG_HOUR_HIGH].uiBrightness);

   m_stcDigitData[DIG_HOUR_LOW].uiBrightness = (255 / 100.0) * uiHourLow;
   ledcWrite(m_stcDigitData[DIG_HOUR_LOW].uiPwmChannel, m_stcDigitData[DIG_HOUR_LOW].uiBrightness);

   m_stcDigitData[DIG_MINUTE_HIGH].uiBrightness = (255 / 100.0) * uiMinHigh;
   ledcWrite(m_stcDigitData[DIG_MINUTE_HIGH].uiPwmChannel, m_stcDigitData[DIG_MINUTE_HIGH].uiBrightness);

   m_stcDigitData[DIG_MINUTE_LOW].uiBrightness = (255 / 100.0) * uiMinLow;
   ledcWrite(m_stcDigitData[DIG_MINUTE_LOW].uiPwmChannel, m_stcDigitData[DIG_MINUTE_LOW].uiBrightness);
}

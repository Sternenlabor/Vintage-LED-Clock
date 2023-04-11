
#include "ledclockctrl.h"
#include "time.h"

#define NUM_OUTPUTS_PER_DIGIT 5
#define SEGMENT_OFF 10

#define PWM_LED_CHANNEL_LOW 0  //!< PWM Channel which always stays low
#define PWM_LED_CHANNEL_HIGH 1 //!< PWM Channel which is used for dimming
#define PWM_LED_FREQUENCY 1000 //!< frequency in Hz
#define PWM_LED_RESOLUTION 8   //!< PWM resolution in bits

stcPin g_stcPinConfHourHigh[11][NUM_OUTPUTS_PER_DIGIT] = {
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

stcPin g_stcPinConfHourLow[11][NUM_OUTPUTS_PER_DIGIT] = {
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

stcPin g_stcPinConfMinHigh[11][NUM_OUTPUTS_PER_DIGIT] = {
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

stcPin g_stcPinConfMinLow[11][NUM_OUTPUTS_PER_DIGIT] = {
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

LedClockControl::LedClockControl(bool bEnableDimming, uint8_t uiBrigthnessPercent) : m_bEnableDimming(bEnableDimming),
                                                                                     m_uiBrigthnessPercent(uiBrigthnessPercent)
{
   // nothing to do
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
      for (uint8_t i = 0; i < NUM_OUTPUTS_PER_DIGIT; i++)
      {
         pinMode(g_stcPinConfHourHigh[0][i].pin_number, OUTPUT);
         pinMode(g_stcPinConfHourLow[0][i].pin_number, OUTPUT);
         pinMode(g_stcPinConfMinHigh[0][i].pin_number, OUTPUT);
         pinMode(g_stcPinConfMinLow[0][i].pin_number, OUTPUT);
      }
   }
   else
   {
      ledcSetup(PWM_LED_CHANNEL_LOW, PWM_LED_FREQUENCY, PWM_LED_RESOLUTION);
      ledcWrite(PWM_LED_CHANNEL_LOW, 0);

      ledcSetup(PWM_LED_CHANNEL_HIGH, PWM_LED_FREQUENCY, PWM_LED_RESOLUTION);
      setBrightness(m_uiBrigthnessPercent);
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

   Serial.println(String(h1) + "-" + String(h2) + ":" + String(m1) + "-" + String(m2));
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
      for (uint8_t i = 0; i < NUM_OUTPUTS_PER_DIGIT; i++)
      {
         selectPwmForIO(g_stcPinConfHourHigh[uiHourHigh][i].pin_number, g_stcPinConfHourHigh[uiHourHigh][i].pin_state);
         selectPwmForIO(g_stcPinConfHourLow[uiHourLow][i].pin_number, g_stcPinConfHourLow[uiHourLow][i].pin_state);
         selectPwmForIO(g_stcPinConfMinHigh[uiMinHigh][i].pin_number, g_stcPinConfMinHigh[uiMinHigh][i].pin_state);
         selectPwmForIO(g_stcPinConfMinLow[uiMinLow][i].pin_number, g_stcPinConfMinLow[uiMinLow][i].pin_state);
      }
   }
}

void LedClockControl::selectPwmForIO(uint8_t uiPin, uint8_t uiState)
{
   if (uiState == LOW)
   {
      ledcAttachPin(uiPin, PWM_LED_CHANNEL_LOW);
   }
   else
   {
      ledcAttachPin(uiPin, PWM_LED_CHANNEL_HIGH);
   }
}

void LedClockControl::setBrightness(uint8_t uiBrigthnessPercent)
{
   if (m_bEnableDimming)
   {
      m_uiBrigthnessPercent = uiBrigthnessPercent;
      ledcWrite(PWM_LED_CHANNEL_HIGH, ((255 / 100.0) * m_uiBrigthnessPercent));
   }
}

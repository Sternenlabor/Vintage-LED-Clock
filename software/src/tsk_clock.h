#ifndef __TSK_CLOCK_H__
#define __TSK_CLOCK_H__

#include <tasker.h>
#include "ledclockctrl.h"
#include "evt_custom.h"

#define DEFAULT_BRIGHTNESS 30

class TskClock : public TaskBase
{
public:
    TskClock() : TaskBase("TskClock"),
                 m_ledClock(true, DEFAULT_BRIGHTNESS),
                 m_bUpdateByUdp(false)
    {
    }
    ~TskClock();

    void Entry(const Event *pEvt)
    {
        if (pEvt)
        {
            if (pEvt->GetType() == EVT_INIT)
            {
                m_ledClock.begin();
                m_ledClock.updateDigits(SEGMENT_OFF, SEGMENT_OFF, SEGMENT_OFF, SEGMENT_OFF);
            }
            else if (pEvt->GetType() == EVT_UPDATE)
            {
                Serial.println("Startgin LED Clock update.");
                StartTimer(0, 100);
            }
            else if (pEvt->GetType() == EVT_TIMER)
            {
                HandleTimer(static_cast<const EvtTimer *>(pEvt));
            }
            else if (pEvt->GetType() == EVT_LED_UPDATE)
            {
                Serial.println("Updating LED by UDP");
                const EvtLedUpdate *pLed = static_cast<const EvtLedUpdate *>(pEvt);
                m_ledClock.setBrightness(pLed->m_uiBrightnessHourHigh, pLed->m_uiBrightnessHourLow, pLed->m_uiBrightnessMinuteHigh, pLed->m_uiBrightnessMinuteLow);
                m_ledClock.updateDigits(pLed->m_uiHourHigh, pLed->m_uiHourLow, pLed->m_uiMinuteHigh, pLed->m_uiMinuteLow);
                m_bUpdateByUdp = true;
            }
        }
    }

private:
    void HandleTimer(const EvtTimer *pEvt)
    {
        if (!m_bUpdateByUdp)
        {
            m_ledClock.digitalClockDisplay();
            m_ledClock.setBrightnessAll(DEFAULT_BRIGHTNESS);
        }
        else
        {
            m_bUpdateByUdp = false;
        }
        StartTimer(0, 1000);
    }

    LedClockControl m_ledClock;
    bool m_bUpdateByUdp;
};

#endif // __TSK_CLOCK_H__
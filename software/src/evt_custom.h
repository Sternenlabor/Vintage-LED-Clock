#ifndef _EVT_CUSTOM_
#define _EVT_CUSTOM_

#include <event.h>

enum eEVT_CUSTOM
{
    EVT_LED_UPDATE = EVT_LAST
};

class EvtLedUpdate : public Event
{
public:
    EvtLedUpdate(TaskBase *pSrc, TaskBase *pDst, uint8_t *cstrData, size_t uiSize) : Event(pSrc, pDst)
    {
        if (uiSize == 8)
        {
            uint8_t i = 0;
            m_uiBrightnessHourHigh = cstrData[i++];
            m_uiBrightnessHourLow = cstrData[i++];
            m_uiBrightnessMinuteHigh = cstrData[i++];
            m_uiBrightnessMinuteLow = cstrData[i++];
            
            m_uiHourHigh = cstrData[i++];
            m_uiHourLow = cstrData[i++];
            m_uiMinuteHigh = cstrData[i++];
            m_uiMinuteLow = cstrData[i++];
        }
    }
    
    ~EvtLedUpdate()
    {
    }

    virtual uint8_t GetType() const override
    {
        return EVT_LED_UPDATE;
    }
    uint8_t m_uiBrightnessHourHigh;
    uint8_t m_uiBrightnessHourLow;
    uint8_t m_uiBrightnessMinuteHigh;
    uint8_t m_uiBrightnessMinuteLow;

    uint8_t m_uiHourHigh;
    uint8_t m_uiHourLow;
    uint8_t m_uiMinuteHigh;
    uint8_t m_uiMinuteLow;
};

#endif // _EVT_CUSTOM_
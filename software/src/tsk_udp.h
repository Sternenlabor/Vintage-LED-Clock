#ifndef __TSK_UDP_H__
#define __TSK_UDP_H__

#include <tasker.h>
#include <Arduino.h>
#include <AsyncUDP.h>
#include <ArduinoOTA.h>
#include "evt_custom.h"

#define UDP_PORT 2233
#define BUFF_SIZE 20

class TskUdp : public TaskBase
{
public:
    TskUdp() : TaskBase("TskUdp"), m_udp(), m_bInitDone(false)
    {
    }

    ~TskUdp();
    void Entry(const Event *pEvt)
    {
        if (pEvt)
        {
            if (pEvt->GetType() == EVT_UPDATE)
            {
                Serial.println("Initializing UDP");
                m_udp.listen(UDP_PORT);
                m_udp.onPacket([this](AsyncUDPPacket packet)
                               { Serial.print("Received package with size: ");
                               Serial.println(packet.length());
                                   TK()->SendEvent(new EvtLedUpdate(this, TK()->GetTask("TskClock"), packet.data(), packet.length())); });

                // setup OTA
                ArduinoOTA.setHostname(WiFi.getHostname());
                ArduinoOTA.setRebootOnSuccess(true);
                ArduinoOTA.begin();
                m_bInitDone = true;
            }
        }
        else if (m_bInitDone)
        {
            ArduinoOTA.handle();
        }
    }

private:
    uint8_t m_arrBuff[BUFF_SIZE];
    AsyncUDP m_udp;
    bool m_bInitDone;
};

#endif // __TSK_UDP_H__

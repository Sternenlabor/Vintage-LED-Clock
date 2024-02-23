#ifndef _TSK_TIMEUPDATE_H_
#define _TSK_TIMEUPDATE_H_

#include <tasker.h>
#include <Arduino.h>
#include "time.h"
#include "credentials.h"

extern const char cstrSSID[];
extern const char cstrPWD[];

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;

#define TIM_UPDATE 0
#define TO_MS_UPDATE_TIME 600000

#define TIM_CHECK_WIFI 1
#define TO_MS_CHECK_WIFI 3000

#define TIM_UPDATE_NTP 2
#define TO_MS_UPDATE_NTP 500

class TskTimeUpdate : public TaskBase
{
public:
   TskTimeUpdate(bool bWifiOnlyForUpdate = true) : TaskBase("TskTimeUpdate"),
                                                   m_bWifiOnlyForUpdate(bWifiOnlyForUpdate),
                                                   m_bInitDone(false)
   {
      WiFi.setHostname(cstrHostname);
   }
   virtual void Entry(const Event *pEvt)
   {
      if (pEvt != nullptr)
      {
         if (pEvt->GetType() == EVT_INIT)
         {
            StartTimer(TIM_UPDATE, 100);
         }
         else if (pEvt->GetType() == EVT_TIMER)
         {
            HandleEvtTimer(static_cast<const EvtTimer *>(pEvt));
         }
      }
   }

   void HandleEvtTimer(const EvtTimer *pEvt)
   {
      if (pEvt->GetTimerId() == TIM_UPDATE && WiFi.status() != WL_CONNECTED)
      {
         // Connect to Wi-Fi
         Serial.print("Connecting to WiFi: ");
         Serial.println(cstrSSID);
         WiFi.mode(WIFI_STA);
         WiFi.begin(cstrSSID, cstrPWD);
         StartTimer(TIM_CHECK_WIFI, TO_MS_CHECK_WIFI);
      }
      else if (pEvt->GetTimerId() == TIM_CHECK_WIFI)
      {
         if (WiFi.status() != WL_CONNECTED)
         {

            Serial.println("...waiting for WiFi connection.");
            WiFi.disconnect();
            WiFi.reconnect();
            StartTimer(TIM_CHECK_WIFI, TO_MS_CHECK_WIFI);
         }
         else
         {
            Serial.println("WiFi connected.");
            StartTimer(TIM_UPDATE_NTP, TO_MS_UPDATE_NTP);
         }
      }
      else if (pEvt->GetTimerId() == TIM_UPDATE_NTP || WiFi.status() == WL_CONNECTED)
      {
         struct tm timeinfo;
         Serial.print("Updating time from NTP server...");

         // Init and get the time
         configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

         if (!getLocalTime(&timeinfo))
         {
            Serial.println(" ERROR retrying.");
            StartTimer(TIM_UPDATE_NTP, TO_MS_UPDATE_NTP);
         }
         else
         {
            Serial.println(" success.");
            String timezone = "CET-1CEST,M3.5.0,M10.5.0/3";
            //  Now adjust the TZ.  Clock settings are adjusted to show the new local time
            setenv("TZ", timezone.c_str(), 1);
            tzset();

            if (!m_bInitDone)
            {
               //Serial.println("Send Event to Clock.");
               TK()->SendEvent(new EvtUpdate(this, TK()->GetTask("TskClock")));
               TK()->SendEvent(new EvtUpdate(this, TK()->GetTask("TskUdp")));
               m_bInitDone = true;
            }

            if (m_bWifiOnlyForUpdate)
            {
               // disconnect WiFi as it's no longer needed
               Serial.println("Shutting down WiFi.");
               WiFi.disconnect(true);
               WiFi.mode(WIFI_OFF);
            }
         }

         // restart timer for update
         StartTimer(TIM_UPDATE, TO_MS_UPDATE_TIME);
      }
   }

private:
   bool m_bWifiOnlyForUpdate;
   bool m_bInitDone;
};

#endif /* _TSK_TIMEUPDATE_H_ */
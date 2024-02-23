#include <Arduino.h>
#include <WiFi.h>


#include "tsk_timupdate.h"
#include "tsk_clock.h"
#include "tsk_udp.h"



void setup()
{
   Serial.begin(115200);
   Serial.setDebugOutput(true);
   
   Serial.println("Initializing Tasker.");
   Tasker* pTasker = Tasker::GetInstance();
   pTasker->AddTask(new TskTimeUpdate(false));
   pTasker->AddTask(new TskClock());
   pTasker->AddTask(new TskUdp());
    
   Serial.println("setup() completed");
   

}

void loop()
{
   Tasker::GetInstance()->Run();
   // g_LedClock.digitalClockDisplay();
   // delay(1000);
}

#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include "credentials.h"
#include "ledclockctrl.h"

extern const char cstrSSID[];
extern const char cstrPWD[];

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;

LedClockControl g_LedClock(true, 30);

void setup()
{

   g_LedClock.begin();
   g_LedClock.updateDigits(SEGMENT_OFF,SEGMENT_OFF,SEGMENT_OFF,SEGMENT_OFF);

   Serial.begin(115200);
   Serial.setDebugOutput(true);

   // Connect to Wi-Fi
   Serial.print("Connecting to ");
   Serial.println(cstrSSID);
   WiFi.begin(cstrSSID, cstrPWD);
   while (WiFi.status() != WL_CONNECTED)
   {
      delay(500);
      Serial.print(".");
   }
   Serial.println("");
   Serial.println("WiFi connected.");

   struct tm timeinfo;

   Serial.println("Setting up time");

   // Init and get the time
   configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

   if (!getLocalTime(&timeinfo))
   {
      Serial.println("  Failed to obtain time");
      return;
   }
   Serial.println("  Got the time from NTP");

   Serial.println();
   Serial.println("Now - change timezones to Berlin");

   String timezone = "CET-1CEST,M3.5.0,M10.5.0/3";
   setenv("TZ", timezone.c_str(), 1); //  Now adjust the TZ.  Clock settings are adjusted to show the new local time
   tzset();

   g_LedClock.digitalClockDisplay();
   // disconnect WiFi as it's no longer needed
   WiFi.disconnect(true);
   WiFi.mode(WIFI_OFF);

}

void loop()
{
   g_LedClock.digitalClockDisplay();
   delay(1000);
}

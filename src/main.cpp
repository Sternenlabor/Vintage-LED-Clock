#include <Arduino.h>
#include <WiFi.h>
#include "time.h"

// char *ssid = "Sternenlabor";         // Set you WiFi SSID
// char *password = "!Sternenlabor99!"; // Set you WiFi password

char *ssid = "blacky_nomap";         // Set you WiFi SSID
char *password = "SaltAndPepper101"; // Set you WiFi password

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;

struct pin
{
  int pin_number;
  int pin_state;
};

pin char4[10][5] = {
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
     {23, HIGH}}};

pin char3[10][5] = {
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
     {5, HIGH}}};

pin char2[10][5] = {
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
     {15, HIGH}}};

pin char1[10][5] = {
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
     {14, HIGH}}};

void digitalClockDisplay()
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

  int temp = hours;  // Get the hours and save to variable temp
  int h1 = temp / 10; // Split hours into two digits, tens and units
  int h2 = temp % 10;
  temp = minutes;    // Get the minutes and save to variable temp
  int m1 = temp / 10; // Split minutes into two digits, tens and units
  int m2 = temp % 10;

  Serial.println(String(h1) + "-" + String(h2) + ":" + String(m1) + "-" + String(m2));

  digitalWrite(char4[h1][0].pin_number, char4[h1][0].pin_state);
  digitalWrite(char4[h1][1].pin_number, char4[h1][1].pin_state);
  digitalWrite(char4[h1][2].pin_number, char4[h1][2].pin_state);
  digitalWrite(char4[h1][3].pin_number, char4[h1][3].pin_state);
  digitalWrite(char4[h1][4].pin_number, char4[h1][4].pin_state);

  digitalWrite(char3[h2][0].pin_number, char3[h2][0].pin_state);
  digitalWrite(char3[h2][1].pin_number, char3[h2][1].pin_state);
  digitalWrite(char3[h2][2].pin_number, char3[h2][2].pin_state);
  digitalWrite(char3[h2][3].pin_number, char3[h2][3].pin_state);
  digitalWrite(char3[h2][4].pin_number, char3[h2][4].pin_state);

  digitalWrite(char2[m1][0].pin_number, char2[m1][0].pin_state);
  digitalWrite(char2[m1][1].pin_number, char2[m1][1].pin_state);
  digitalWrite(char2[m1][2].pin_number, char2[m1][2].pin_state);
  digitalWrite(char2[m1][3].pin_number, char2[m1][3].pin_state);
  digitalWrite(char2[m1][4].pin_number, char2[m1][4].pin_state);

  digitalWrite(char1[m2][0].pin_number, char1[m2][0].pin_state);
  digitalWrite(char1[m2][1].pin_number, char1[m2][1].pin_state);
  digitalWrite(char1[m2][2].pin_number, char1[m2][2].pin_state);
  digitalWrite(char1[m2][3].pin_number, char1[m2][3].pin_state);
  digitalWrite(char1[m2][4].pin_number, char1[m2][4].pin_state);
}

void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);

  digitalWrite(13, LOW); // 0
  digitalWrite(0, LOW);  // 1
  digitalWrite(32, LOW); // 2
  digitalWrite(33, LOW); // 3
  digitalWrite(23, LOW); // 4

  digitalWrite(22, LOW); // 10
  digitalWrite(21, LOW); // 11
  digitalWrite(19, LOW); // 12
  digitalWrite(18, LOW); // 13
  digitalWrite(5, LOW);  // 14

  digitalWrite(17, LOW); // 20
  digitalWrite(16, LOW); // 21
  digitalWrite(4, LOW);  // 22
  digitalWrite(2, LOW);  // 23
  digitalWrite(15, LOW); // 24

  digitalWrite(25, LOW); // 30
  digitalWrite(26, LOW); // 31
  digitalWrite(27, LOW); // 32
  digitalWrite(12, LOW); // 33
  digitalWrite(14, LOW); // 34

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
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

  if(!getLocalTime(&timeinfo)){
    Serial.println("  Failed to obtain time");
    return;
  }
  Serial.println("  Got the time from NTP");

  Serial.println();
  Serial.println("Now - change timezones to Berlin");

  String timezone = "CET-1CEST,M3.5.0,M10.5.0/3";
  setenv("TZ",timezone.c_str(),1);  //  Now adjust the TZ.  Clock settings are adjusted to show the new local time
  tzset();

  digitalClockDisplay();

  // disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop()
{
  
  digitalClockDisplay();
  delay(1000);

return;
/*
  if (timeStatus() != timeNotSet)
  {
    if (now() != prevDisplay)
    { // update the display only if time has changed
      prevDisplay = now();
      digitalClockDisplay();
    }
  }
*/
  return;

  for (int i = 9; i >= 0; i--)
  {
    digitalWrite(char4[i][0].pin_number, char4[i][0].pin_state);
    digitalWrite(char4[i][1].pin_number, char4[i][1].pin_state);
    digitalWrite(char4[i][2].pin_number, char4[i][2].pin_state);
    digitalWrite(char4[i][3].pin_number, char4[i][3].pin_state);
    digitalWrite(char4[i][4].pin_number, char4[i][4].pin_state);

    digitalWrite(char3[i][0].pin_number, char3[i][0].pin_state);
    digitalWrite(char3[i][1].pin_number, char3[i][1].pin_state);
    digitalWrite(char3[i][2].pin_number, char3[i][2].pin_state);
    digitalWrite(char3[i][3].pin_number, char3[i][3].pin_state);
    digitalWrite(char3[i][4].pin_number, char3[i][4].pin_state);

    digitalWrite(char2[i][0].pin_number, char2[i][0].pin_state);
    digitalWrite(char2[i][1].pin_number, char2[i][1].pin_state);
    digitalWrite(char2[i][2].pin_number, char2[i][2].pin_state);
    digitalWrite(char2[i][3].pin_number, char2[i][3].pin_state);
    digitalWrite(char2[i][4].pin_number, char2[i][4].pin_state);

    digitalWrite(char1[i][0].pin_number, char1[i][0].pin_state);
    digitalWrite(char1[i][1].pin_number, char1[i][1].pin_state);
    digitalWrite(char1[i][2].pin_number, char1[i][2].pin_state);
    digitalWrite(char1[i][3].pin_number, char1[i][3].pin_state);
    digitalWrite(char1[i][4].pin_number, char1[i][4].pin_state);

    delay(500);
  }
}

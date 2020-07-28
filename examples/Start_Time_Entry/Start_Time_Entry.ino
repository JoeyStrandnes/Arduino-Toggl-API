/*
This example will:
Print the Username and Time zone to the terminal.
Start a timer with a description "HelloWorld", use the tag "TagName", and created by "ESP". The PID must be collected by the user at the moment.

The timer will be stopped after ~10 seconds
*/
#define ESP32

#include "Toggl.h"


String const Token{"Token"};

//String const SSID{"SSID"};
//String const PASS{"PASS"};
const char* SSID = "SSID";
const char* PASS = "PASS";

String TimerID{};
int const PID{"PID"};

Toggl toggl;

void setup(){

    Serial.begin(115200);

    toggl.init(SSID,PASS);
    toggl.setAuth(Token);

    Serial.println(toggl.getFullName());
    Serial.println(toggl.getTimezone());
    
    TimerID = (toggl.StartTimeEntry("HelloWorld", "TagName", PID, "ESP"));
    delay(10000);
    Serial.println(toggl.StopTimeEntry(TimerID));
  
}

void loop(){

}

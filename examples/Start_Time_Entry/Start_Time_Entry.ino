/*
This example will:
Print the Username and Time zone to the terminal.
Start a timer with a description "HelloWorld", use the tag "TagName", and created by "ESP". The PID must be collected by the user at the moment.

The timer will be stopped after ~10 seconds
*/

#include "Toggl.h"

const char* SSID = "SSID";
const char* PASS = "PASSWORD";

String TimerID{};
int const PID{123456789};                 //Project ID is specific to each user project
String const Token{"TOKEN"};               //API Token is found in "Profile Settings" 


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

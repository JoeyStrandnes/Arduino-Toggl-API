/*
This example will:
Print the Username and Time zone to the terminal.
Start a timer with a description "HelloWorld", use the tag "TagName", and created by "ESP". The PID must be collected by the user at the moment.

The timer will be stopped after ~10 seconds
*/
#include <Toggl.h>

String const Token{"API Token"};

String const SSID{"Network SSID"};
String const PASS{"Password"};
String const TimerID{};
int const PID{Project ID};

Toggl toggl;

void setup(){

    Serial.begin(115200);
    
    toggl.init(SSID,PASS);
    toggl.setAuth(Token);

    Serial.println(toggl.getFullName());
    Serial.println(toggl.getTimezone());
    
    TimerID = (toggl.StartTimeEntry("HelloWorld", "TagName", PID, "ESP"));
    delay(10000);
    toggl.StopTimeEntry(TimerID);
}

void loop(){

}
/*
This example will:
Print the Username and Time zone to the terminal.
Start a timer with a description "HelloWorld", use the tag "TagName", and created by "ESP". The PID must be collected by the user at the moment.

The timer will be stopped after ~10 seconds
*/

#include <Toggl.h>

#if defined (ESP8266)         							//Use String for ESP8266

String const SSID{"SSID"};
String const PASS{"PASSWORD"};

#elif defined(ESP32)         	 						//Use char* for ESP32

const char* SSID = "SSID";
const char* PASS = "PASSWORD";

#else
#error "ERROR: Processor not defined"

#endif
/*****************************************************/

String TimerID{};
int const PID{123456789};                               //Project ID is specific to each user project
String const Token{"Token"}; 							//API Token is found in "Profile Settings" 


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

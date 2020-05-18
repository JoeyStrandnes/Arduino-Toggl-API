# Arduino-Toggl-API
Port of Toggls official API V8
https://github.com/toggl/toggl_api_docs

***Only the most used API features are implemented***

This more of a learning exercise for me so take all the code with a grain of salt.
The code is written for the ESP8266 but can easily be ported to the ESP32. Will do so when I have access to an ESP32.

This code is heavily "work in progress" and not complete, it’s not optimized.

* GET "User details" is implemented
* Some PUT/POST have been implemented 

# GET
```c++
getID();                    //Returns ID as integer
getApiToken();              //Returns API Token as String
getDefaultWid();            //Return the default Workspace ID as Int
getEmail();                 //Returns Email as String   
getFullName();              //Returns Name of user as String
getJqTimeOfDayFormat();     //Returns Time of day JQ formatting as String
getJqDateFormat();          //Returns date JQ formatting as String
getTimeOfDayFormat();       //Returns Time of day formatting as String
getDateFormat();            //Returns date formatting as String
getStoreStartAndStopTime(); //Returns START/STOP time as bool
getBeginningOfWeek();       //Returns The day the weeks starts on as uint
getLang();                  //Returns The language used as String
getDurationFormat();        //Returns Duration formatting as String
getAt();                    //Returns AT? as String
getCreation();              //Returns Account creation date as String
getTimezone();              //Returns Time zone as string
getWorkSpace();             //Returns a String of all the workplaces
```
# PUT & POST
```c++
StartTimeEntry(String Description, String Tags, int PID, String CreatedWith); // Returns the timer ID as a String
StopTimeEntry(String ID);
CreateTimeEntry(String Description, String Tags, int Duration, String Start, int PID, String CreatedWith); // Returns the timer ID as a String
CreateTag(String Name, int WID); // Requires the Workspace ID
```

# General Setup
```c++
init(String const& SSID, String const& PASS); //Starts WiFi connection
setAuth(String const Token);                  //Creates Basic authentication key
```

# Used packages (Must be installed on computer)
```c++
ArduinoJson
ESP8266WiFi
ESP8266HTTPClient
WiFiClientSecureBearSSL
```
# Example
```c++
/*
This example will:
Print the Username and Time zone to the terminal.
Start a timer with a description "HelloWorld", use the tag "TagName", and created by "ESP". The PID must be collected by the user at the moment.

The timer will be stopped after ~10 seconds
*/
#include "Toggl.h"

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

```

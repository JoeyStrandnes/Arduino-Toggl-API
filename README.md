# Arduino-Toggl-API
Port of Toggls official API V8
https://github.com/toggl/toggl_api_docs

This more of a learning exercise for me so take all the code with a grain of salt.
The code is written for the ESP8266 but can easily be ported to the ESP32. Will do so when I have access to an ESP32.

This code is heavily "work in progress" and not complete, it’s not optimized.

* So far only the "GET User details" is implemented

# GET
```c++
getID();                    //Returns ID as integer
getApiToken();              //Returns API Token as String
getDefaultWid();            //Returns Email as String
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
```
# General Setup
```c++
init(String const& SSID, String const& PASS); //Starts WiFi connection
setAuth(String const Token);        //Creates Basic authentication key
```
# Example

```c++
#include "Toggl.h"

String const Token{"API Token"};

String SSID{"Network SSID"};
String PASS{"Password"};

Toggl toggl;

void setup(){

    toggl.init(SSID,PASS);
    toggl.setAuth(Token);

    Serial.println(toggl.getFullName());
    Serial.println(toggl.getTimezone());

}

void loop(){
    
    delay(1000);
}

```

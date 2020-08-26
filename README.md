# Arduino Toggl API

![Passing](https://img.shields.io/badge/build-passing-brightgreen)![GitHub last commit](https://img.shields.io/github/last-commit/JoeyStrandnes/Arduino-Toggl-API)![GitHub issues](https://img.shields.io/github/issues/JoeyStrandnes/Arduino-Toggl-API)

![Banner](https://i.imgur.com/Mr9Amfs.png)



Port of Toggl's official API V8 https://github.com/toggl/toggl_api_docs

***Most used API features are implemented***

This more of a learning exercise for me so take all the code with a grain of salt.

There is lots of room for optimization and improvement.



# Get User Details
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
# Create/Start Time Entries
```c++
StartTimeEntry(String Description, String Tags, int PID, String CreatedWith); 	// Returns the timer ID as a String
StopTimeEntry(String ID);													  	//Returns HTTP error in form of string
CreateTimeEntry(String Description, String Tags, int Duration, String Start, int PID, String CreatedWith); // Returns the timer ID as a String
CreateTag(String Name, int WID); // Requires the Workspace ID
```

# General Setup
```c++
init(String const& SSID, String const& PASS); //Starts WiFi connection
setAuth(String const Token);                  //Creates Basic authentication key
```

# Dependencies (Must be installed on computer)
```markdown
ArduinoJson
ESP8266WiFi
ESP8266HTTPClient
WiFiClientSecureBearSSL
ESP32 default libraries
   
```
# Example

### Print username and time zone to the terminal

### Starts a timer that lasts ~10s

```c++
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


```

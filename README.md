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
```
# Create/Start Time Entries

```c++
StartTimeEntry(String Description, String Tags, int PID, String CreatedWith); 	// Returns the timer ID as a String
StopTimeEntry(String ID);	//Returns HTTP error in form of string
CreateTimeEntry(String Description, String Tags, int Duration, String Start, int PID, String CreatedWith); // Returns the timer ID as a String
getTimerDuration();		//Returns the duration of the active timer in secconds. Returns 0 if no timer is active.
getTimerID();			//Returns the active timers ID as String. Returns "null" if no timer is active.
isTimerActive();		//Returns a bool if timer is active.

```

# Misc

```c++
getWorkSpace(); 					// Returns a "pretty" string of all workspaces and ID's
getProject(int const& WID); 		// Returns a "pretty" string of all project is specific workplace
CreateTag(String Name, int WID); 	// Requires the Workspace ID
```



# General Setup

```c++
init(const char* SSID, const char* PASS); 	//Starts WiFi connection
setAuth(String const Token);                //Creates Basic authentication key
```

# Dependencies
```markdown
ArduinoJson v6
ESP8266 default libraries
ESP32 default libraries
```
# Examples

- [Start Time Entry:](https://github.com/JoeyStrandnes/Arduino-Toggl-API/tree/master/examples/Start_Time_Entry) Runs a timer for ~10s

- [Button Timer:](https://github.com/JoeyStrandnes/Arduino-Toggl-API/tree/master/examples/Button_Timer) Starts a timer and LED when a button is pressed. Stops timer and turns of LED when it is pressed again.



[Advanced Button Timer:](https://github.com/JoeyStrandnes/Arduino-Toggl-API/tree/master/examples/Advanced_Button_Timer) Does everything that the regular button timer does but will "sync" with other active timers. It will know if a timer is started and will know if it is stopped. The LED and button function will adjust acording to the timer status.


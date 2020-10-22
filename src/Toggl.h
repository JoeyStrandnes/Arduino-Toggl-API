/*
 * Arduino ESP8266 & ESP32 Toggl API v8 Port
 * Using ArduinoJson Version 6
 * Using Toggl API v8
 * https://github.com/toggl/toggl_api_docs/blob/master/toggl_api.md
 */

#ifndef TOGGL_H
#define TOGGL_H

#include <Arduino.h>
#include <ArduinoJson.h>


// Dependencies for ESP8266
# if defined (ESP8266)

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include "base64.h"

// Dependencies for ESP32
# elif defined(ESP32)

#include "WiFi.h"
#include <HTTPClient.h>
#include <base64.h>

# else
#error "Please define ESP processor, ESP32 or ESP8266"

# endif

class Toggl{
  public:
    Toggl();

    //Get the induvidual account settings/data
    const uint16_t  getID();
    const String    getApiToken();
    const uint16_t  getDefaultWid();
    const String    getEmail();
    const String    getFullName();
    const String    getJqTimeOfDayFormat();
    const String    getJqDateFormat();
    const String    getTimeOfDayFormat();
    const String    getDateFormat();
    const bool      getStoreStartAndStopTime();
    const uint16_t  getBeginningOfWeek();
    const String    getLang();
    const String    getDurationFormat();
    const String    getAt();
    const String    getCreation();
    const String    getTimezone();

    //Misc
    const String    getWorkSpace();
    const String    getProject(int const& WID);
    //const int       getPID(String const& WID ,String const& ProjectName);
    const String    CreateTag(String const& Name, int const& WID);
    
    //Timer related functions
    const String    StartTimeEntry(String const& Description, String const& Tags, int const& PID, String const& CreatedWith);
    const String    StopTimeEntry(String const& ID);
    const String    CreateTimeEntry(String const& Description, String const& Tags, int const& Duration, String const& Start,  int const& PID, String const& CreatedWith);
    const int32_t   getTimerDuration();
    const String    getTimerID();
    const bool      isTimerActive();
    
    //General functionality
    void init(const char* SSID,const char* PASS);
    void setAuth(String const& Token);

  private:
    const uint32_t  getCurrentTime(const String Timezone);
    const String    getUserData(String Input);
    const String    getTimerData(String Input);
    String          AuthorizationKey{};
    const char*     Fingerprint{"51240ac662cb06319ca77b133a9de73f6ba789bf"};  // Fingerprint for Toggle API, expires on 01/10/2021
};

#endif

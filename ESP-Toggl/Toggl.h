/*
 * Arduino ESP8266 Toggl TEST
 * Using ArduinoJson Version 6
 * Using Toggl API v8
 * https://github.com/toggl/toggl_api_docs/blob/master/toggl_api.md
 */


#ifndef TOGGL_H
#define TOGGL_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include "base64.h"



class Toggl{


  public:
    Toggl();
    

    //Get the induvidual account settings/data
    const uint16_t  getID();
    const String    getApiToken();
    const uint16_t  getDefaultWid();
    const String    getEmail();
    const String     getFullName();
    const String    getJqTimeOfDayFormat();
    const String    getJqDateFormat();
    const String    getTimeOfDayFormat();
    const String    getDateFormat();
    const bool      getStoreStartAndStopTime();
    const uint16_t   getBeginningOfWeek();
    const String     getLang();
    const String     getDurationFormat();
    const String    getAt();
    const String    getCreation();
    const String    getTimezone();

    
    void getWorkspace();
    
    //POST requests
    String StartTimeEntry();
    int StopTimeEntry(String ID);
    int CreateTag(String const Name);

    //General functionality
    void init(String const& SSID, String const& PASS);
    void setAuth(String const Token);

    
  private:

    // Fingerprint for Toggle API, expires on 01/10/2021
    //const char fingerprint[] PROGMEM {"51240ac662cb06319ca77b133a9de73f6ba789bf"};
    //DynamicJsonDocument getUserData();
    String getUserData(String Input);
    String AuthorizationKey{};

  
};







#endif

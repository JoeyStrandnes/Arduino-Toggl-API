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

// Key/Value Pair
struct KVPair {
	String name;
	int id;
};

// A Key/Value return struct, including HTTP code for readability/
// This is essentially a std::arr, but there's not support for that in the default Arduino libs
struct KVReturn {
	int HTTPCode;
	int pairCount;
	KVPair * KVPairs;
};

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
    KVReturn        getWorkSpaces();
    KVReturn        getProjects(int const& WID);
    KVReturn        getTags(int const& WID);
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

	void getKVPairs(String const URL, KVReturn &data);
    const uint32_t getCurrentTime(const String Timezone);
    const String getUserData(String Input);
    const String getTimerData(String Input);
    String AuthorizationKey{};
    const char* Fingerprint{"dac8ac00a1aab269af2149ddb4bd5c881a1a9613"};  // Fingerprint valid until 18 June 2021
	const char* root_ca = \
	"-----BEGIN CERTIFICATE-----\n"\
	"MIIESjCCAzKgAwIBAgINAeO0nXfN9AwGGRa24zANBgkqhkiG9w0BAQsFADBMMSAw\n"\
	"HgYDVQQLExdHbG9iYWxTaWduIFJvb3QgQ0EgLSBSMjETMBEGA1UEChMKR2xvYmFs\n"\
	"U2lnbjETMBEGA1UEAxMKR2xvYmFsU2lnbjAeFw0xNzA2MTUwMDAwNDJaFw0yMTEy\n"\
	"MTUwMDAwNDJaMEIxCzAJBgNVBAYTAlVTMR4wHAYDVQQKExVHb29nbGUgVHJ1c3Qg\n"\
	"U2VydmljZXMxEzARBgNVBAMTCkdUUyBDQSAxRDIwggEiMA0GCSqGSIb3DQEBAQUA\n"\
	"A4IBDwAwggEKAoIBAQCy2Xvh4dc/HJFy//kQzYcVeXS3PkeLsmFV/Qw2xn53Qjqy\n"\
	"+lJbC3GB1k3V6SskTSNeiytyXyFVtSnvRMvrglKrPiekkklBSt6o3THgPN9tek0t\n"\
	"1m0JsA7jYfKy/pBsWnsQZEm0CzwI8up5DGymGolqVjKgKaIwgo+BUQzzornZdbki\n"\
	"nicUukovLGNYh/FdEOZfkbu5W8xH4h51toyPzHVdVwXngsaEDnRyKss7VfVucOtm\n"\
	"acMkuziTNZtoYS+b1q6md3J8cUhYMxCv6YCCHbUHQBv2PeyirUedtJQpNLOML80l\n"\
	"A1g1wCWkVV/hswdWPcjQY7gg+4wdQyz4+anV7G+XAgMBAAGjggEzMIIBLzAOBgNV\n"\
	"HQ8BAf8EBAMCAYYwHQYDVR0lBBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMCMBIGA1Ud\n"\
	"EwEB/wQIMAYBAf8CAQAwHQYDVR0OBBYEFLHdMl3otzdy0s5czib+R3niAQjpMB8G\n"\
	"A1UdIwQYMBaAFJviB1dnHB7AagbeWbSaLd/cGYYuMDUGCCsGAQUFBwEBBCkwJzAl\n"\
	"BggrBgEFBQcwAYYZaHR0cDovL29jc3AucGtpLmdvb2cvZ3NyMjAyBgNVHR8EKzAp\n"\
	"MCegJaAjhiFodHRwOi8vY3JsLnBraS5nb29nL2dzcjIvZ3NyMi5jcmwwPwYDVR0g\n"\
	"BDgwNjA0BgZngQwBAgEwKjAoBggrBgEFBQcCARYcaHR0cHM6Ly9wa2kuZ29vZy9y\n"\
	"ZXBvc2l0b3J5LzANBgkqhkiG9w0BAQsFAAOCAQEAcUrEwyOu9+OyAnmME+hTjoDF\n"\
	"8OPvcWCpqXs0ZYU0vUc7A1cWAJlIOuDg8OrNtkg81aty8NAby2QtOw10aNd0iDF8\n"\
	"aroO8IxNeM7aEPSKlkWXqZetxTUaGGTok7YNnR+5Xh2A6udbnI6uDqaE0tEXzrP7\n"\
	"9oFPPOZon8/xpnbFfafz3X1YD+D2YQEcUY52MytInVyBUXIIF7r9AdPuRvn0smhA\n"\
	"mTEBbE8bxlbrgXPSeVIFkiZbcc2dxNLOI3cPQXppXiElxvi3/3r3R97CAHucWkWc\n"\
	"Kk5GkNl1LNj/jO7M3GnrbOYV0KP/SAusVd/fJZ1CtlGjZpVgxdAi5yJ6UaXMhw==\n"\
	"-----END CERTIFICATE-----\n";
	const String BaseUrl = "https://api.track.toggl.com/api/v8";
};

#endif

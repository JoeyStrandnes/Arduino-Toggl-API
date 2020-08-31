#include "Toggl.h"


Toggl::Toggl(){

}




#if defined (ESP8266)

void Toggl::init(const char* NAME,const char* PASSWORD){

  String SSID{NAME};
  String PASS{PASSWORD};

  WiFi.begin(SSID, PASS);

  while(WiFi.status() != WL_CONNECTED){
    delay(100);
  }

}

//ToDo: Dont waste so much recourses
// String -> String -> char -> Base64 char -> String -> String
 void Toggl::setAuth(String const& Token){

  String TokenHolder{Token + ":api_token"};
  uint8_t Size{TokenHolder.length()+1};

  char Encoded[Size];
  char TESTBUFF[Size];

  TokenHolder.toCharArray(TESTBUFF,Size);

  int encoded_length = b64_encode(Encoded, TESTBUFF, Size-1);
  String Out{Encoded};

  AuthorizationKey = ("Basic " + Out);
}


const String Toggl::getUserData(String Input){

  if ((WiFi.status() == WL_CONNECTED)) {

      String payload{};
      String Output{};
      int16_t HTTP_Code{};

      std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
      client->setFingerprint("51240ac662cb06319ca77b133a9de73f6ba789bf"); // Fingerprint for Toggle API, expires on 01/10/2021

      HTTPClient https;
      https.begin(*client, "https://www.toggl.com/api/v8/me");
      https.addHeader("Authorization", AuthorizationKey);

      HTTP_Code = https.GET();

      if (HTTP_Code >= 200 && HTTP_Code <= 226){
          StaticJsonDocument<128> filter;
          filter["data"][Input] = true;

          const size_t capacity = 2*JSON_ARRAY_SIZE(0) + 3*JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(0) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(9) + JSON_OBJECT_SIZE(24) + 850;
          DynamicJsonDocument doc(capacity);

          deserializeJson(doc, https.getString(), DeserializationOption::Filter(filter));
          doc.shrinkToFit();

          const String TMP_Str = doc["data"][Input];
          Output = TMP_Str;
          doc.garbageCollect();
          filter.garbageCollect();

      }

      else{ // To return the error instead of the data, no idea why the built in espHttpClient "errorToString" only returns blank space when a known error occurs...
           Output = ("Error: " + String(HTTP_Code));
      }

      https.end();
      return Output;
  }

}


//POST & PUT request for handling the timer

const String Toggl::StartTimeEntry(String const& Description, String const& Tags, int const& PID,String const& CreatedWith){

  if ((WiFi.status() == WL_CONNECTED)) {

      String payload;

      std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
      client->setFingerprint("51240ac662cb06319ca77b133a9de73f6ba789bf"); // Fingerprint for Toggle API, expires on 01/10/2021

      HTTPClient https;
      https.begin(*client, "https://www.toggl.com/api/v8/time_entries/start");
      https.addHeader("Authorization", AuthorizationKey, true);
      https.addHeader("Content-Type", " application/json");

      const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(4) + 90;
      DynamicJsonDocument doc(capacity);

      doc["time_entry"]["description"] = Description;
      doc["time_entry"]["tags"] = Tags;
      doc["time_entry"]["pid"] = PID;
      doc["time_entry"]["created_with"] = CreatedWith;

      serializeJson(doc, payload);

      https.POST(payload);
      doc.clear();

      deserializeJson(doc, https.getString());

      String TimeID = doc["data"]["id"];

      doc.clear();
      doc.garbageCollect();
      https.end();
      
      return TimeID;
  }

}


const String Toggl::StopTimeEntry(String const& ID){

if ((WiFi.status() == WL_CONNECTED)) {

  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setFingerprint("51240ac662cb06319ca77b133a9de73f6ba789bf"); // Fingerprint for Toggle API, expires on 01/10/2021

  HTTPClient https;
  https.begin(*client, "https://www.toggl.com/api/v8/time_entries/" + ID +"/stop");
  https.addHeader("Authorization", AuthorizationKey, true);
  https.addHeader("Content-Type", " application/json");
  String TMP{String(https.PUT(" "))};
  https.end();
  
  return TMP;
     
  }

 else{
  return "Not connected to the internet";
 }
}


const String Toggl::CreateTimeEntry(String const& Description, String const& Tags, int const& Duration, String const& Start,  int const& PID, String const& CreatedWith){

  if ((WiFi.status() == WL_CONNECTED)) {

      String payload;

      std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
      client->setFingerprint("51240ac662cb06319ca77b133a9de73f6ba789bf"); // Fingerprint for Toggle API, expires on 01/10/2021

      HTTPClient https;
      https.begin(*client, "https://www.toggl.com/api/v8/time_entries");
      https.addHeader("Authorization", AuthorizationKey, true);
      https.addHeader("Content-Type", " application/json");

      const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(4) + 90;
      DynamicJsonDocument doc(capacity);

      doc["time_entry"]["description"] = Description;
      doc["time_entry"]["tags"] = Tags;
      doc["time_entry"]["duration"] = Duration;
      doc["time_entry"]["start"] = Start;
      doc["time_entry"]["pid"] = PID;
      doc["time_entry"]["created_with"] = CreatedWith;

      serializeJson(doc, payload);

      https.POST(payload);
      doc.clear();

      deserializeJson(doc, https.getString());

      String TimeID = doc["data"]["id"];

      doc.clear();
      doc.garbageCollect();
      https.end();
      
      return TimeID;
  }
}


const String Toggl::CreateTag(String const& Name, int const& WID){

  if ((WiFi.status() == WL_CONNECTED)) {

      String payload;

      std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
      client->setFingerprint("51240ac662cb06319ca77b133a9de73f6ba789bf"); // Fingerprint for Toggle API, expires on 01/10/2021

      HTTPClient https;
      https.begin(*client, "https://www.toggl.com/api/v8/tags");
      https.addHeader("Authorization", AuthorizationKey, true);
      https.addHeader("Content-Type", " application/json");

      const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(4) + 90;
      DynamicJsonDocument doc(capacity);

      doc["tag"]["name"] = Name;
      doc["tag"]["wid"] = WID;

      serializeJson(doc, payload);

      https.POST(payload);

      deserializeJson(doc, https.getString());
      String output = doc["data"]["id"];

      doc.clear();
      doc.garbageCollect();
      https.end();
      
      return output;

    }
}


const String Toggl::getWorkSpace(){

  if ((WiFi.status() == WL_CONNECTED)) {

      String Output{};
      uint16_t HTTP_Code{};

      std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
      client->setFingerprint("51240ac662cb06319ca77b133a9de73f6ba789bf"); // Fingerprint for Toggle API, expires on 01/10/2021

      DynamicJsonDocument doc(1024);

      StaticJsonDocument<50> filter;
      filter[0]["id"] = true;
      filter[0]["name"] = true;

      HTTPClient https;
      https.begin(*client, "https://www.toggl.com/api/v8/workspaces");
      https.addHeader("Authorization", AuthorizationKey, true);

      HTTP_Code = https.GET();

      if(HTTP_Code >= 200 && HTTP_Code <= 226){
        deserializeJson(doc, https.getString(), DeserializationOption::Filter(filter));
        serializeJsonPretty(doc, Output);
        doc.garbageCollect();
        filter.garbageCollect();
      }

      else{
        Output = ("Error: " + String(HTTP_Code));
      }

      https.end();
      return Output;

     }
}
#elif defined (ESP32)

void Toggl::init(const char* SSID,const char* PASS){

  
  WiFi.begin(SSID, PASS);

  while(WiFi.status() != WL_CONNECTED){
    delay(100);
  }

}
//Using built in ESP32 Base64 driver
void Toggl::setAuth(String const& Token){

  String TokenHolder{Token + ":api_token"};

  String Encoded = base64::encode(TokenHolder);

  AuthorizationKey = ("Basic " + Encoded);
  return;
}


//Get user data
const String Toggl::getUserData(String Input){

  if ((WiFi.status() == WL_CONNECTED)) {

      String payload{};
      String Output{};
      int16_t HTTP_Code{};

      HTTPClient https;
      https.begin("https://www.toggl.com/api/v8/me",Fingerprint);
      https.addHeader("Authorization", AuthorizationKey);
      
      HTTP_Code = https.GET();

      if (HTTP_Code >= 200 && HTTP_Code <= 226){
          StaticJsonDocument<128> filter;
          filter["data"][Input] = true;

          const size_t capacity = 2*JSON_ARRAY_SIZE(0) + 3*JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(0) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(9) + JSON_OBJECT_SIZE(24) + 850;
          DynamicJsonDocument doc(capacity);

          deserializeJson(doc, https.getString(), DeserializationOption::Filter(filter));
          doc.shrinkToFit();

          const String TMP_Str = doc["data"][Input];
          Output = TMP_Str;
          doc.garbageCollect();
          filter.garbageCollect();

      }

      else{ // To return the error instead of the data, no idea why the built in espHttpClient "errorToString" only returns blank space when a known error occurs...
           Output = ("Error: " + String(HTTP_Code));
      }

      https.end();
      return Output;
  }

}

const String Toggl::StartTimeEntry(String const& Description, String const& Tags, int const& PID,String const& CreatedWith){

  if ((WiFi.status() == WL_CONNECTED)) {

      String payload;

      
      HTTPClient https;
      https.begin("https://www.toggl.com/api/v8/time_entries/start", Fingerprint);
      https.addHeader("Authorization", AuthorizationKey, true);
      https.addHeader("Content-Type", " application/json");

      const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(4) + 90;
      DynamicJsonDocument doc(capacity);

      doc["time_entry"]["description"] = Description;
      doc["time_entry"]["tags"] = Tags;
      doc["time_entry"]["pid"] = PID;
      doc["time_entry"]["created_with"] = CreatedWith;

      serializeJson(doc, payload);

      https.POST(payload);
      doc.clear();

      deserializeJson(doc, https.getString());

      String TimeID = doc["data"]["id"];

      doc.clear();
      doc.garbageCollect();
      https.end();
      
      return TimeID;
  }

}


const String Toggl::StopTimeEntry(String const& ID){

  if ((WiFi.status() == WL_CONNECTED)) {

      HTTPClient https;
      https.begin("https://www.toggl.com/api/v8/time_entries/" + ID + "/stop", Fingerprint);
      
      https.addHeader("Authorization", AuthorizationKey, true);
      https.addHeader("Content-Type", " application/json");
      String TMP{String(https.PUT(" "))};
      https.end();
      
      return TMP;
      //return https.errorToString(https.PUT(" ")); // Not sure why it never returns anything, just a blank

      }

  else{
    return "Not connected to the internet";
  }
}


const String Toggl::CreateTimeEntry(String const& Description, String const& Tags, int const& Duration, String const& Start,  int const& PID, String const& CreatedWith){

  if ((WiFi.status() == WL_CONNECTED)) {

      String payload;
 
      HTTPClient https;
      https.begin("https://www.toggl.com/api/v8/time_entries", Fingerprint);
      https.addHeader("Authorization", AuthorizationKey, true);
      https.addHeader("Content-Type", " application/json");

      const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(4) + 90;
      DynamicJsonDocument doc(capacity);

      doc["time_entry"]["description"] = Description;
      doc["time_entry"]["tags"] = Tags;
      doc["time_entry"]["duration"] = Duration;
      doc["time_entry"]["start"] = Start;
      doc["time_entry"]["pid"] = PID;
      doc["time_entry"]["created_with"] = CreatedWith;

      serializeJson(doc, payload);

      https.POST(payload);
      doc.clear();

      deserializeJson(doc, https.getString());

      String TimeID = doc["data"]["id"];

      doc.clear();
      doc.garbageCollect();
      https.end();
      
      return TimeID;
  }
}


const String Toggl::CreateTag(String const& Name, int const& WID){

  if ((WiFi.status() == WL_CONNECTED)) {

      String payload;

      HTTPClient https;
      https.begin("https://www.toggl.com/api/v8/tags", Fingerprint);
      https.addHeader("Authorization", AuthorizationKey, true);
      https.addHeader("Content-Type", " application/json");

      const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(4) + 90;
      DynamicJsonDocument doc(capacity);

      doc["tag"]["name"] = Name;
      doc["tag"]["wid"] = WID;

      serializeJson(doc, payload);

      https.POST(payload);

      deserializeJson(doc, https.getString());
      String output = doc["data"]["id"];

      doc.clear();
      doc.garbageCollect();
      https.end();
      
      return output;

    }
}


const String Toggl::getWorkSpace(){

  if ((WiFi.status() == WL_CONNECTED)) {

      String Output{};
      uint16_t HTTP_Code{};

      DynamicJsonDocument doc(1024);

      StaticJsonDocument<50> filter;
      filter[0]["id"] = true;
      filter[0]["name"] = true;

      HTTPClient https;
      https.begin("https://www.toggl.com/api/v8/workspaces", Fingerprint);
      https.addHeader("Authorization", AuthorizationKey, true);

      HTTP_Code = https.GET();

      if(HTTP_Code >= 200 && HTTP_Code <= 226){
        deserializeJson(doc, https.getString(), DeserializationOption::Filter(filter));
        serializeJsonPretty(doc, Output);
        doc.garbageCollect();
        filter.garbageCollect();
      }

      else{
        Output = ("Error: " + String(HTTP_Code));
      }

      https.end();
      return Output;

     }
}


#endif


//ToDo: For all GET requests. Better memory handling
//GET requests for user Data

const uint16_t Toggl::getID(){

    const uint16_t output = (getUserData("id")).toInt();

    return output;
}


const String Toggl::getApiToken(){

    return getUserData("api_token");

}


const uint16_t Toggl::getDefaultWid(){

    const uint16_t output = (getUserData("default_wid")).toInt();

    return output;

}


const String Toggl::getEmail(){

    return getUserData("email");
}


const String Toggl::getFullName(){

    return getUserData("fullname");

}


const String Toggl::getJqTimeOfDayFormat(){

    return getUserData("jquery_timeofday_format");
}


const String Toggl::getJqDateFormat(){

    return getUserData("jquery_date_format");
}


const String Toggl::getTimeOfDayFormat(){

    return getUserData("timeofday_format");
}


const String Toggl::getDateFormat(){

    return getUserData("date_format");
}


const bool Toggl::getStoreStartAndStopTime(){

    return getUserData("store_start_and_stop_time");

}


const uint16_t Toggl::getBeginningOfWeek(){

    // Not sure why a uint8_t creates a stack overflow
    const uint16_t output = (getUserData("beginning_of_week")).toInt();

    return output;

}


const String Toggl::getLang(){

    return getUserData("language");

}


const String Toggl::getDurationFormat(){

    return getUserData("duration_format");
}


const String Toggl::getAt(){

    return getUserData("at");

}


const String Toggl::getCreation(){

    return getUserData("created_at");
}


const String Toggl::getTimezone(){

    return getUserData("timezone");
}

#if defined (ESP32)

#include "Toggl.h"


Toggl::Toggl(){

}


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
      https.begin("https://api.track.toggl.com/api/v8/me",Fingerprint);
      https.addHeader("Authorization", AuthorizationKey);
      
      HTTP_Code = https.GET();

      if (HTTP_Code >= 200 && HTTP_Code <= 226){
          StaticJsonDocument<80> filter;
          filter["data"][Input] = true;

          DynamicJsonDocument doc(2*JSON_OBJECT_SIZE(1) + 60);
          deserializeJson(doc, https.getString(), DeserializationOption::Filter(filter));

          String TMP_Str = doc["data"][Input];
          Output = TMP_Str;
          
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

const String Toggl::StartTimeEntry(String const& Description, String const& Tags, int const& PID,String const& CreatedWith){

  if ((WiFi.status() == WL_CONNECTED)) {

      String payload;
      
      HTTPClient https;
      https.begin("https://api.track.toggl.com/api/v8/time_entries/start", Fingerprint);
      https.addHeader("Authorization", AuthorizationKey, true);
      https.addHeader("Content-Type", " application/json");

      DynamicJsonDocument doc(JSON_ARRAY_SIZE(1) +JSON_OBJECT_SIZE(5 + 1));

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

  String Output{};
  
  if ((WiFi.status() == WL_CONNECTED)) {

      HTTPClient https;
      https.begin("https://api.track.toggl.com/api/v8/time_entries/" + ID + "/stop", Fingerprint);
      
      https.addHeader("Authorization", AuthorizationKey, true);
      https.addHeader("Content-Type", " application/json");
      Output = String(https.PUT(" "));
      https.end();
      
      //return https.errorToString(https.PUT(" ")); // Not sure why it never returns anything, just a blank

      }

  else{
    Output = "Not connected to the internet";
  }
  return Output;
}


const String Toggl::CreateTimeEntry(String const& Description, String const& Tags, int const& Duration, String const& Start,  int const& PID, String const& CreatedWith){

  if ((WiFi.status() == WL_CONNECTED)) {

      String payload;
 
      HTTPClient https;
      https.begin("https://api.track.toggl.com/api/v8/time_entries", Fingerprint);
      https.addHeader("Authorization", AuthorizationKey, true);
      https.addHeader("Content-Type", " application/json");

      DynamicJsonDocument doc(JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(6)+ 50);

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
      https.begin("https://api.track.toggl.com/api/v8/tags", Fingerprint);
      https.addHeader("Authorization", AuthorizationKey, true);
      https.addHeader("Content-Type", " application/json");
      
      DynamicJsonDocument doc(JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(3));

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

//Returns Workplace ID (WID)
const String Toggl::getWorkSpace(){

  if ((WiFi.status() == WL_CONNECTED)) {

      String Output{};
      uint16_t HTTP_Code{};
      
      HTTPClient https;
      https.begin("https://api.track.toggl.com/api/v8/workspaces", Fingerprint);
      https.addHeader("Authorization", AuthorizationKey, true);

      HTTP_Code = https.GET();

      if(HTTP_Code >= 200 && HTTP_Code <= 226){

        DynamicJsonDocument doc(1024);
  
        StaticJsonDocument<50> filter;
        filter[0]["id"] = true;
        filter[0]["name"] = true;
        
        deserializeJson(doc, https.getString(), DeserializationOption::Filter(filter));     
              
        JsonArray arr = doc.as<JsonArray>();

        for (JsonVariant value : arr) {        
          
          const int TmpID{value["id"]};
          Output += TmpID;
          Output += "\n";
          String TmpName = value["name"];
          Output += TmpName + "\n" + "\n";

        }
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


const String Toggl::getProject(int const& WID){
  
  if ((WiFi.status() == WL_CONNECTED)) {

      String Output{};
      uint16_t HTTP_Code{};
      
      DynamicJsonDocument doc(1024);

      StaticJsonDocument<50> filter;
      filter[0]["id"] = true;
      filter[0]["name"] = true;
      HTTPClient https;
      https.begin("https://api.track.toggl.com/api/v8/workspaces/" + String(WID) + "/projects", Fingerprint);
      https.addHeader("Authorization", AuthorizationKey, true);

      HTTP_Code = https.GET();

      if(HTTP_Code >= 200 && HTTP_Code <= 226){
        
        deserializeJson(doc, https.getString(), DeserializationOption::Filter(filter));     
        
        
        JsonArray arr = doc.as<JsonArray>();


        for (JsonVariant value : arr) {        
          
          const int TmpID{value["id"]};
          Output += TmpID;
          Output += "\n";
          String TmpName = value["name"];
          Output += TmpName + "\n" + "\n";

        }
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

/*
//ToDo make the code somewhat nicer.
const int Toggl::getPID(String const& WID ,String const& ProjectName){

  int output{};
  
  String TMP_String = getProject(WID);

  Serial.println(TMP_String);
  

  
  return output;
}
*/

const String  Toggl::getTimerData(String Input){

  if ((WiFi.status() == WL_CONNECTED)) {

      String payload{};
      String Output{};
      int16_t HTTP_Code{};

      HTTPClient https;
      https.begin("https://api.track.toggl.com/api/v8/time_entries/current",Fingerprint);
      https.addHeader("Authorization", AuthorizationKey);
      
      HTTP_Code = https.GET();

      if (HTTP_Code >= 200 && HTTP_Code <= 226){
          StaticJsonDocument<46> filter;
          filter["data"][Input] = true;

          DynamicJsonDocument doc(JSON_OBJECT_SIZE(4));

          deserializeJson(doc, https.getString(), DeserializationOption::Filter(filter));

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

//This got to go...
const uint32_t  Toggl::getCurrentTime(const String Timezone){

  if ((WiFi.status() == WL_CONNECTED)) {

      int16_t HTTP_Code{};
      uint32_t Output{};
      HTTPClient http;
      
      http.begin("http://worldtimeapi.org/api/timezone/" + Timezone);
    
      HTTP_Code = http.GET();
      
      if (HTTP_Code >= 200 && HTTP_Code <= 226){
          StaticJsonDocument<21> filter;
          filter["unixtime"] = true;

          const size_t capacity = JSON_OBJECT_SIZE(2);
          DynamicJsonDocument doc(capacity);

          deserializeJson(doc, http.getString(), DeserializationOption::Filter(filter));

          Output = doc["unixtime"];
          doc.garbageCollect();
          filter.garbageCollect();

      }

      else{
        HTTP_Code;
      }

      http.end();
      return Output;
      }
}


/*
 * Since the duration is in the epoch time format i need to convert it to regular secconds.
 * This is done by taking "current time" + "Duration" resulting in duration in secconds. 
 * 
 * The JSON request for getting the time when the timer started does not include the time zone....
 * 
 * This function makes me cry :'(
 */

//Not even sure if i can do this properly. Il just use the World Time API for now...
const int32_t Toggl::getTimerDuration(){
  
  uint32_t Output{};
  const int32_t Duration = (getTimerData("duration")).toInt();

  if (Duration < 0){
    Output = getCurrentTime(getTimezone()) + Duration;
  }

  else{
    Output = 0;
  }
  
  return Output;
}

const bool Toggl::isTimerActive(){

  bool output;
  
  String wid = getTimerData("wid"); //Just using a filter for less data.

  if(wid != "null"){
    output = true;
  }
  
  else{
    output = false;
  }
  
  return output;
}

const String  Toggl::getTimerID(){

  return getTimerData("id");
  
}




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

#endif

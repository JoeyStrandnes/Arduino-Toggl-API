

#include "Toggl.h"


Toggl::Toggl(){

}

   
void Toggl::init(String const& SSID, String const& PASS){


  WiFi.begin(SSID, PASS);

  while(WiFi.status() != WL_CONNECTED){
    delay(100);
  }

}

//ToDo: Dont waste so much recourses
// String -> String -> char -> Base64 char -> String -> String
 void Toggl::setAuth(String const Token){

  String TokenHolder{Token + ":api_token"};
  //Serial.println(TokenHolder);
  uint8_t Size{TokenHolder.length()+1};
  
  char Encoded[Size];
  char TESTBUFF[Size];
  
  TokenHolder.toCharArray(TESTBUFF,Size);

  /*
  Serial.println(Size);
  Serial.println(sizeof(TESTBUFF));
  Serial.println(TESTBUFF);
  */
  int encoded_length = b64_encode(Encoded, TESTBUFF, Size-1);
  String Out{Encoded};
  //Serial.println(Out);
  
  
  AuthorizationKey = ("Basic " + Out);
}


String Toggl::getUserData(String Input){

  if ((WiFi.status() == WL_CONNECTED)) {
      String payload{};
      
      
      std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
      client->setFingerprint("51240ac662cb06319ca77b133a9de73f6ba789bf"); // Fingerprint for Toggle API, expires on 01/10/2021
      
      HTTPClient https;
      https.begin(*client, "https://www.toggl.com/api/v8/me");
      https.addHeader("Authorization", AuthorizationKey);

      https.GET();
      payload = https.getString();
      https.end();
      
      StaticJsonDocument<1024> doc;

      deserializeJson(doc, payload);
      const String Output = doc["data"][Input];
      doc.clear();
      return Output;
  }
    
}

/*
int Toggl::CreateTag(String const Name){

  if ((WiFi.status() == WL_CONNECTED)) {
    
      std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
      client->setFingerprint("51240ac662cb06319ca77b133a9de73f6ba789bf"); // Fingerprint for Toggle API, expires on 01/10/2021
      
      HTTPClient https;
      https.begin(*client, "https://www.toggl.com/api/v8/tags");
      https.addHeader("Authorization", AuthorizationKey, true);
      https.addHeader("Content-Type", " application/json");

      DynamicJsonDocument doc2(512);
      doc2["tag"]["name"] = Name;
      doc2["tag"]["wid"] = 0;
      
      String Out{};

      //char Out[] = "{"tag"\n""{\n""name\":\"HelloWorld\"\n""wid\":\"666\"}\n""}"; 
      serializeJson(doc2, Out);

      Serial.println(Out);
      

      int https_Code{};
      https_Code = https.POST(Out);

      Serial.println(https.getString());
      https.end();

      return https_Code;

    
  }
}

String Toggl::StartTimeEntry(){

  if ((WiFi.status() == WL_CONNECTED)) {

      std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
      client->setFingerprint("51240ac662cb06319ca77b133a9de73f6ba789bf"); // Fingerprint for Toggle API, expires on 01/10/2021
      
      HTTPClient https;
      https.begin(*client, "https://www.toggl.com/api/v8/time_entries/start");
      https.addHeader("Authorization", AuthorizationKey, true);
      https.addHeader("Content-Type", " application/json");
      
      DynamicJsonDocument doc(100);
      doc["time_entry"]["description"] = "HelloWorld";
      doc["time_entry"]["tags"] = "TEST";
      doc["time_entry"]["pid"] = 159958000;
      doc["time_entry"]["created_with"] = "ESP";
      
      String Out{};
      //String TimeID{};
      
      serializeJson(doc, Out);
      
      //Serial.println(Out);
    
      https.POST(Out);
      doc.clear();
      
      doc = https.getString();
      String TimeID = doc["data"]["id"];
      
      //serializeJson(TMP_T, TimeID);
      return TimeID;
  }
  
    //return ("Error");
  
}

int Toggl::StopTimeEntry(String ID){
  
if ((WiFi.status() == WL_CONNECTED)) {

      std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
      client->setFingerprint("51240ac662cb06319ca77b133a9de73f6ba789bf"); // Fingerprint for Toggle API, expires on 01/10/2021
      
      HTTPClient https;
      https.begin(*client, "https://www.toggl.com/api/v8/time_entries/stop");
      https.addHeader("Authorization", AuthorizationKey, true);
      https.addHeader("Content-Type", " application/json");
      

      
      int https_Code{};      
      https_Code = https.PUT(ID);
      
      Serial.println(https.getString());
      return https_Code;
  }
  
    //return ("Error");
  

  
}
void Toggl::getWorkspace(){

      std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
      client->setFingerprint("51240ac662cb06319ca77b133a9de73f6ba789bf"); // Fingerprint for Toggle API, expires on 01/10/2021
      
      HTTPClient https;
      https.begin(*client, "https://www.toggl.com/api/v8/tags");
      https.addHeader("Authorization", AuthorizationKey, true);

      Serial.println(https.GET());
      Serial.println(https.getString());
      https.end();
}

*/
//ToDo: For all GET requests. Remove the need for the temporary JSON document for every request.

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






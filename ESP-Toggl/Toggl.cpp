

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


DynamicJsonDocument Toggl::getUserData(){

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
      
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);
      
      return doc;
  }
  
    //return ("Error");
  
}


int Toggl::StartTimeEntry(){

  if ((WiFi.status() == WL_CONNECTED)) {

      std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
      client->setFingerprint("51240ac662cb06319ca77b133a9de73f6ba789bf"); // Fingerprint for Toggle API, expires on 01/10/2021
      



/*
      {"time_entry":{"description":"Meeting with possible clients","tags":["billed"],"pid":123,"created_with":"curl"}}

      
      {
        "time_entry":{
        
          "description":"Meeting with possible clients",
          "tags":["billed"],
          "pid":123,
          "created_with":"curl",
          }
        }
      
      DynamicJsonDocument doc2(512);
      doc2["time_entry"]["description"] = "New time entry";
      doc2["time_entry"]["tags"] = "TEST";
      doc2["time_entry"]["pid"] = 123;
      doc2["time_entry"]["created_with"] = "ESP";
      */
      const char* doc2 = "{\"time_entry\":{\"description\":\"Hello World\",\"tags\":[\"billed\"],\"pid\":123,\"created_with\":\"curl\"}}";
      https.POST(doc2);

      https.end();
      
      return https.GET();
  }
  
    //return ("Error");
  
}

//ToDo: For all GET requests. Remove the need for the temporary JSON document for every request.
const uint16_t Toggl::getID(){
    
    DynamicJsonDocument doc{getUserData()};
    const uint16_t output = doc["data"]["id"];

    return output;
}

const String Toggl::getApiToken(){

    DynamicJsonDocument doc{getUserData()};
    const String output = doc["data"]["api_token"];

    return output;
  
}

const uint16_t Toggl::getDefaultWid(){

    DynamicJsonDocument doc{getUserData()};
    const uint16_t output = doc["data"]["default_wid"];

    return output;
  
}


const String Toggl::getEmail(){
    
    DynamicJsonDocument doc{getUserData()};
    const String output = doc["data"]["email"];

    return output;
}

const char* Toggl::getFullName(){

    DynamicJsonDocument doc{getUserData()};
    const char* output = doc["data"]["fullname"];

    return output;

}

const String Toggl::getJqTimeOfDayFormat(){

    DynamicJsonDocument doc{getUserData()};
    const String output = doc["data"]["jquery_timeofday_format"];

    return output;
}

const String Toggl::getJqDateFormat(){

    DynamicJsonDocument doc{getUserData()};
    const String output = doc["data"]["jquery_date_format"];

    return output;
}


const String Toggl::getTimeOfDayFormat(){
    
    DynamicJsonDocument doc{getUserData()};
    const String output = doc["data"]["timeofday_format"];

    return output;
}

const String Toggl::getDateFormat(){
    
    DynamicJsonDocument doc{getUserData()};
    const String output = doc["data"]["date_format"];

    return output;
}


const bool Toggl::getStoreStartAndStopTime(){
    
    DynamicJsonDocument doc{getUserData()};
    const bool output = doc["data"]["store_start_and_stop_time"];

    return output;
}


const uint8_t Toggl::getBeginningOfWeek(){

    DynamicJsonDocument doc{getUserData()};
    const uint8_t output = doc["data"]["beginning_of_week"];

    return output;
  
}


const char* Toggl::getLang(){

    DynamicJsonDocument doc{getUserData()};
    const char* output = doc["data"]["language"];

    return output;
  
}



const char* Toggl::getDurationFormat(){

    DynamicJsonDocument doc{getUserData()};
    const char* output = doc["data"]["duration_format"];

    return output;
}

const String Toggl::getAt(){
    
    DynamicJsonDocument doc{getUserData()};
    const String output = doc["data"]["at"];

    return output;
  
}

const String Toggl::getCreation(){
    
    DynamicJsonDocument doc{getUserData()};
    const String output = doc["data"]["created_at"];

    return output;
}

const String Toggl::getTimezone(){

    DynamicJsonDocument doc{getUserData()};
    const String output = doc["data"]["timezone"];

    return output;

  
}







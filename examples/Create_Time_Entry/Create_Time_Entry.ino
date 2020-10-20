/*
This example will:
Create a time entry that lasts 1 hour with a description "HelloWorld", use the tag "TagName", and created by "ESP".
*/

#include <Toggl.h>

const char* SSID{"SSID"};
const char* PASS{"PASSWORD"};


String const Token{"TOKEN"};               //API Token is found in "Profile Settings" 

// Timer details
char* const Description{"HelloWorld!"};   //Description of time entry.
char* const Tag{""};                      //Tag name, leave empty if no tag is used. 
int   const Duration{3600};               //Duration in secconds.
int   const PID{123456789};               //Project ID is specific to each user project.
char* const CreatedWith{"ESP"};

Toggl toggl;

void setup(){

  toggl.init(SSID,PASS);  
  toggl.setAuth(Token);


  CreateTimeEntry(String Description, String Tags, int Duration, String Start, int PID, String CreatedWith); // Returns the timer ID as a String
  
}


void loop(){
  
}

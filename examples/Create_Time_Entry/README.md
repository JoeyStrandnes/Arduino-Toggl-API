# Create a time entry.

#### This example will:

##### Create a time entry that lasts 1 hour with a description "HelloWorld" and created by "ESP"

```c++

#include <Toggl.h>

char* const SSID{"SSID"};
char* const PASS{"PASSWORD"};


String const Token{"TOKEN"};                  //API Token is found in "Profile Settings" 

// Timer details
char* const Description{"HelloWorld!"};       //Description of time entry.
char* const Tag{""};                          //Tag name, leave empty if no tag is used. 
int   const Duration{3600};                   //Duration in secconds.
char* const Start{"2020-09-24T12:00:00.000Z"};//Start time in ISO 8601 format.
int   const PID{123456789};                   //Project ID is specific to each user project.
char* const CreatedWith{"ESP"};               //Name of "client".

Toggl toggl;

void setup(){

  toggl.init(SSID,PASS);  
  toggl.setAuth(Token);

  toggl.CreateTimeEntry(Description, Tag, Duration, Start, PID, CreatedWith);
  
}


void loop(){
  
}
```


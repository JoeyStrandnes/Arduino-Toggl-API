/*
This example will:
Print the Username and Time zone to the terminal.
Start a timer with a description "HelloWorld", use the tag "TagName", and
created by "ESP". The PID must be collected by the user at the moment.

The timer will be stopped after ~10 seconds
*/

#include <Toggl.h>

char *const SSID{"SSID"};
char *const PASS{"PASSWORD"};

String const Token{"TOKEN"};            // API Token is found in "Profile Settings"

// Timer details
char *const Description{"HelloWorld!"}; // Description of time entry.
char *const Tag{""};                    // Tag name, leave empty if no tag is used.
int   const PID{123456789};             // Project ID is specific to each user project.
char *const CreatedWith{"ESP"};         // Name of "client".


String TimerID{};                       // Place holder for timer ID.


Toggl toggl;

void setup() {
  Serial.begin(115200);

  toggl.init(SSID, PASS);
  toggl.setAuth(Token);

  Serial.println(toggl.getFullName());
  Serial.println(toggl.getTimezone());

  TimerID = (toggl.StartTimeEntry(Description, Tag, PID, CreatedWith));
  delay(10000);
  Serial.println(toggl.StopTimeEntry(TimerID));
}

void loop() {

}

/*
Uses a momentary button to start a time entry and light a LED. 
The Timer will stop when the button is pressed a seccond time.
*/

#include <Toggl.h>

const char* SSID = "SSID";
const char* PASS = "PASSWORD";


String TimerID{};
int const PID{123456789};                   //Project ID is specific to each user project
String const Token{"TOKEN"};                //API Token is found in "Profile Settings" 

const int buttonPin = D7;
const int ledPin =  D8;

int buttonState = 0;
bool TOGGLE = true;
bool BUTTON = false;


void ICACHE_RAM_ATTR handleInterrupt ();


Toggl toggl;


void setup(){

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleInterrupt, FALLING); // Triggers on falling edge, change it to "RISING" depending on your button.
  
  toggl.init(SSID,PASS);
  toggl.setAuth(Token);
    
}


void handleInterrupt() {
  BUTTON = true;
}



void loop(){

  if(TOGGLE == true && BUTTON == true){
    digitalWrite(ledPin, HIGH);
    TimerID = (toggl.StartTimeEntry("HelloWorld", "TagName", PID, "ESP-Button"));
    TOGGLE = false;
    BUTTON = false;
    delay(1000);   
  }


  if (TOGGLE == false && BUTTON == true){
    digitalWrite(ledPin, LOW);
    toggl.StopTimeEntry(TimerID);
    TOGGLE = true;
    BUTTON = false;
    delay(1000);
  }
}

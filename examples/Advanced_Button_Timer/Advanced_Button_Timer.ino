/*
This is an "advanced" version of the Button example.

It uses a momentary button to start and stop a timer.
The timer will start if no timer is active, otherwise it will stop the timer.

A LED will light up and indicate if a timer is started or running.
The LED will turn of if the timer is stopped either through a button press or the website.

*/

#include <Toggl.h>

const char* SSID = "SSID";
const char* PASS = "PASSWORD";

// Toggl information
int const PID{123456789};                   //Project ID is specific to each user project
String const Token{"TOKEN"};                //API Token is found in "Profile Settings" 

char const Description[]{"HelloWorld"};     // Timer description
char const TagName[]{" "};                  // Timer tag name



const int ButtonPin = D7;
const int LedPin =  D8;

bool TOGGLE = true;
bool BUTTON = false;
bool TimerActive = false;


void ICACHE_RAM_ATTR HandleInterrupt();


Toggl toggl;


void setup(){

  pinMode(LedPin, OUTPUT);
  pinMode(ButtonPin, INPUT);
  digitalWrite(LedPin, LOW);
  Serial.begin(115200);
  
  attachInterrupt(digitalPinToInterrupt(ButtonPin), HandleInterrupt, FALLING); // Triggers on falling edge, change it to "RISING" depending on your button.
  
  toggl.init(SSID,PASS);
  toggl.setAuth(Token);
    
}


void HandleInterrupt() {
  BUTTON = true;
}



void loop(){

  TimerActive = toggl.isTimerActive();

  // Button is pressed and the timer starts
  if(TOGGLE == true && BUTTON == true && TimerActive == false){
    digitalWrite(LedPin, HIGH);
    toggl.StartTimeEntry(Description, TagName, PID, "ESP");
    TimerActive = true;
    TOGGLE = false;
    BUTTON = false;   
  }

  // Button is pressed and the timer stops
  if (TOGGLE == false && BUTTON == true && TimerActive == true){
    digitalWrite(LedPin, LOW);
    toggl.StopTimeEntry(toggl.getTimerID());
    TimerActive = false;
    TOGGLE = true;
    BUTTON = false;
  }

  // Keeping LED active if timer is running
  else if(TimerActive == true){
    digitalWrite(LedPin, HIGH);
    TOGGLE = false;
  }
  
  // Keeping LED off if timer is not running
  else if (TimerActive == false){
    digitalWrite(LedPin, LOW);
    TOGGLE = true;   
  }
}

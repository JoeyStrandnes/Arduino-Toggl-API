#include <Toggl.h>

const char* SSID = "";
const char* PASS = "";

String const Token {""}; //API Token is found in "Profile Settings"

Toggl toggl;

void setup() {
  Serial.begin(115200);
  toggl.init(SSID, PASS);
  toggl.setAuth(Token);
  delay(100);
  Serial.println("Get all projects for all workspaces");
  KVReturn workspaces = toggl.getWorkSpaces();
  KVReturn projects;
  if (workspaces.HTTPCode >= 200 && workspaces.HTTPCode <= 226) {
    Serial.println("There are " + String(workspaces.pairCount) + " workspaces");

    for (int i = 0; i < workspaces.pairCount; i++) {
      projects = toggl.getProjects(workspaces.KVPairs[i].id);
      if (projects.HTTPCode >= 200 && projects.HTTPCode <= 226) {
        Serial.println("There are " + String(projects.pairCount) + " projects in workspace " + workspaces.KVPairs[i].name);
        for (int i = 0; i < projects.pairCount; i++) {
          Serial.println(String(projects.KVPairs[i].id) + ": " + projects.KVPairs[i].name);
        }
        projects.KVPairs = NULL; // set to null here, as we plan to use this again later.
      }
      else {
        Serial.println("Failed to get projects with HTTPCode " + String(projects.HTTPCode));
      }
    }
  }
  else {
    Serial.println("Failed to get workspaces with HTTPCode " + String(workspaces.HTTPCode));
  }

  delete[] workspaces.KVPairs; // we're done with the workspace KVPairs
  delete[] projects.KVPairs; // we're done with the project KVPairs

}

void loop() {
}

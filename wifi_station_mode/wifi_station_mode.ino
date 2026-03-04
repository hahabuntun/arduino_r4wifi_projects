#include <WiFiS3.h>

const char *ssid_Router     = "L7242 - 2.4 Ggz";
const char *password_Router = "B4AS1UHKch";

void setup(){
  Serial.begin(115200);
  delay(2000);
  Serial.println("Setup start");
  
  WiFi.begin(ssid_Router, password_Router);
  Serial.println(String("Connecting to ")+ssid_Router);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    attempts++;
    
    if (attempts > 20) {  // Stop after 10 seconds if no connection
      Serial.println("Failed to connect.");
      break;
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected, IP address: ");
    Serial.println(WiFi.gatewayIP());
  } else {
    Serial.println("\nCould not connect to WiFi.");
  }

  Serial.println("Setup End");
}

void loop() {
  // put your main code here, to run repeatedly:
}
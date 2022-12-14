#include <WiFi.h>
#include "ThingSpeak.h"

#include <BH1750.h>
#include <Wire.h>

BH1750 lightMeter;

const char* ssid = "MySSID";   // replace MySSID with your WiFi network name
const char* pass = "MyPassword";   // replace MyPassword with your WiFi password

WiFiClient  client;

unsigned long myChannelNumber = 0000000; // replace 0000000 with your channel number
const char * myWriteAPIKey = "XYZ"; // replace XYZ with your channel write API Key

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

void setup() {
  Serial.begin(115200);  // Initialize serial 

  WiFi.mode(WIFI_MODE_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak

  Wire.begin();
  lightMeter.begin();
}

void loop() {

  if ((millis() - lastTime) > timerDelay) {

    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect to SSID: ");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
        Serial.print(".");
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }

    float lux = lightMeter.readLightLevel();
    float fps = 30;
    float r = 0;
    float n = 50;

    // set the fields with the values
    ThingSpeak.setField(1, lux);
    ThingSpeak.setField(2, fps);
    ThingSpeak.setField(3, r);
    ThingSpeak.setField(4, n);
       
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
}

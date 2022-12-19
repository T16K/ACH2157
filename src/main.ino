#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "MySSID";   // replace MySSID with your WiFi network name
const char* password = "MyPassword";   // replace MyPassword with your WiFi password

unsigned long myChannelNumber = 0000000; // replace 0000000 with your channel number
const char * myWriteAPIKey = "XYZ"; // replace XYZ with your channel write API Key

WiFiClient  client;

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

int UVOUT = 34; //Output from the sensor
float n = 0; // Update time

void setup() {
  Serial.begin(115200);  // Initialize serial 

  WiFi.mode(WIFI_MODE_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak

  pinMode(UVOUT, INPUT);
}

// Takes an average of readings on a given pin
// Returns the average
int averageAnalogRead(int pinToRead) {
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 

  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return(runningValue);  
}

// The Arduino Map function for floats
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void loop() {

  if ((millis() - lastTime) > timerDelay) {

    if(WiFi.status() != WL_CONNECTED) {
      Serial.print("Attempting to connect to SSID: ");
      while(WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, password); // Connect to WPA/WPA2 network.
        Serial.print(".");
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }

    int uvLevel = averageAnalogRead(UVOUT);
  
    // Use the 3.3V power pin as a reference to get a very accurate output value from sensor
    float outputVoltage = 3.3 / 4095 * uvLevel;

    // Convert the voltage to a UV intensity level
    float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); 

    // Update time every 30 second
    n = n + 0.5;

    // Set the fields with the values
    ThingSpeak.setField(1, uvIntensity);
    thingSpeak.setfield(4, n);
       
    // Write to ThingSpeak
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if(x == 200) {
      Serial.println("Channel update successful.");
    }
    else {
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
}

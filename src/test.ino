#include <WiFi.h>
#include "ThingSpeak.h"

#include <BH1750.h>
#include <Wire.h>

#include <Arduino.h>
#include <ML8511.h>

const char* ssid = "";   // your network SSID (name) 
const char* password = "";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 1;
const char * myWriteAPIKey = "";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 20000;

int UVsensorIn = 4; //Output from the sensor

BH1750 lightMeter;

void setup() {
  Serial.begin(115200);  // Initialize serial 
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  lightMeter.begin();

  pinMode(UVsensorIn, INPUT);
}

//Takes an average of readings on a given pin
//Returns the average
int averageAnalogRead(int pinToRead) {
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 

  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return(runningValue);  
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }

    float lux = lightMeter.readLightLevel();
    
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");
    
    int uvLevel = averageAnalogRead(UVsensorIn);
 
    float outputVoltage = 3.3 * uvLevel/4095;
    float uvIntensity = mapfloat(outputVoltage, 0.99, 2.9, 0.0, 15.0);
 
    Serial.print("UV Intensity: ");
    Serial.print(uvIntensity);
    Serial.print(" mW/cm^2"); 
    Serial.println(); 

    // set the fields with the values
    ThingSpeak.setField(1, lux);
    ThingSpeak.setField(2, uvIntensity);
       
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

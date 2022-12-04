#include <WiFi.h>
#include "ThingSpeak.h"

#include <BH1750.h>
#include <Wire.h>

const char* ssid = "SSID";   // your network SSID (name) 
const char* password = "password";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 1;
const char * myWriteAPIKey = "APIKey";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 20000;

//Hardware pin definitions
int UVOUT = 2; //Output from the sensor
int REF_3V3 = 4; //3.3V power on the Arduino board

BH1750 lightMeter;

void setup() {
  Serial.begin(115200);  // Initialize serial
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  lightMeter.begin();
    
  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);
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

    int uvLevel = averageAnalogRead(UVOUT);
    int refLevel = averageAnalogRead(REF_3V3);

    //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
    float outputVoltage = 3.3 / refLevel * uvLevel;

    //Convert the voltage to a UV intensity level
    float UV = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0);

    // set the fields with the values
    ThingSpeak.setField(1, lux);
    ThingSpeak.setField(2, UV);
       
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

//Takes an average of readings on a given pin
//Returns the average
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 

  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return(runningValue);  
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
#include <WiFi.h>
#include "ThingSpeak.h"

#include <BH1750.h>
#include <Wire.h>

#include <Arduino.h>
#include <ML8511.h>

const char* ssid = "Zetakron";   // your network SSID (name) 
const char* password = "tk02463al27618";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 1;
const char * myWriteAPIKey = "98PNN4DP3RW17W4P";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 20000;

int UVOUT = 15; //Output from the sensor
int REF_3V3 = 4; //3.3V power on the ESP32 board

BH1750 lightMeter;

void setup() {
  Serial.begin(115200);  // Initialize serial 
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  lightMeter.begin();

  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);

  WiFi.begin(ssid, password); 
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

  float lux = lightMeter.readLightLevel();
    
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
    
  int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);
  
  //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
  float outputVoltage = 3.3 / refLevel * uvLevel;
  
  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); //Convert the voltage to a UV intensity level
 
  Serial.print("output: ");
  Serial.print(refLevel);
 
  Serial.print(" / ML8511 output: ");
  Serial.print(uvLevel);
 
  Serial.print(" / ML8511 voltage: ");
  Serial.print(outputVoltage);
 
  Serial.print(" / UV Intensity (mW/cm^2): ");
  Serial.print(uvIntensity);
  
  Serial.println();

  delay(1000);

  if ((millis() - lastTime) > timerDelay) {

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

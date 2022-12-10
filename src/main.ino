#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "MySSID";   // replace MySSID with your WiFi network name
const char* pass = "MyPassword";   // replace MyPassword with your WiFi password

WiFiClient  client;

unsigned long myChannelNumber = 0000000; // replace 0000000 with your channel number
const char * myWriteAPIKey = "XYZ"; // replace XYZ with your channel write API Key

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

int UVOUT = 34; //Output from the sensor
//int REF_3V3 = 35; //3.3V power on the ESP32 board

void setup() {
  Serial.begin(115200);  // Initialize serial 

  WiFi.mode(WIFI_MODE_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak

  pinMode(UVOUT, INPUT);
  //pinMode(REF_3V3, INPUT); 
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

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void loop() {

  if ((millis() - lastTime) > timerDelay) {

    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect to SSID: ");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
        Serial.print(".");
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }

    int uvLevel = averageAnalogRead(UVOUT);
    //int refLevel = averageAnalogRead(REF_3V3);
  
    //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
    //float outputVoltage = 3.3 / refLevel * uvLevel;
    float outputVoltage = 3.3 / 4095 * uvLevel;

    //Convert the voltage to a UV intensity level
    float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); 

    // set the fields with the values
    ThingSpeak.setField(1, uvIntensity);
       
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

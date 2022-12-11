#include <WiFi.h>
#include <WebServer.h>

// SSID & Password
const char* ssid = "SSID";  // Enter your SSID here
const char* password = "13742654800";  //Enter your Password here

// SSID & Password
const char* ap_ssid = "ESP32";  // Enter your SSID here
const char* ap_password = "13742654800";  //Enter your Password here

// Object of WebServer(HTTP port, 80 is defult)
WebServer server(80);

void setup() {
  Serial.begin(115200);

  // Set the Wi-Fi mode
  WiFi.mode(WIFI_MODE_APSTA);
 
  //Create the Access point
  WiFi.softAP(ap_ssid, ap_password);

  Serial.print("ESP32 IP as soft AP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handle_root);

  server.begin();
  
  Serial.println("HTTP server started");
  delay(100);
}

void loop() {

  int num_devices = WiFi.softAPgetStationNum();

  Serial.print("number:");
  Serial.println(WiFi.softAPgetStationNum());
  delay(60000);

  if(WiFi.status() != WL_CONNECTED && num_devices == 0){
    Serial.print("Attempting to connect to SSID: ");
    while(WiFi.status() != WL_CONNECTED){
      // Connect to WPA/WPA2 network.
      WiFi.begin(ssid, password);
      Serial.print(".");
      delay(5000);     
    } 
    Serial.print("ESP32 IP on the WiFi network: ");
    Serial.println(WiFi.localIP());
  }
}

// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>My First Web Server with ESP32 - AP Mode &#128522;</h1>\
</body>\
</html>";

// Handle root url (/)
void handle_root() {
  server.send(200, "text/html", HTML);
}

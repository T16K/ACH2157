# Arduino IDE

Nesta seção, eu vou mostrar as pesquisas que foram feitas para solucionar a parte da comunicação do *ESP32*, com o sensor [*GY-30*](../comp/sensor.md) e o site [*ThingSpeak*](https://thingspeak.com/).

## Preparando Arduino IDE

Então primerio eu instalei Arduino IDE, na versão mais recente pelo [site](https://www.arduino.cc/en/software).

Em seguida, é interessante adicionar a placa *ESP32* no Arduino IDE:
- No Arduino IDE, **File** > **Preferences**.
- Digitar o seguinte no campo “Additional Board Manager URLs”:
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
Depois clicar no botão de "OK".
- Abrir **Tools** > **Board:** > **Board Manager...**
- Procurar por **ESP32** e instalar o "ESP32 by Espressif Systems".

## Testando a Instalação

Agora eu conecto a placa *ESP32* no meu computador, e com o Arduino IDE:
- Selecionar a placa no menu **Tools** > **Board:** (no meu caso foi [**ESP32-WROOM-DA Module**](https://www.amazon.com.br/gp/product/B09491Q4F6/ref=ppx_yo_dt_b_asin_title_o08_s00?ie=UTF8&psc=1))
- Selecionar a porta **Tools** > **Port:** (no meu caso foi **/dev/ttyUSB0**)
- No caso eu escolhi usar o arquivo exemplo **File** > **Examples** > **WiFi (ESP32)** > **WiFiScan**.
- Fazer o *Upload* do arquivo:
![upload](../../../img/upload.png)
- Abrir o Arduino IDE *Serial Monitor* e colocar a taxa de transmissão em ```115200```:
![monitor](../../../img/monitor.png)

## Instalando a **Biblioteca BH1750**
Existem várias bibliotecas para o sensor *BH1750*. Eu escolhi usar a [biblioteca BH1750 por Christopher Laws](https://github.com/claws/BH1750).
- Abrir o Arduino IDE, **Sketch** > **Include Library** > **Manage Libraries**.
- Buscar "BH1750" na caixa de pesquisa e instalar a *biblioteca BH1750 por Christopher Laws*.
- Para testar eu usei o arquivo exemplo **File** > **Examples** > **BH1750** > **BH1750test**.
- Depois de dar *Upload* com sucesso, abra o *Serial Monitor* a uma taxa de transmissão em ```9600``` e pressione o botão **RST** no *ESP32*:
![luz](../../../img/luz.png)

## Instalando a **Biblioteca ThingSpeak**

Para enviar leituras de sensores para o *ThingSpeak*, usei a biblioteca *thingspeak-arduino*. Para instalar: Sketch > Include Library > Manage Libraries... e procure por "**ThingSpeak**" no *Library Manager*. Instalei a biblioteca *ThingSpeak* pelo *MathWorks*.
```
#include <WiFi.h>
#include "ThingSpeak.h"

#include <BH1750.h>
#include <Wire.h>

#include <Arduino.h>
#include <ML8511.h>

const char* ssid = "SSID";   // your network SSID (name) 
const char* password = "password";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 1;
const char * myWriteAPIKey = "APIKey";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 20000;

BH1750 lightMeter;

#define ANALOGPIN     A0

// Connect EN to 3V3 to explicitly 
// enable the sensor continuously
ML8511 light(ANALOGPIN);

void setup() {
  Serial.begin(115200);  //Initialize serial
  
  WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
    
  lightMeter.begin();
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

    float UV = light.getUV();
    Serial.print(UV, 4);
    Serial.println(" mW cm^2");

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
```

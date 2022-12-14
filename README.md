# Projeto Protetor Solar

## Descrição

O projeto busca avisar o usuário, o momento mais adequado para a reaplicação do protetor solar. Para isso, foi utilizado um sensor de coleta de dados do ambiente, um controlador para viabilizar o envio desses dados para o site em que serão processados, e por fim, um aplicativo para receber a resposta desse site, para atualizar o usuário. 

### Lista de Materiais

| Quantidade | Nome | Link para referência |
| :---: | :---: | :---: |
| 1 | Placa de desenvolvimento ESP-WROOM-32 e cabo USB | https://www.amazon.com.br/gp/product/B09491Q4F6/ref=ppx_yo_dt_b_asin_title_o08_s00?ie=UTF8&psc=1 |
| 1 | Sensor de Luz Ultravioleta UV ML8511 | https://www.institutodigital.com.br/produto/sensor-de-luz-ultravioleta-uv-ml8511/ |
| X | Jumpers variados | --- |
| {0,1} | protoboard | --- |
| {0,1} | fonte de alimentação - powerbank | --- |

### Conexões

| ESP32 | ML8511 |
| :---: | :---: |
| 3.3V | 3.3V |
| GND | GND |
| GPIO 34 | OUT |

## Explica como montar o dispositivo físico

Fazer as conexões listadas, configurar, transferir e executar [`main.ino`](/src/main.ino) no ESP32.

## Arquitetura e organização

Figura 1 - Esquema do projeto, arquivo-fonte da figura em /img/esquema.png:

![esquema](/img/esquema.png)

Primeiro os dados são coletados, utilizando o sensor (ML8511), e em seguida utilizando o controlador (ESP32), esses dados são interpretados e convertidos na escala [Índice Ultravioleta](https://pt.wikipedia.org/wiki/%C3%8Dndice_ultravioleta). Além disso, o controlador também é responsável por conectar-se à internet (e.g. ponto de acesso do celular) como um cliente wi-fi, e enviar as informações para o site [ThingSpeak](https://thingspeak.com/).

Com isso, o aplicativo servirá como uma interface para o usuário, tanto para enviar dados adicionas ao site, quanto para receber a resposta. No app, ao escolher as opções mais adequadas para o contexto do usuário, o site recebe essas informações e consegue prever o tempo estimado para a próxima reaplicação do protetor solar, e por fim, devolve esse valor para o aplicativo que vai atualizar o usuário.

## Explica como o sensor funciona

Para mais [informações](https://t16k-ach2157.readthedocs.io/en/latest/comp/sensor.html#introduzindo-o-ml8511-uv-sensor)

## Explica como processar os dados do sensor

Para mais [informações](https://t16k-ach2157.readthedocs.io/en/latest/software/ino.html#programas-ino)

## Explica como o programa foi feito

### Bibliotecas

Primeiro foram incluídas duas bibliotecas:
```C
#include <WiFi.h>
#include "ThingSpeak.h"
```
- A [primeira](https://github.com/arduino-libraries/WiFi), habilita a conexão de rede (local e Internet) usando o Arduino WiFi shield.
- A [segunda](https://github.com/mathworks/thingspeak-arduino) permite que o controlador escreva ou leia dados de ou para o ThingSpeak.

### Wifi

Para a conexão com o ponto de acesso,
```C
if(WiFi.status() != WL_CONNECTED) {
  Serial.print("Attempting to connect to SSID: ");
  while(WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password); // Connect to WPA/WPA2 network.
    Serial.print(".");
    delay(5000);     
  } 
  Serial.println("\nConnected.");
}
```

### ThingSpeak

Para o controlador comunicar com o site, enviando o valor do índice ultravioleta.
```C
ThingSpeak.setField(1, uvIntensity);
       
int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

if(x == 200) {
  Serial.println("Channel update successful.");
}
else {
  Serial.println("Problem updating channel. HTTP error code " + String(x));
}
```

### Pinos

Para a entrada do controlador foi [escolhido](https://t16k-ach2157.readthedocs.io/en/latest/comp/esp.html#notas) o `GPIO 34`:
```C
int UVOUT = 34;
```

O valor do pino irá passar por uma função para tirar a média das medidas:
```C
int averageAnalogRead(int pinToRead) {
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 

  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return(runningValue);  
}
```

Esse valor será utilizado para calcular o [valor da voltagem](https://t16k-ach2157.readthedocs.io/en/latest/comp/sensor.html#aumentar-a-precisao-do-ml8511) que o sensor emite.
```C
int uvLevel = averageAnalogRead(UVOUT);
float outputVoltage = 3.3 / 4095 * uvLevel;
```

### Converter a Voltagem para o Índice Ultravioleta

Então primeiro, foi utilizado o pino `GPIO 34` para encontrar a voltagem.
Depois, é necessário utilizar uma função de [mapeamento](http://forum.arduino.cc/index.php?topic=3922.0), para converter a voltagem em mW/cm².
```C
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
```

Com isso, utilizando a seguinte [informação](https://cdn.sparkfun.com/datasheets/Sensors/LightImaging/ML8511_3-8-13.pdf), é possível assumir que nehuma luz UV começa em 1V, e além disso possui um máximo de 15 mW/cm² em torno de 2.8V.
```C
float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0);
```

## Explica como o site foi utilizado

Para mais [informações](https://t16k-ach2157.readthedocs.io/en/latest/software/iot.html#iot-analytics)

## Explica como o aplicativo funciona

Para mais [informações](https://t16k-ach2157.readthedocs.io/en/latest/software/aplicativo.html#aplicativo)

## Referência

https://t16k-ach2157.rtfd.io

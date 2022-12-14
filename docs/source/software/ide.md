# Arduino IDE

Nesta seção, será mostrado as pesquisas que foram feitas para solucionar a parte da comunicação do *ESP32*, com o [sensor solar](../comp/sensor.md) e o [*ThingSpeak*](iot.md).

## Preparar Arduino IDE

Então primerio instalar o Arduino IDE, na versão mais recente pelo [site](https://www.arduino.cc/en/software).

Em seguida, é interessante adicionar a placa *ESP32* no Arduino IDE:
- No Arduino IDE, **File** > **Preferences**.
- Digitar o seguinte no campo “Additional Board Manager URLs”:
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
Depois clicar no botão de "OK".
- Abrir **Tools** > **Board:** > **Board Manager...**
- Procurar por **ESP32** e instalar o "ESP32 by Espressif Systems".

## Testar a Instalação

Agora conectar a placa *ESP32* no computador, e com o Arduino IDE:
- Selecionar a placa no menu **Tools** > **Board:** (no caso foi [**ESP32-WROOM-DA Module**](https://www.amazon.com.br/gp/product/B09491Q4F6/ref=ppx_yo_dt_b_asin_title_o08_s00?ie=UTF8&psc=1))
- Selecionar a porta **Tools** > **Port:** (no caso foi `/dev/ttyUSB0`)
- Foi escolhido usar o arquivo exemplo **File** > **Examples** > **WiFi (ESP32)** > **WiFiScan**.
- Fazer o *Upload* do arquivo:
![upload](../../../img/upload.png)
- Abrir o Arduino IDE *Serial Monitor* e colocar a taxa de transmissão em `115200`:
![monitor](../../../img/monitor.png)

## Utilizar a **Biblioteca BH1750**
Existem várias bibliotecas para o sensor *BH1750*. Foi escolhido usar a [biblioteca BH1750 por Christopher Laws](https://github.com/claws/BH1750).
- Abrir o Arduino IDE, **Sketch** > **Include Library** > **Manage Libraries**.
- Buscar "BH1750" na caixa de pesquisa e instalar a *biblioteca BH1750 por Christopher Laws*.
- Para testar foi utilizado o arquivo exemplo **File** > **Examples** > **BH1750** > **BH1750test**.
- Depois de dar *Upload* com sucesso, abrir o *Serial Monitor* a uma taxa de transmissão em `9600` e pressionar o botão **RST** no *ESP32*:
![luz](../../../img/luz.png)

## Utilizar a **Biblioteca ThingSpeak**

- Para enviar leituras de sensores para o *ThingSpeak*, usar a biblioteca *thingspeak-arduino*. 
- Para instalar: Sketch > Include Library > Manage Libraries... e procurar por "**ThingSpeak**" no *Library Manager*. 
- Instalar a biblioteca *ThingSpeak* pelo *MathWorks*.
- Para fins de teste foi escolhido o arquivo exemplo **File** > **Examples** > **ThingSpeak** > **ESP32** > **WriteSingleField**.
- No arquivo `secrets.h` substituir os valores de `"MySSID"`, `"MyPassword"`, `000000` e `"XYZ"`.
- Para mais [informações](https://t16k-ach2157.readthedocs.io/en/latest/software/iot.html).

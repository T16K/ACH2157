# Arduino IDE

Nesta seção, eu vou mostrar as pesquisas que foram feitas para solucionar a parte da comunicação do *ESP32*, com o sensor *GY-30* e o site [*ThingSpeak*](https://thingspeak.com/).

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

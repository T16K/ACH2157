# Programas

Para este projeto, usaremos um arquivo *boot.py* e um arquivo *socket.py*. O arquivo [*boot.py*](../comp/esp.md) tem o código que só precisa ser executado uma vez na inicialização, ele será responsável por

O arquivo *socket.py* conterá o código que executa o servidor web para servir arquivos e executar tarefas com base nas solicitações recebidas pelo cliente.

## *boot.py*

```python
try:
  import usocket as socket
except:
  import socket

from machine import Pin
import network

import esp
esp.osdebug(None)

import gc
gc.collect()

ssid = 'REPLACE_WITH_YOUR_SSID'
password = 'REPLACE_WITH_YOUR_PASSWORD'

station = network.WLAN(network.STA_IF)

station.active(True)
station.connect(ssid, password)

while station.isconnected() == False:
  pass

print('Connection successful')
print(station.ifconfig())

led = Pin(2, Pin.OUT)
```

- {ref}`boot:boot-py`


<br />

[site](https://randomnerdtutorials.com/esp32-esp8266-micropython-web-server/)

[site](https://randomnerdtutorials.com/esp32-bh1750-ambient-light-sensor/)
# Programas

Para este projeto, usaremos um arquivo *boot.py* e um arquivo *socket.py*. O arquivo *boot.py* tem o código que só precisa ser executado uma vez na inicialização, ele será responsável por conectar a placa ESP32 à rede de roteador e inicializar o *webrepl*.

O arquivo *socket.py* conterá o código que executa o servidor web para servir arquivos e executar tarefas com base nas solicitações recebidas pelo cliente.

## *boot.py*

```python
def do_connect(ssid, pwd):
    import network
    sta_if = network.WLAN(network.STA_IF)
    if not sta_if.isconnected():
        print('connecting to network...')
        sta_if.active(True)
        sta_if.connect(ssid, pwd)
        while not sta_if.isconnected():
            pass
    print('network config:', sta_if.ifconfig())
 
# This file is executed on every boot (including wake-boot from deepsleep)
#import esp
#esp.osdebug(None)
 
# Attempt to connect to WiFi network
do_connect('your_ssid', 'your_password')
 
import webrepl
webrepl.start()
```

## *socket.py*

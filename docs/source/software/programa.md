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

O script começa criando uma função chamada ```do_connect()```. Essa função possibilitará a conexão com a internet.

Nela é importante importar a biblioteca ```network```. Essa biblioteca
nos permite conectar o *ESP32* a uma rede Wi-Fi.

Em seguida, defina o *ESP32* como uma estação Wi-Fi:
```py
sta_if = network.WLAN(network.STA_IF)
```
e ative a estação:
```py
sta_if.active(True)
```

Finalmente, o *ESP32* se conecta ao seu roteador usando o SSID e senha que serão definidos mais adiante:
```py
sta_if.connect(ssid, pwd)
```

A instrução a seguir garante que o código não proceda enquanto o *ESP32* não estiver conectado à rede.
```py
while not sta_if.isconnected():
  pass
```

Após uma conexão bem-sucedida, imprima parâmetros de interface de rede como o endereço IP ESP32 – use o método ```ifconfig()``` no objeto da estação.
```py
print('network config:', sta_if.ifconfig())
```

Agora, usamos a função para definir as variáveis referentes as credenciais de rede:
```py
do_connect('your_ssid', 'your_password')
```
É preciso substituir as palavras destacadas, com o SSID da rede e senha, para que o *ESP32* seja capaz de se conectar ao roteador.

Por fim, iniciamos o *webrepl*:
```py
import webrepl
webrepl.start()
```

## *socket.py*

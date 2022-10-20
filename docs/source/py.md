# ESP32

*ESP32* é um sistema em um chip que integra os seguintes recursos:

- Wi-Fi (2.4 GHz band)
- Bluetooth
- Dual high performance Xtensa® 32-bit LX6 CPU cores
- Ultra Low Power co-processor
- Multiple peripherals

Alimentado por tecnologia de 40 nm, o *ESP32* fornece uma plataforma robusta e altamente integrada, que ajuda a atender às demandas contínuas de uso eficiente de energia, design compacto, segurança, alto desempenho e confiabilidade.

O *Espressif* fornece recursos básicos de hardware e software para ajudar os desenvolvedores de aplicativos a realizar suas ideias usando o hardware da série *ESP32*. A estrutura de desenvolvimento de software da *Espressif* destina-se ao desenvolvimento de aplicações de Internet das Coisas (IoT) com Wi-Fi, Bluetooth, gerenciamento de energia e vários outros recursos do sistema.

Para esse projeto usaremos o [*MicroPython*](https://docs.micropython.org/en/latest/esp32/quickref.html). Usar o *MicroPython* é uma ótima maneira de aproveitar ao máximo sua placa *ESP32*. E vice-versa, o chip *ESP32* é uma ótima plataforma para usar o *MicroPython*. Esta seção irá guiá-lo através da configuração do *MicroPython*, obtendo um prompt, usando WebREPL, conectando-se à rede e se comunicando com a Internet, usando os periféricos de hardware e controlando alguns componentes externos.

## Como configurar o *MicroPython* em sua placa de desenvolvimento *ESP32* para executar aplicativos *Python*

Informações gerais sobre a porta [*ESP32*](https://docs.micropython.org/en/latest/esp32/general.html)

### Baixando uma cópia do *MicroPython* para o seu *ESP32*

A primeira coisa que você precisa fazer é baixar o *firmware MicroPython* (arquivo .bin) para carregar em seu dispositivo *ESP32*. Você pode baixá-lo na [página de downloads do *MicroPython*](https://micropython.org/download/esp32/).

### Colocando o *MicroPython* no *ESP32*

Com isso, precisamos ter permissão para acessar a porta ``` \dev\ttyUSB0 ```,
```
sudo chmod 666 /dev/ttyUSB0 
```
mas se nós desconectarmos o dispositivo USB e reconectarmos ele, precisaremos refazer o comando.

<br />

Depois que o computador for capaz de se comunicar com sua placa de desenvolvimento *ESP32*, instale o [```esptool```](https://github.com/espressif/esptool) com,
```
pip install esptool
```

<br />

Então agora apagamos tudo do *flash* da sua placa *ESP32* com o seguinte comando:
```
esptool.py --chip esp32 --port /dev/ttyUSB0 erase_flash
```
A partir daí, programe o firmware a partir do endereço 0x1000:
```
esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 460800 write_flash -z 0x1000 'nome_do_arquivo'.bin
```
Quando o comando for concluído, você poderá executar códigos Python em sua placa ESP32 via MicroPython.

### Verificando sua configuração do *MicroPython* em sua placa de desenvolvimento *ESP32*

Então, como podemos saber se o *MicroPython* está corretamente instalado em nossa placa de desenvolvimento *ESP32*?

Quando o *MicroPython* estiver corretamente instalado, poderemos acessar o ```REPL``` em série com um programa de emulador de terminal.

Por exemplo, você pode usar o comando de tela se estiver o ```rshell``` instalado:
```
rshell -p /dev/tty.ttyUSB0 -b 115200 --editor nvim 
repl
```
Se você quiser ver o *MicroPython*, então você pode pressionar ```Ctrl-D``` para iniciar uma reinicialização suave. Neste momento, você pode tentar executar alguns códigos *Python* no ```REPL```.

## Como configurar o *MicroPython* [*WebREPL*](https://docs.micropython.org/en/latest/esp8266/tutorial/repl.html#webrepl-a-prompt-over-wifi) em sua placa de desenvolvimento *ESP32*

Agora, você poderá habilitar o *WebREPL* em sua placa *ESP32*. Para isso, digite o seguinte código no prompt ```REPL```:
```
import webrepl_setup
```
Depois de fazê-lo, siga as instruções para ativar o *WebREPL* em sua placa *ESP32*.

### Conectando sua placa ESP32 à sua rede de roteador

Primeiro, use ```rshell``` para se conectar à sua placa *ESP32* via conexão serial:
```
rshell -p /dev/tty.SLAB_USBtoUART -b 115200 --editor nvim
```
Quando você fizer isso, você poderá editar arquivos no quadro *ESP32* com o editor ```neovim```.
Uma vez que o ```rshell``` é iniciado, execute o seguinte comando para editar ```boot.py``` na placa *ESP32*:
```
edit /pyboard/boot.py
```
Quando o seu editor ```neovim``` carregar ```boot.py```, edite-o para parecer com o seguinte:
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
Altere **your_ssid** e **your_password** para as credenciais (SSID, senha WiFi) da sua rede WiFi de 2.4GHz. Quando terminar as alterações, digite ```:x``` e pressione ```Enter``` para salvar as alterações.
Depois de editar ```boot.py```, entre no *MicroPython REPL*:
```
repl
```
Uma vez que o *Python REPL* seja carregado, pressione o ```Ctrl-D``` para reiniciar a placa *ESP32*. Quando o seu quadro de desenvolvimento *ESP32* for reiniciado, você deve encontrar alguma saída semelhante à seguinte:
```
MPY: soft reboot
network config: ('192.168.1.131', '255.255.255.0', '192.168.1.1', '192.168.1.1')
WebREPL daemon started on ws://192.168.1.131:8266
Started webrepl in normal mode
MicroPython v1.12-68-g3032ae115 on 2020-01-15; ESP32 module with ESP32
Type "help()" for more information.
```
Neste caso, usaremos ```ws://192.168.1.131:8266``` para conectar à placa de desenvolvimento *ESP32*. Se sua placa de desenvolvimento *ESP32* estiver conectada à sua rede WiFi com sucesso, então você deve obter a URL para se conectar à sua placa.

### Usando o cliente *MicroPython WebREPL* para interagir com sua placa de desenvolvimento *ESP32*

Nessa parte, precisamos baixar o [WebREPL](https://github.com/micropython/webrepl), eu recomendo utilizar o SSH:
```
git clone git@github.com:micropython/webrepl.git
```
Depois de baixar, abrir o arquivo ```webrepl.html``` com o navegador.

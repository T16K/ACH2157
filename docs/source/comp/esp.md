# *ESP32*

[*ESP32*](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/) é um sistema em um chip que integra os seguintes recursos:

- Wi-Fi (2.4 GHz band)
- Bluetooth
- Dual high performance Xtensa® 32-bit LX6 CPU cores
- Ultra Low Power co-processor
- Multiple peripherals

Alimentado por tecnologia de 40 nm, o *ESP32* fornece uma plataforma robusta e altamente integrada, que ajuda a atender às demandas contínuas de uso eficiente de energia, *design* compacto, segurança, alto desempenho e confiabilidade.

O *Espressif* fornece recursos básicos de *hardware* e *software* para ajudar os desenvolvedores de aplicativos a realizar as ideias usando o *hardware* da série *ESP32*. A estrutura de desenvolvimento de *software* da *Espressif* destina-se ao desenvolvimento de aplicações de Internet das Coisas (IoT) com *Wi-Fi*, *Bluetooth*, gerenciamento de energia e vários outros recursos do sistema.

Para esse projeto foi utilizado o [*MicroPython*](https://docs.micropython.org/en/latest/esp32/quickref.html). Usar o *MicroPython* é uma ótima maneira de aproveitar ao máximo a placa *ESP32*. E vice-versa, o chip *ESP32* é uma ótima plataforma para usar o *MicroPython*. Esta seção guiará através da configuração do *MicroPython*, obtendo um prompt, usando WebREPL, conectando-se à rede e se comunicando com a Internet.





## Como configurar o *MicroPython* na placa de desenvolvimento *ESP32* para executar aplicativos *Python*

Informações gerais sobre a [porta *ESP32*](https://docs.micropython.org/en/latest/esp32/general.html).





### Baixar uma cópia do *MicroPython* no *ESP32*

Primeiro é preciso baixar o *firmware MicroPython* (arquivo .bin) para carregar no dispositivo *ESP32*. Ele está disponível na [página de downloads do *MicroPython*](https://micropython.org/download/esp32/).





### Colocar o *MicroPython* no *ESP32*

Com isso, é necessário ter permissão para acessar a porta `\dev\ttyUSB0`,
```
sudo chmod 666 /dev/ttyUSB0 
```
mas ao desconectar o dispositivo USB e reconectar ele, será necessário refazer o comando.

<br />

Depois que o computador for capaz de se comunicar com sua placa de desenvolvimento *ESP32*, instalar o [`esptool`](https://github.com/espressif/esptool) com,
```
pip install esptool
```

<br />

Então agora apagar tudo do *flash* da placa *ESP32* com o seguinte comando:
```
esptool.py --chip esp32 --port /dev/ttyUSB0 erase_flash
```
A partir daí, programar o *firmware* usando o endereço 0x1000:
```
esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 460800 write_flash -z 0x1000 'nome_do_arquivo'.bin
```
Quando o comando for concluído, será possível executar códigos Python na placa *ESP32* via *MicroPython*.





### Verificar a configuração do *MicroPython* na placa de desenvolvimento *ESP32*

- Então, como saber se o *MicroPython* está corretamente instalado na placa de desenvolvimento *ESP32*?

- Quando o *MicroPython* estiver corretamente instalado, será possível acessar o `REPL` em série com um programa de emulador de terminal.

Por exemplo, usar o comando de tela se com o `rshell` instalado:
```
rshell -p /dev/tty.ttyUSB0 -b 115200 --editor nvim 
repl
```
Para ver o *MicroPython*, pressionar `Ctrl-D` para iniciar uma reinicialização suave. Neste momento, tentar executar alguns códigos *Python* no `REPL`.





## Como configurar o *MicroPython* [*WebREPL*](https://docs.micropython.org/en/latest/esp8266/tutorial/repl.html#webrepl-a-prompt-over-wifi) na placa de desenvolvimento *ESP32*

Agora, será possível habilitar o *WebREPL* na placa *ESP32*. Para isso, digitar o seguinte código no prompt `REPL`:
```
import webrepl_setup
```
Depois de executar, seguir as instruções para ativar o *WebREPL* na placa *ESP32*.





### Conectar sua placa ESP32 à sua rede de roteador

Primeiro, usar `rshell` para se conectar à sua placa *ESP32* via conexão serial:
```
rshell -p /dev/tty.SLAB_USBtoUART -b 115200 --editor nvim
```
Quando fizer isso, será possível editar arquivos no quadro *ESP32* com o editor `neovim`.
Uma vez que o `rshell` é iniciado, execute o seguinte comando para editar `boot.py` na placa *ESP32*:
```
edit /pyboard/boot.py
```
Quando o seu editor `neovim` carregar `boot.py`, edite-o para parecer com o [seguinte](../software/programa.md).

Altere `your_ssid` e `your_password` para as credenciais `(SSID, senha WiFi)` da rede WiFi de 2.4GHz. Quando terminar as alterações, digitar `:x` e pressionar `Enter` para salvar as alterações.
Depois de editar o `boot.py`, entrar no *MicroPython REPL*:
```
repl
```
Uma vez que o *Python REPL* seja carregado, pressionar o `Ctrl-D` para reiniciar a placa *ESP32*. Quando o quadro de desenvolvimento *ESP32* for reiniciado, será encontrado alguma saída semelhante à seguinte:
```
MPY: soft reboot
network config: ('192.168.1.131', '255.255.255.0', '192.168.1.1', '192.168.1.1')
WebREPL daemon started on ws://192.168.1.131:8266
Started webrepl in normal mode
MicroPython v1.12-68-g3032ae115 on 2020-01-15; ESP32 module with ESP32
Type "help()" for more information.
```
Neste caso, usar ```ws://192.168.1.131:8266``` para conectar à placa de desenvolvimento *ESP32*. Se a placa de desenvolvimento *ESP32* estiver conectada à sua rede WiFi com sucesso, então será possível obter a URL para se conectar à sua placa.





### Usar o cliente *MicroPython WebREPL* para interagir com sua placa de desenvolvimento *ESP32*

Nessa parte, será preciso baixar o [WebREPL](https://github.com/micropython/webrepl), para isso utilizar o SSH:
```
git clone git@github.com:micropython/webrepl.git
```
Depois de baixar, abrir o arquivo ```webrepl.html``` com o navegador.

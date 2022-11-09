# Sensor Solar

Para o projeto utilizaremos o **BH1750 – Ambient Light Sensor**.

[Sensor de intensidade luminosa GY-30 (BH1750FVI)](https://randomnerdtutorials.com/esp32-bh1750-ambient-light-sensor/)

## Introduzindo o *BH1750 Ambient Light Sensor*

O *BH1750* é um sensor de luz ambiente de 16 *bits* que se comunica através do [**protocolo I2C**](https://github.com/FNakano/CFA/tree/master/projetos/I2C). Produz medições de luminosidade em *lux* (unidade derivada de SI de iluminação). Pode medir um mínimo de 1 *lux* e um máximo de 65535 *lux*.

## Características do *BH1750*

Aqui está uma lista dos recursos do sensor BH1750. Para mais informações consulte o [**BH1750 sensor datasheet**](https://datasheet.octopart.com/BH1750FVI-TR-Rohm-datasheet-25365051.pdf).
- Interface I2C 
- Faixa: 1 – 65535 lux 
- Baixa corrente por função de desligamento de energia 
- Função de rejeição de ruído leve de 50Hz / 60Hz 
- Pequena variação de medição (+/- 20%) 
- Pouca influência do infravermelho 
- Suporta modo de medição contínua 
- Suporta o modo de medição único

## Modos de Medição

O sensor suporta dois modos de medição diferentes: *continuous measurement mode* e *one-time measurement mode*. Cada modo suporta três modos de resolução diferentes.

| Modo Resolução | Precisão | Tempo de Medição |
| :---: | :---: | :---: |
| Modo de Baixa Resolução | 4 lux | 16 ms |
| Modo de Alta Resolução | 1 lux | 120 ms |
| Modo de Alta Resolução 2 | 0.5 lux | 120 ms |

No *continuous measurement mode*, o sensor mede continuamente os valores da luz ambiente. No *one-time measurement mode*, o sensor mede o valor da luz ambiente uma vez, e então ele vai para o modo de desligamento.

[GYML8511 UV Sensor](http://wiki.sunfounder.cc/index.php?title=GYML8511_UV_Sensor)

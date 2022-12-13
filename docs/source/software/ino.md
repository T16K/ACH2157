# Programas .ino

Nesta seção, será explicado o código que foi utilizado para testar a leitura do sensor ML8511, e converter a intensidade da voltagem para a intensidade em mW/cm².

[main.ino](../../prog/ino/main.ino)

Primeiro, é interessante mapear o [`UV_Voltage`](https://t16k-ach2157.readthedocs.io/en/latest/comp/esp.html#notas). Nenhuma luz UV começa em 1V e possui um máximo de 15mW/cm² em torno de 2.8V. O Arduino tem uma função map() embutida, mas map() não funciona para floats, mas graças aos usuários no fórum Arduino, existe uma simples função mapFloat():
```C
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
```

<br />

A próxima linha é responsável por converte a tensão lida do sensor em intensidade mW/cm²:
```C
float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0);
```

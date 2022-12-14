# Programas .ino

Nesta seção, será explicado o código que foi utilizado para testar a leitura do sensor ML8511, e converter a intensidade da voltagem para a intensidade em mW/cm².

## [main.ino](../../prog/ino/main.ino)

```C
//Hardware pin definitions
int UVOUT = 34; //Output from the sensor
int REF_3V3 = 35; //3.3V power on the Arduino board

//The Arduino Map function but for floats
//From: http://forum.arduino.cc/index.php?topic=3922.0
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//Takes an average of readings on a given pin
//Returns the average
int averageAnalogRead(int pinToRead) {
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 

  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return(runningValue);  
}

void setup() {
  Serial.begin(9600);

  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);

  Serial.println("ML8511 example");
}

void loop() {
  int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);

  //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
  float outputVoltage = 3.3 / refLevel * uvLevel;

  //Convert the voltage to a UV intensity level
  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); 

  Serial.print("output: ");
  Serial.print(refLevel);

  Serial.print("ML8511 output: ");
  Serial.print(uvLevel);

  Serial.print(" / ML8511 voltage: ");
  Serial.print(outputVoltage);

  Serial.print(" / UV Intensity (mW/cm^2): ");
  Serial.print(uvIntensity);

  Serial.println();

  delay(100);
}
```

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

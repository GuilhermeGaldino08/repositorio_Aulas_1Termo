#include <Arduino.h>

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int valor = 10;

  switch (valor)
  {
  case 1:
    Serial.println("Um");
    break;

  case 2:
    Serial.println("Dois");
    break;

  case 3:
    Serial.println("Três");
    break;

  case 4:
    Serial.println("Quatro");
    break;

  default:
    Serial.println("Nome não reconhecido");
    break;
  }
}
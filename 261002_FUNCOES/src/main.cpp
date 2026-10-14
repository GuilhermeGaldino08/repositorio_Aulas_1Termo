#include <Arduino.h>
#include "func.h"

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  for (int i = 0; i < 10; i++)
  {
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(obterNomeCor(i));
  }
  Serial.print("Media entre 27.2 e 43.8 é: ");
  Serial.println(calcularMedia(27.2, 43.9));

  if (verificarTemperatura(30, 35))
    Serial.print("Temperatura OK");

  while (botaoPressionado(0))
  {
    Serial.println("Botao pressionado");
  }
}

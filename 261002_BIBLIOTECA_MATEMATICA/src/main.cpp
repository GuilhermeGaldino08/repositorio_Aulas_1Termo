#include <Arduino.h>
#include "matRobo.h"

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("=====RESULTADOS DAS FUNÇÕES=====");

  //*Calcular Dobro
  Serial.print("Qual o dobro de 3.5? ");
  Serial.println(calcularDobro(3.5));

  //*Eh Par
  Serial.print("O numero 7 é par? ");
  if (ehPar(7)) Serial.println("Sim, é par");
  else Serial.println("Não, é impar");

  //*Calculadora Magica
  Serial.print("Qual o resultado de 55 x 3? ");
  Serial.println(calculadoraMagica(55, 3, 3));

  //*Calcular Fatorial
  Serial.print("Qual o fatorial de 5? ");
  Serial.println(numeroFatorial(5));

  Serial.println("================================");
}

void loop()
{}
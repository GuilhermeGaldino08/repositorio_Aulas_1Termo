/*============================
Projeto: Sequencia Fibonacci
Descrição: Exercicío Fibonacci com FOR
Autor: Guilherme Oliveira Galdino
Data: 17/09/2026
Versão: 0.2
============================*/
#include <Arduino.h>

void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.println("0 - 0");
  Serial.println("1 - 1");
  
  unsigned int A = 0;
  unsigned int B = 1;
  unsigned int C = 0;

  for (int contador = 2; contador < 20; contador++)
  {
    C = A + B;
    A = B;
    B = C;
    Serial.print(contador);
    Serial.print(" - ");
    Serial.println(C);
  }

}
void loop()
{}
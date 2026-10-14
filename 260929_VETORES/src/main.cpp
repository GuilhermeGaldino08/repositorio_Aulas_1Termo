#include <Arduino.h>

int vetor [10] = {12, 3, 14, 56, 31, 3, 89, 0, 62, 10};

void setup()
{
  Serial.begin(9600);
  Serial.println(vetor[0]);
  Serial.println(vetor[1]);
  Serial.println(vetor[2]);
  Serial.println(vetor[3]);
  Serial.println(vetor[4]);
  Serial.println(vetor[5]);
  Serial.println(vetor[6]);
  Serial.println(vetor[7]);
  Serial.println(vetor[8]);
  Serial.println(vetor[9]);
}

void loop()
{}
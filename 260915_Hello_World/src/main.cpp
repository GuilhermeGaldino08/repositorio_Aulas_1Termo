#include <Arduino.h>

const int pinLedVermelho = 2;
const int pinLedAmarelo =  38;
const int pinLedVerde = 45;
const int umSegundo = 1000;

void setup()
{
  Serial.begin(9600);
  pinMode(pinLedVermelho, OUTPUT);
  pinMode(pinLedAmarelo, OUTPUT);
  pinMode(pinLedVerde, OUTPUT);
}

void loop()
{
  unsigned long tempoAgora = millis();
  static unsigned long tempoInicial = 0;
  static bool estadoLedVermelho = 0;
  static bool estadoLedAmarelo = 0;
  static bool estadoLedVerde = 0;
  static int contador = 0;
  
  if (tempoAgora >= tempoInicial + umSegundo)
  {
    contador = contador + 1;
    if (contador > 9) contador = 0;
    Serial.println(contador);
   	tempoInicial = tempoAgora;
  }
  
  if(contador < 3)
  {
    estadoLedVermelho = LOW;
    estadoLedVerde = HIGH;
  }
  
  else if(contador < 5)
  {
    estadoLedVerde = LOW;
    estadoLedAmarelo = HIGH;
  }
  else
  {
    estadoLedAmarelo = LOW;
    estadoLedVermelho = HIGH;
  }
  
  digitalWrite(pinLedVermelho, estadoLedVermelho);
  digitalWrite(pinLedVerde, estadoLedVerde);
  digitalWrite(pinLedAmarelo, estadoLedAmarelo);
}
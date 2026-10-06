#include <Arduino.h>
#include "led.h"

Led ledAmarelo(4);

void setup()
{
  ledAmarelo.iniciar();
  ledAmarelo.ativarPiscar(100);
}

void loop()
{
  ledAmarelo.atualizar();
}
#include "led.h"

Led::Led(uint8_t pino)
{
    _pino = pino;
}

void Led::iniciar()
{
    pinMode(_pino, OUTPUT);
    digitalWrite(_pino, LOW);
}

void Led::ligar()
{
    digitalWrite(_pino, HIGH);
}

void Led::desligar()
{
    digitalWrite(_pino, LOW);
}

void Led::piscar(uint32_t intervalo)
{
    _intervalo = intervalo;
}

void Led::ativarPiscar()
{
    _piscando = true;
}

void Led::desativarPiscar()
{
    _piscando = false;
}

void Led::atualizar()
{
    if (!_piscando) return;
    if (millis() - _tempoAnterior >= _intervalo)
    {
        _tempoAnterior = millis();
        _estado = !_estado;

        digitalWrite(_pino, _estado);
    }
}
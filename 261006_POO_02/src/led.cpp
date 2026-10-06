//! src/led.cpp
#include "led.h"

Led::Led(uint8_t pino)
{
    _pinoLed = pino;
}

void Led::iniciar()
{
    pinMode(_pinoLed, OUTPUT);
    digitalWrite(_pinoLed, LOW);
}

void Led::atualizar()
{
    if (_estaPiscando)
    {
        const uint32_t tempoDecorrido = millis() - _tempoAnteriorAcionamento_ms;
        if (tempoDecorrido >= _intervaloPiscar_ms)
        {
            _tempoAnteriorAcionamento_ms = millis();
            alternar();
        }
    }
    digitalWrite(_pinoLed, _estadoLed);
}

void Led::ligar()
{
    _estadoLed = HIGH;
}

void Led::desligar()
{
    _estadoLed = LOW;
}

void Led::ativarPiscar(uint32_t tempoIntervalo_ms)
{
    _estaPiscando = HIGH;
    _intervaloPiscar_ms = tempoIntervalo_ms;
}

void Led::desativarPiscar()
{
    _estaPiscando = LOW;
    _estadoLed = LOW;
}

void Led::alternar()
{
    _estadoLed = !_estadoLed;
}

uint8_t Led::getPinoLed()
{
    return _pinoLed;
}

void Led::setEstadoLed(bool estadoLed)
{
    _estadoLed = estadoLed;
}

bool Led::getEstadoLed()
{
    return _estadoLed;
}
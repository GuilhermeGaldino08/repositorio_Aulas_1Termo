//! include/led.h
#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led
{
private:
    uint8_t _pinoLed;
    bool _estadoLed = 0;
    bool _estaPiscando = 0;
    uint32_t _tempoAnteriorAcionamento_ms = 0;
    uint32_t _intervaloPiscar_ms = 1000;

public:
    Led(uint8_t pino);

    void iniciar();
    void atualizar();
    void ligar();
    void desligar();
    void ativarPiscar(uint32_t tempoIntervalo_ms);
    void desativarPiscar();
    void alternar();
    uint8_t getPinoLed();
    void setEstadoLed(bool estadoLed);
    bool getEstadoLed();
};
#endif
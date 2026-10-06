#include <Arduino.h>

#ifndef LED_H
#define LED_H

class Led
{
public:
    uint8_t _pino;

    uint32_t _tempoAnterior = 0;
    uint32_t _intervalo = 500;
    
    bool _estado = false;
    bool _piscando = false;
    
    Led(uint8_t pino);

    void iniciar();
    void ligar();
    void desligar();
    void piscar(uint32_t intervalo);
    void ativarPiscar();
    void desativarPiscar();
    void atualizar();

};

#endif
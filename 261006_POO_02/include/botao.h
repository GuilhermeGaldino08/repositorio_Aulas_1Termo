#ifndef BOTAO_H
#define BOTAO_H

#include <Arduino.h>

class Botao
{
private:
    uint8_t _pinoBotao;
    bool _estadoAtualBotao = HIGH;
    bool _estadoAnteriorBotao = HIGH;

public:
    Botao(uint8_t pino);

    void iniciar();
    void atualizar();
    bool pressionou();
    bool soltou();
};

#endif
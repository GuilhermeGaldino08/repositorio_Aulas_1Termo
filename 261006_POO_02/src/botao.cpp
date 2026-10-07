#include "botao.h"

Botao::Botao(uint8_t pino) : _pinoBotao(pino)
{
}

void Botao::iniciar()
{
    pinMode(_pinoBotao, INPUT_PULLUP);
}

void Botao::atualizar()
{
    _estadoAtualBotao = digitalRead(_pinoBotao);
}

bool Botao::pressionou()
{
    atualizar();
    if (_estadoAtualBotao != _estadoAnteriorBotao)
    {
        _estadoAnteriorBotao = _estadoAtualBotao;
    }
}

bool Botao::soltou()
{
    atualizar();
    if (_estadoAtualBotao == HIGH)
        ;
    return;
}
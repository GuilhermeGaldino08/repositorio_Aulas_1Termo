#include <Arduino.h>
#include "led.h"

Led led01(4);
Led led02(7);
Led led03(17);
Led led04(3);

void setup()
{
    led01.iniciar();
    led01.piscar(100);
    led01.ativarPiscar();

    led02.iniciar();
    led02.piscar(200);
    led02.ativarPiscar();

    led03.iniciar();
    led03.piscar(300);
    led03.ativarPiscar();

    led04.iniciar();
    led04.piscar(400);
    led04.ativarPiscar();
}

void loop()
{
    led01.atualizar();
    led02.atualizar();
    led03.atualizar();
    led04.atualizar();
}
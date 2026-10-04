/*=====
Projeto: Seletor Numerico Binario
Descrição: Seleciona um valor no LCD e acende os leds com o valor correspondente em binário
Autor: Guilherme Oliveira Galdino
Data: 01/10/2026
Versão: 0.1
=====*/
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Botao.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
Botao btnCima(12);
Botao btnBaixo(13);
Botao btnEnter(14);

const int pinLeds[4] = {18, 16, 7, 4};
int contador = 0;
int acenderLeds[4];

//=====PROTOTIPOS DAS FUNÇÕES=====
void telaInicial();
void atualizarDisplay();

void setup()
{
    lcd.init();
    lcd.backlight();

    btnCima.iniciar();
    btnBaixo.iniciar();
    btnEnter.iniciar();

    for (int i = 0; i < 4; i++)
        pinMode(pinLeds[i], OUTPUT);

    telaInicial();
    atualizarDisplay();
}

void loop()
{
    btnCima.atualizar();
    btnBaixo.atualizar();
    btnEnter.atualizar();

    //=====BOTÕES=====
    if (btnCima.pressionou())
    {
        if (contador < 15)
        {
            contador++;
            atualizarDisplay();
        }
    }

    if (btnBaixo.pressionou())
    {
        if (contador > 0)
        {
            contador--;
            atualizarDisplay();
        }
    }

    //=====CONVERSOR PARA BINARIO=====
    if (btnEnter.pressionou())
    {
        int numeroBinario = contador;

        for (int i = 0; i < 4; i++)
        {
            acenderLeds[i] = numeroBinario % 2;
            numeroBinario = numeroBinario / 2;
        }

        for (int i = 0; i < 4; i++)
        {
            digitalWrite(pinLeds[i], acenderLeds[i]);
        }
        atualizarDisplay();
    }
}

void telaInicial()
{
    lcd.setCursor(0, 0);
    lcd.print("SELECIONE O VALOR:");
    lcd.setCursor(0, 1);
    lcd.print("VALOR: ");
    lcd.setCursor(0, 2);
    lcd.print("BINARIO: ");
    lcd.setCursor(0, 3);
    lcd.print("ENTER = CONFIRMAR");
}

void atualizarDisplay()
{
    lcd.setCursor(8, 1);
    lcd.print("     ");
    lcd.setCursor(8, 1);
    lcd.print(contador);
    lcd.setCursor(10, 2);

    for (int i = 3; i >= 0; i++)
    {
        lcd.print(acenderLeds[i]);
    }
}
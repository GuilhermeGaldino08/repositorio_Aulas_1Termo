#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Botao.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
Botao btnCima(12);
Botao btnBaixo(13);
Botao btnEnter(14);

const int pinLeds[4] = {4, 6, 17, 10};
bool estadosLeds[4] = {0, 0, 0, 0};
bool alteracaoDisplay = 0;
int contador = 0;

//=====PROTOTIPOS DE FUNÇÕES=====
void telaInicial();
void atualizarDisplay();

void setup()
{
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);

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
}

void telaInicial()
{
    lcd.setCursor(0, 0);
    lcd.print("SELECIONE O VALOR:");
    lcd.setCursor(0, 1);
    lcd.print("VALOR: ");
}

void atualizarDisplay()
{
    lcd.setCursor(8 ,1);
    lcd.print(contador);
}
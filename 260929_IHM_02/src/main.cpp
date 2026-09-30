/*========================
Projeto: IHM_02
Descrição: Fazer funcionar um LCD com seletor de Led
Autor: Guilherme Oliveira Galdino
Data: 30/09/2026
Versão: 0.1
========================*/
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Botao.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
Botao btnCima(12);
Botao btnBaixo(13);
Botao btnEnter(14);

const int pinLeds[4] = {4, 6, 17, 10};

//=====PROTOTIPO DAS FUNÇÕES=====
void telaInicial();

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  btnCima.iniciar();
  btnBaixo.iniciar();
  btnEnter.iniciar();

  for (int i = 0; i < 4; i++)
    pinMode(pinLeds[i], OUTPUT);

    telaInicial();
}

void loop()
{
  btnCima.atualizar();
  btnBaixo.atualizar();
  btnEnter.atualizar();

  static int posicaoSeletor = 0;
  static int posicaoSeletorAnterior = 0;
  static bool estadosLeds[4] = {0, 0, 0, 0};
  bool alteracaoDisplay = 0;

  if (btnCima.pressionou())
  {
    if (posicaoSeletor < 3)
      posicaoSeletor++;
  }

  if (btnBaixo.pressionou())
  {
    if (posicaoSeletor > 0)
      posicaoSeletor--;
  }

  if (btnEnter.pressionou())
  {
    estadosLeds[posicaoSeletor] = !estadosLeds[posicaoSeletor];
    alteracaoDisplay = 1;
  }

  //=====LEDS=====
  for (int i = 0; i < 4; i++)
    digitalWrite(pinLeds[i], estadosLeds[i]);

  //=====DISPLAY=====
  if (posicaoSeletor != posicaoSeletorAnterior)
  {
    lcd.setCursor(0, posicaoSeletor);
    lcd.print(">");
    lcd.setCursor(0, posicaoSeletorAnterior);
    lcd.print(" ");
    posicaoSeletorAnterior = posicaoSeletor;
  }

  if (alteracaoDisplay)
  {
    lcd.setCursor(8, posicaoSeletor);
    lcd.print(estadosLeds[posicaoSeletor] ? "LIGADO   " : "DESLIGADO");
    //*(estadosLeds[posicaoSeletor]) ? lcd.print("LIGADO   ") : lcd.print("DESLIGADO");
  }
}

void telaInicial()
{
  lcd.setCursor(0, 0);
  lcd.print("> LED A DESLIGADO");
  lcd.setCursor(0, 1);
  lcd.print("  LED B DESLIGADO");
  lcd.setCursor(0, 2);
  lcd.print("  LED C DESLIGADO");
  lcd.setCursor(0, 3);
  lcd.print("  LED D DESLIGADO");
}

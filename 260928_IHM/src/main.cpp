#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int pinLedVermelho = 4;
const int pinLedVerde = 6;
const int pinLedAmarelo = 17;
const int pinLedAzul = 10;

const int pinBotao1 = 12;
const int pinBotao2 = 13;
const int pinBotao3 = 14;

static int estadoLedVermelho = 0;
static int estadoLedVerde = 0;
static int estadoLedAmarelo = 0;
static int estadoLedAzul = 0;

static int estadoBotao1 = 0;
static int estadoBotao2 = 0;
static int estadoBotao3 = 0;

static int estadoAntigoBotao1 = 0;
static int estadoAntigoBotao2 = 0;
static int estadoAntigoBotao3 = 0;

static int contador = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(pinLedVermelho, OUTPUT);
  pinMode(pinLedVerde, OUTPUT);
  pinMode(pinLedAmarelo, OUTPUT);
  pinMode(pinLedAzul, OUTPUT);

  pinMode(pinBotao1, INPUT_PULLUP);
  pinMode(pinBotao2, INPUT_PULLUP);
  pinMode(pinBotao3, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Led 1");
  lcd.setCursor(0, 1);
  lcd.print("Led 2");
  lcd.setCursor(0, 2);
  lcd.print("Led 3");
  lcd.setCursor(0, 3);
  lcd.print("Led 4");
}

void loop()
{

  static bool displayLigado = false;

  estadoBotao1 = digitalRead(pinBotao1);
  estadoBotao2 = digitalRead(pinBotao2);
  estadoBotao3 = digitalRead(pinBotao3);

  if (estadoBotao2 == 0 && estadoAntigoBotao2 == 1)
  {
    contador = contador + 1;
    if (contador > 4)
    {
      contador = 1;
    }

    lcd.setCursor(5, 0);
    lcd.print(" ");
    lcd.setCursor(5, 1);
    lcd.print(" ");
    lcd.setCursor(5, 2);
    lcd.print(" ");
    lcd.setCursor(5, 3);
    lcd.print(" ");

    if (contador == 1)
    {
      lcd.setCursor(5, 0);
      lcd.print("<");
    }
    if (contador == 2)
    {
      lcd.setCursor(5, 1);
      lcd.print("<");
    }
    if (contador == 3)
    {
      lcd.setCursor(5, 2);
      lcd.print("<");
    }
    if (contador == 4)
    {
      lcd.setCursor(5, 3);
      lcd.print("<");
    }
  }
  if (estadoBotao1 == 0 && estadoAntigoBotao1 == 1)
  {
    contador = contador - 1;
    if (contador < 1)
    {
      contador = 4;
    }

    lcd.setCursor(5, 0);
    lcd.print(" ");
    lcd.setCursor(5, 1);
    lcd.print(" ");
    lcd.setCursor(5, 2);
    lcd.print(" ");
    lcd.setCursor(5, 3);
    lcd.print(" ");

    if (contador == 1)
    {
      lcd.setCursor(5, 0);
      lcd.print("<");
    }
    if (contador == 2)
    {
      lcd.setCursor(5, 1);
      lcd.print("<");
    }
    if (contador == 3)
    {
      lcd.setCursor(5, 2);
      lcd.print("<");
    }
    if (contador == 4)
    {
      lcd.setCursor(5, 3);
      lcd.print("<");
    }
  }

  if (estadoBotao3 == 0 && estadoAntigoBotao3 == 1)
  {
    if (contador == 1)
    {
      if (estadoLedVermelho == 0)
      {
        estadoLedVermelho = 1;
      }
      else
      {
        estadoLedVermelho = 0;
      }
    }
    if (contador == 2)
    {
      if (estadoLedVerde == 0)
      {
        estadoLedVerde = 1;
      }
      else
      {
        estadoLedVerde = 0;
      }
    }
    if (contador == 3)
    {
      if (estadoLedAmarelo == 0)
      {
        estadoLedAmarelo = 1;
      }
      else
      {
        estadoLedAmarelo = 0;
      }
    }
    if (contador == 4)
    {
      if (estadoLedAzul == 0)
      {
        estadoLedAzul = 1;
      }
      else
      {
        estadoLedAzul = 0;
      }
    }
  }
  digitalWrite(pinLedVermelho, estadoLedVermelho);
  digitalWrite(pinLedVerde, estadoLedVerde);
  digitalWrite(pinLedAmarelo, estadoLedAmarelo);
  digitalWrite(pinLedAzul, estadoLedAzul);

  estadoAntigoBotao1 = estadoBotao1;
  estadoAntigoBotao2 = estadoBotao2;
  estadoAntigoBotao3 = estadoBotao3;
}
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>

String pedirParaApiClima(String codigo);
void telaLCD();

LiquidCrystal_I2C lcd(0x27, 20, 4);

const char *nomeRedeWiFi = "SENAI EDUCACIONAL";
const char *senhaRedeWiFi = "info@134";
const char *enderecoApiClima = "https://wttr.in/Sao+Caetano+do+Sul?m&lang=pt&format=";

String clima;
int temperatura;
int sensacaoTermica;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(nomeRedeWiFi, senhaRedeWiFi);
  lcd.init();
  lcd.backlight();

  Serial.print("\n\rIniciando conexão WiFi...\n\r");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("#");
    delay(500);
  }

  Serial.print("\n\rConectado com sucesso!\n\r");
  Serial.printf("Endereço IPv4: %s\n\r", WiFi.localIP().toString().c_str());
  Serial.printf("Endereço MAC: %s\n\r", WiFi.macAddress().c_str());

  clima = pedirParaApiClima("%C");
  temperatura = pedirParaApiClima("%t").toInt();
  sensacaoTermica = pedirParaApiClima("%f").toInt();

  Serial.printf("Condição climatica para hoje: %s\n\r", clima.c_str());
  Serial.printf("Temperatura atual: %d°C e sensação termica %d°C", temperatura, sensacaoTermica);

  telaLCD();
}

void loop()
{
}

String pedirParaApiClima(String codigo)
{
  HTTPClient http;
  http.begin(enderecoApiClima + codigo);

  int codigoHTTP = http.GET(); //*Retorna o código HTTP ex.: 200 -> ok, 404 -> página não encontrada.
  String resposta;

  if (codigoHTTP == 200) //*OK.
  {
    resposta = http.getString(); //*Retorna o conteudo HTML da página.
  }

  else
  {
    Serial.printf("Deu erro. Código: %d\n\r", codigoHTTP);
  }

  http.end();
  return resposta;
}

void telaLCD()
{
  clima = pedirParaApiClima("%C");
  temperatura = pedirParaApiClima("%t").toInt();
  sensacaoTermica = pedirParaApiClima("%f").toInt();
  lcd.setCursor(0, 0);
  lcd.printf("Temperatura: %dC", temperatura);
  lcd.setCursor(0, 1);
  lcd.printf("Sens. term. %dC", sensacaoTermica);
}
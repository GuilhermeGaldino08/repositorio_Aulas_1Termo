#include "func.h"

String obterNomeCor(int codigoCor)
{
  switch (codigoCor)
  {
  case 0:
    return "Preto";

  case 1:
    return "Marrom";

  case 2:
    return "Vermelho";

  case 3:
    return "Laranja";

  case 4:
    return "Amarelo";

  case 5:
    return "Verde";

  case 6:
    return "Azul";

  case 7:
    return "Violeta";

  case 8:
    return "Cinza";

  case 9:
    return "Branco";

  default:
    return "Invalido, escolha entre 0 à 9";
  }
}

float calcularMedia(float valor1, float valor2)
{
  float resultado = (valor1) + (valor2) / 2;
  return resultado;
}

bool verificarTemperatura(int tempAtual, int limTemp)
{
  return tempAtual <= limTemp ? true : false;
}

bool botaoPressionado(int pinBotao)
{
  bool estado = digitalRead(pinBotao);
  return estado ? true : false;
}
#include <Arduino.h>

void textoTipoC();
void textoTipoSTR();

void setup()
{
  Serial.begin(9600);
  Serial.println();
  textoTipoC();
  textoTipoSTR();
}

void loop()
{
}

void textoTipoC()
{
  //*texto literal
  //*Use CONST CHAR* quando o texto não será alterado
  const char *cidade = "Sao Paulo";
  const char outraCidade[] = "Sao Caetano";
  Serial.println(cidade);
  Serial.println(outraCidade);

  //*Descobrindo o tamanho do texto
  //*strlen conta quantos caracteres antes do '/0'
  int tamanhoCidade = strlen(cidade);
  int tamanhoOutraCidade = strlen(outraCidade);

  Serial.print("Comprimento do texto em caracteres: ");
  Serial.println(tamanhoOutraCidade);

  Serial.print("Tamanho do conteudo do ponteiro: ");
  Serial.println(tamanhoCidade);

  //*Descobrindo o tamanho ocupado
  int tamanhoVariavel = sizeof(outraCidade);
  int tamanhoPonteiro = sizeof(cidade);

  //*Quando usamos o sizeof em uma string sempre retornará
  //*um byte a mais do que a quantidade de caracteres por
  //*causa do '/0' que finaliza o texto
  Serial.print("Tamanho da variavel em bytes: ");
  Serial.println(tamanhoVariavel);

  //*Quando usamos o sizeof em ponteiros retorna sempre 4 bytes
  //*pois o conteúdo dee é um endereço de memoria como 0xFF00C245
  Serial.print("Tamanho do ponteiro: ");
  Serial.println(tamanhoPonteiro);

  //*O caractere '/0' é colocado automaticamente quando escrevemos
  //*um texto entre aspas duplas "".
  const char vetorTexto[7] = {'T', 'h', 'i', 'a', 'g', 'o', '/0'};
  Serial.print(vetorTexto);

  //*Comparar texto
  const char *cidade1 = "Porto Alegre";
  const char *cidade2 = "Porto Alegre";

  if (strcmp(cidade1, cidade2) == 0)
    Serial.println("As strings são iguais");

  else
    Serial.println("As strings são diferentes");

  //*strcmp analiza a ordem lexica (ordem alfabetica das palavras) das palavras,
  //*se a primeria palavra vem antes que a segunda, o valor retornado será menor que zero (0)
  //*se a primeira palavra vem após a segunda, o retorno será maior que zero (0)

  //?=========================
  //?TEXTO EDITAVEL COM char()
  //?=========================

  char nomeAluno[10] = "Guilhermo";
  Serial.println(nomeAluno);

  nomeAluno[8] = 'e';
  Serial.println(nomeAluno);

  //*Copiando outro texto para dentro do vetor
  //! CUIDADO: o vetor precisa ter espaço suficiente

  strcpy(nomeAluno, "Tadeu");
  Serial.println(nomeAluno);

  //*Concatenando texto ao final
  char frase[40] = "Ola ";
  strcat(frase, "Mundo cruel!");
  Serial.println(frase);

  //*Procurando um caractere no texto
  char *posicaoLetra = strchr(frase, 'M');

  if (posicaoLetra != NULL)
  {
    Serial.println("Letra encontrada");
    Serial.println(posicaoLetra);
  }

  else
    Serial.println("Letra não encontrada");

  //*Convertendo texto numérico para inteiro
  char idadeTexto[] = "39"; //*[0x33, 0x39, 0x00]
  int idade = atoi(idadeTexto);

  //*Montando texto
  char buffer[100];
  char *local = "Sala de aula";
  float temperatura = 26.4;
  int umidade = 72;

  snprintf(buffer, sizeof(buffer), "%s | Temp: %f C | Umid: %d %% \n\r", local, temperatura, umidade);
  Serial.print(buffer);

  //*snprintf monta o texto dentro de um vetor de char
  //*Isso é muito util quando depois vc quer:
  //* - Enviar por MQTT
  //* - Salvar em variavel
  //* - Mandar para o display
  //* - Imprimir na Serial

  //*ESPECIFICADORES
  //*   %d ou %i    - int
  //*   %u          - unsigned int
  //*   %ld         - long
  //*   %lu         - unsigned long
  //*   %f          - float
  //*   %e          - notação cientifica
  //*   %g          - float, formato mais curto
  //*   %c          - char
  //*   %s          - char*
  //*   %x ou %X    - hexadecimal minusculo/maiusculo
  //*   %o          - octal
  //*   %p          - ponteiro
  //*   %%          - O proprio %

  //* FLAGS, LARGURA E PRECISAO
  //*   %5d         - imprime com largura minima de 5, alinhado a direita
  //*   %-2d        - imprime com largura minima de 2, alinhado a esquerda
  //*   %04d        - completa com zeros ex. 0022
  //*   %+d         - sempre mostra o sinal ex. +5
  //*   %.2f        - 2 casas decimais
  //*   %4.2f       - largura de 4 com 2 casas
  //*   %02x        - hexadecimal com 2 digitos
  //*   %#x         - prefixo 0x
  //*   %.3s        - só os primerios 3 caracteres da string  
  //*   %*d         - largura passada como argumento ex. snprintf(buffer, sizeof(buffer), "%*d", 5, 42) [   42]
}

void textoTipoSTR()
{
  String nome = "Guilherme";
  String curso = "Lógica de programação";
  String mensagem = "Olá";

  mensagem = mensagem + "," + nome + "! Bem vindo ao curso de " + curso + ".";
  Serial.println(mensagem);
}
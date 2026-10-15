#include <Arduino.h>

void funcaoBloqueante();
void funcaoNaoBloqueante();
void processarFrase(char *texto);
int lerProximoNumro(char* &cursor);
void aplicarCor();

int vermelho = 0;
int verde = 0;
int azul = 0;
int brilho = 0;

void setup()
{
  Serial.begin(115200);

  //*O metodo readStringUntil espera no maximo por caractere esse tempo(ms) pelo "\n"
  Serial.setTimeout(2000);
  // Serial.println();
  // Serial.println("Digite seu nome e pressione Enter");
}

void loop()
{
  funcaoNaoBloqueante();
}

void funcaoNaoBloqueante()
{
  const int tamanho_max = 50; //* Tamanho do vetor que inclui o '/0'
  static char frase[tamanho_max];
  static int position = 0;

  while (Serial.available() > 0)
  {
    char c = Serial.read();

    if (c == '\r')
      continue;
    //*O 'continue' pula o restante do while() naquela volta e passa para leitura
    //*do próximo caractere. O '\r' é lido e simplesmente descartado, sem entrar no vetor.

    if (c == '\n')
    {
      frase[position] = '\0';
      if (position > 0)
        processarFrase(frase);
      position = 0;
    }

    else if (position < tamanho_max - 1)
    {
      frase[position] = c;
      position++;
    }
  }
}

//* VERMELHO, VERDE, AZUL, BRANCO, DESLIGA
//* RGB r g b (ex: RGB 255 180 5)
//*BRILHO n (0 a 100%)
void processarFrase(char *texto)
{
  Serial.printf("Recebido: [%s]\n\r", texto);
  char *comando = texto;
  char *parametro = NULL; //* '\0'

  char *espaco = strchr(texto, ' '); //* Procura pelo primeiro espaco no texto

  if (espaco != NULL)
  {
    *espaco = '\0'; //* Substitui o espaco por um \0
    parametro = espaco + 1;
  }

  //*strCASEcmp verifica a posicao lexica das palavras ignorando
  //*letras maiusculas ou minusculas
  if (strcasecmp(comando, "VERMELHO") == 0)
  {
    vermelho = 255;
    azul = 0;
    verde = 0;
    brilho = 100;
  }

  else if (strcasecmp(comando, "VERDE") == 0)
  {
    vermelho = 0;
    azul = 0;
    verde = 255;
    brilho = 100;
  }

  else if (strcasecmp(comando, "AZUL") == 0)
  {
    vermelho = 0;
    azul = 255;
    verde = 0;
    brilho = 100;
  }

  else if (strcasecmp(comando, "BRANCO") == 0)
  {
    vermelho = 255;
    azul = 255;
    verde = 255;
    brilho = 100;
  }

  else if (strcasecmp(comando, "DESLIGA") == 0)
  {
    vermelho = 0;
    azul = 0;
    verde = 0;
    brilho = 0;
  }

  else if (strcasecmp(comando, "RGB") == 0)
  {
    if (parametro == NULL)
    {
      Serial.println("Use o comando: RGB r g b (0 a 255)");
      return;
    }

    //*RGB 255 65 89
    char *cursor = parametro;
    int r = lerProximoNumro(cursor);
    int g = lerProximoNumro(cursor);
    int b = lerProximoNumro(cursor);

    vermelho = constrain(r, 0, 255);
    verde = constrain(g, 0, 255);
    azul = constrain(b, 0 , 255);
  }

  else if (strcasecmp(comando, "BRILHO") == 0)
  {
    if(parametro == NULL)
    {
      Serial.println("Use o comando: Brilho n (0 a 100)");
      return;
    }

    brilho = constrain(atoi(parametro), 0, 100);
  }

  else
  {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "comando: [%s] não existe", comando);
    Serial.println(buffer);
    return;
  }
  aplicarCor();
}

//* Cursor é uma referencia (&) para um ponteiro (char*)
//* A função recebe a propria variavel de quem chamou e não cópia
//*
//* PARAMETRO       | ALTERA O TEXTO APONTADO | ALTERA PARA ONDE O PONTEIRO DE FORA APONTA
//* char* p         | sim (*p = '\0')         | Não, pq ele é uma copia do ponteiro
//* const char* p   | não                     | não
//* char* &p        | sim                     | sim, é a propria variavel passada como parametro

int lerProximoNumro(char* &cursor)
{
  if(cursor == NULL) return 0;
  
  //* 20 130 60
  int valor = atoi(cursor);

  char* espaco = strchr(cursor, ' ');
  cursor = (espaco != NULL) ? espaco + 1 : NULL;

  return valor;
}

void aplicarCor()
{
  int r = vermelho * brilho / 100;
  int g = verde * brilho / 100;
  int b = azul * brilho / 100;

  rgbLedWrite(PIN_RGB_LED, r, g, b);

  char bufferMensagem[61];
  snprintf(bufferMensagem, sizeof(bufferMensagem), 
           "Cor: R=%3d G=%3d B=%3d | Birlho: %3d %% | HEX: #%02X%02X%02X",
           vermelho, verde, azul, brilho, r, g, b);
  Serial.println(bufferMensagem);
}

// void funcaoBloqueante()
// {
//   //*Avaliable() diz quantos bytes já chegaram e estão esperando leitura
//   if(Serial.available() > 0)
//   {
//     String texto = Serial.readStringUntil('\n'); //! FUNÇÃO BLOQUEANTE
//
//     //*trim() remove do fim do texto os espaços, '\r', '\t', '\n', que alguns terminais enviam
//     texto.trim();
//
//     if(texto.length() == 0) return;
//
//     Serial.printf("Seu nome é %s\n\r", texto.c_str());
//
//     String textoMaiusculas = texto;
//     textoMaiusculas.toUpperCase();
//     if (textoMaiusculas == "GUILHERME") Serial.println("Esse é o seu nome correto.");
//     else Serial.println("Voce é um animal");
//   }
// }
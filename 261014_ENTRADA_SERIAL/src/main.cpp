#include <Arduino.h>

void funcaoBloqueante();
void funcaoNaoBloqueante();
void processarFrase(char* texto);

void setup()
{
  Serial.begin(115200);

  //*O metodo readStringUntil espera no maximo por caractere esse tempo(ms) pelo "\n"
  Serial.setTimeout(2000);
  Serial.println();
  Serial.println("Digite seu nome e pressione Enter");
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

  while(Serial.available() > 0)
  {
    char c = Serial.read();

    if(c == '\r') continue;
    //*O 'continue' pula o restante do while() naquela volta e passa para leitura 
    //*do próximo caractere. O '\r' é lido e simplesmente descartado, sem entrar no vetor.

    if(c == '\n')
    {
      frase[position] = '\0';
      if(position > 0) processarFrase(frase);
      position = 0;
    }

    else if(position < tamanho_max - 1)
    {
      frase[position] = c;
      position++;
    }
  }
}

//* VERMELHO, VERDE, AZUL, BRANCO, DESLIGA
//* RGB r g b (ex: RGB 255 180 5)
//*BRILHO n (0 a 100%)
void processarFrase(char* texto)
{
  Serial.printf("Recebido: [%s]\n\r", texto);
  char* comando = texto;
  char* parametro = NULL; //* '\0'

  char* espaco = strchr(texto, ' '); //* Procura pelo primeiro espaco no texto

  if( espaco != NULL)
  {
    *espaco = '\0'; //* Substitui o espaco por um \0
    parametro = espaco + 1;
  }

  //*strCASEcmp verifica a posicao lexica das palavras ignorando 
  //*letras maiusculas ou minusculas
  if(strcasecmp(comando, "VERMLHO") == 0)
  {

  }

  else if(strcasecmp(comando, "VERDE") == 0)
  {

  }

  else if(strcasecmp(comando, "AZUL") == 0)
  {

  }

  else if(strcasecmp(comando, "BRANCO") == 0)
  {

  }

  else if(strcasecmp(comando, "DESLIGA") == 0)
  {

  }

  else if(strcasecmp(comando, "RGB") == 0)
  {

  }
  
  else if(strcasecmp(comando, "BRILHO") == 0)
  {

  }
}

// void funcaoBloqueante()
// {
//   //*Avaliable() diz quantos bytes já chegaram e estão esperando leitura
//   if(Serial.available() > 0)
//   {
//     String texto = Serial.readStringUntil('\n'); //! FUNÇÃO BLOQUEANTE  

//     //*trim() remove do fim do texto os espaços, '\r', '\t', '\n', que alguns terminais enviam
//     texto.trim();

//     if(texto.length() == 0) return;

//     Serial.printf("Seu nome é %s\n\r", texto.c_str());

//     String textoMaiusculas = texto;
//     textoMaiusculas.toUpperCase();
//     if (textoMaiusculas == "GUILHERME") Serial.println("Esse é o seu nome correto.");
//     else Serial.println("Voce é um animal");
//   }
// }
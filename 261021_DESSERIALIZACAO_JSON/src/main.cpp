#include <Arduino.h>
#include <ArduinoJson.h>

void setup()
{
  Serial.begin(115200);

  //* RAW - String Literal
  const char *resposta = R"({
    "nome": "Guilherme",
    "idade": 18,
    "naturalidade": "Portugal",
    "profissao": "Desempregado",
    "isSingle": true,
    "hobbies": ["Dormir", "Treinar"],
    "endereco": {
        "rua":"Niterói",
        "numero": "180",
        "coordenadas": {
            "lat": -23.62,
            "lon": -46.55
        }
    }
  })";

  JsonDocument doc;
  //* DeserelizationError é um tipo, uma classe do arduinoJson que guarda o código de erro
  //* Informando que o parse (Segmentação de chave valor) terminou.
  DeserializationError errorJson = deserializeJson(doc, resposta);

  //!===================POSSIVEIS ERROS===================
  //* 0 ou Ok                  | Sucesso
  //* 1 ou EmptyInput          | Entrada vazia ou timeout de strem
  //* 2 ou IncompleteInput     | Json cortado antes de terminar
  //* 3 ou InvalidInput        | Sintaxe invalida
  //*
  //* 4 ou NoMemory            | Memoria insuficiente para montar o documento
  //*                          | ex.: (API do Pokemon - Retorna um Json muito grande)
  //*
  //* 5 ou TooDeep             | Aninhamento acima do limite definido pela função NestingLimit definido como
  //*                          | padrão em ARDUINOJSON_DEFAULT_NESTING_LIMIT = 10
  //*                          | cada { ou [ aberto dentro do outro soma um nível.
  //*                          | ex.: {"a": {"b": [1, 2]}} tem 3 níveis.

  switch (errorJson.code())
  {
  case DeserializationError::Ok:
    break;

  case DeserializationError::InvalidInput:
    Serial.println("JSON com sintaxe inválida");
    return;

  case DeserializationError::EmptyInput:
    Serial.println("JSON vazio ou expirou o tempo");
    return;

  case DeserializationError::IncompleteInput:
    Serial.println("JSON incompleto");
    return;

  case DeserializationError::NoMemory:
    Serial.println("Sem memória");
    return;

  case DeserializationError::TooDeep:
    Serial.println("Aninhamento acima do limite definido pela função");
    return;

  default:
    Serial.println(errorJson.c_str());
    return;
  }

  //* Verifica a existencia da chave, caso não existir passe um valor negativo definido
  //* Para indicar a inexistencia, pois 0 neste caso é um valor possivel
  //* o simbolo "|" (pipe) aqui não é um "OU bit a bit", a biblioteca redefine esse operador
  //* para significar "valor padrão", a lógica é se o valor a esquerda puder
  //* ser convertido para o tipo da direita ele, usa ele; se não usa o da direita.
  //* Verificar a existencia da chave e o seu tipo correto.

  String nome = doc["nome"] | "Não informado";
  int idade = doc["idade"] | -1;
  String naturalidade = doc["naturalidade"] | "Não informado";
  String profissao = doc["profissao"] | "Não informado";
  bool estadoCivil = doc["isSingle"] | false;

  //* for range-based ou for loop | for baseado em intervalos
  //* informalmente é chamado de foreach (para cada) pq é o nome
  //* do mesmo recurso em outras linguagens.

  //* Tratamento de vetores
  const char *vetor_hobbies[10];
  size_t posicaoHobbies = 0;
  size_t tamanhoVetorMax = sizeof(vetor_hobbies) / sizeof(vetor_hobbies[0]);

  //* size_t é o tipo inteiro usado para representar tamanhos e quantidades
  //* de bytes de memóriam números de elemento e índices de vetor, é o tipo que
  //* a função sizeof() retorna. Não tem sinal (unsigned) e a largura depende
  //* da arquitetura mas tem o tamanho necessario para representar qualquer objeto
  //* na memória da maquina em questão.

  //* sizeof() retorna o tamanho em bytes, porém cada posição pode ter mais que um byte
  //* por isso dividimos o tamanho total pelo tamanho de um item do vetor existente,
  //* como sempre existe a posição [0], utilizamos ela como padrão.

  //* sizeof() em printf usar %zu

  if (doc["hobbies"].is<JsonArray>())
  {
    for (JsonVariantConst v : doc["hobbies"].as<JsonArrayConst>())
    {
      if (posicaoHobbies >= tamanhoVetorMax)
        break;

      vetor_hobbies[posicaoHobbies++] = v | "Não informado";
    }

    //* JsonVariantConst representa um valor Json qualquer: texto, número, booleano, null, objeto ou array
    //* O tipo só é conhecido em tempo de execução, por isso é necessário verificar com is<T>() e converter
    //* com as<T>(). É usado quando ainda não se sabe ou não importa o que está sendo guardado ali.

    //* JsonArrayConst representa um array Json, e oferece operações de array:
    //* array.size()                   | retorna quantidade de itens
    //* array.isNull()                 | retorna true se não aponta para um array
    //* array.nesting()                | retorna a profundidade de aninhamento dentro do array
    //* array[i] = item na posição i   | ex.: array[1].as<const char*>() retornaria um "texto"
    //* array[i] | default             | retorna item ou valor padrão se null
    //* array[i].is<T>()               | retorna true para o teste de tipo T
    //*
    //* Acessar um índice fora do limite do array não trava, retorna valor nulo(0, false, nullptr)

    //* Em casos de array de números ou booleanos é possivel copiar um array para outro
    //! (NÃO FUNCIONA COM STRING)
    //* int notas[10];
    //* size_t quantidadeItensCopiados = copyArray(doc["numeros"].as<JsonArrayConst>(), notas);
    //* quando o vetor destino enche não trava e devolve quantos itens foram copiados.

    for (size_t i = 0; i < posicaoHobbies; i++)
    {
      Serial.printf("Hobby %d: %s\n\r", i + 1, vetor_hobbies[i]);
    }
  }

  Serial.printf("\nMeu nome é: %s, tenho %s anos, sou de %s, trabalho como %s e atualmente estou %s",
                nome,
                idade < 0 ? "Não informado" : String(idade).c_str(),
                naturalidade,
                profissao,
                estadoCivil ? "Solteiro" : "Comprometido");

  //* Aninhamento
  //* Jeito 1:
  if(doc["endereco"]["rua"].is<const char*>())
    const char* rua = doc["endereco"]["rua"].as<const char*>();
    
  float lat = doc["endereco"]["coordenadas"]["lat"] | 0.0f;

  //*Jeito 2:
  JsonObjectConst endereco = doc["endereco"];
  Serial.println(endereco["endereco"].as<const char*>());
  Serial.println(endereco["coordenadas"]["lon"].as<float>());

  JsonObjectConst coordenadas = doc["endereco"]["coordenadas"];
  Serial.println(coordenadas["lat"].as<float>());
  Serial.println(coordenadas["lon"] | 0.0f);
}

void loop()
{}
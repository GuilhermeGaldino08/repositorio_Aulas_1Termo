#include <Arduino.h>
#include <ArduinoJson.h>

void setup()
{
  Serial.begin(115200);
  uint32_t quantidade = 30UL;

  float temperatura1 = 2.8f;
  float temperatura2 = 37.89f;
  float temperatura3 = 130.5f;

  bool estaLigado = false;
  const char *nomeDispositivo = "ESP32-S3";
  int pinosUsados[] = {1, 4, 6, 22, 37, 41};

  //* O Heap é a área da RAM usada para alocação dinâmica
  //* É reservada e liberada durante a execução, conforme a necessidade
  //*
  //* Outras áreas da RAM"
  //* - Memoria estática      | Guarda variaveis globais e static
  //* - Pilha (stack)         | Guarda variaveis locais  das funções

  Serial.printf("Inicial - Heap Livre: %u bytes\n\r", ESP.getFreeHeap());
  Serial.printf("Inicial - Maior bloco de memória livre: %u bytes\n\r", ESP.getMaxAllocHeap());

  JsonDocument doc;
  doc["quantidade"] = quantidade;
  doc["estaLigado"] = estaLigado;
  doc["nomeDispositivo"] = nomeDispositivo;

  //*==========ARRAY / VETOR==========
  JsonArray pinos = doc["pinos"].to<JsonArray>();
  size_t tamanhoVetorPinos = sizeof(pinosUsados) / sizeof(pinosUsados[0]);

  //*JEITO 1: PARA TODOS OS CASOS
  for (int i = 0; i < tamanhoVetorPinos; i++)
  {
    pinos.add(pinosUsados[i]);
  }

  //*JEITO 2: APENAS PARA NUMEROS OU BOOLEANOS
  pinos.clear();
  copyArray(pinosUsados, tamanhoVetorPinos, pinos);

  //*==========OBJETOS JSON==========
  JsonObject temps = doc["temperaturas"].to<JsonObject>();
  temps["sensor1"] = temperatura1;
  temps["sensor2"] = temperatura2;
  temps["sensor3"] = temperatura3;

  bool faltouMemoriaErro = doc.overflowed();
  if (faltouMemoriaErro)
    return; //* Clausula de guarda

  char Buffer[512];
  serializeJson(doc, Buffer, sizeof(Buffer));
  Serial.println(Buffer);

  JsonDocument doc2; //* Usado para deserializar o Json recebido

  JsonDocument filtro; //* Usado como modelo para o filtro de chaves JSON
  filtro["estaLigado"] = true;
  filtro["temperaturas"] = true;

  DeserializationError erroJson = deserializeJson(doc2, Buffer, DeserializationOption::Filter(filtro));
  //* Pretty envia bonitinho

  Serial.println(doc2["estaLigado"].as<bool>() ? "Está ligado" : "Está desligado");
  Serial.printf("Temp 1: %6.2f\nTemp 2: %6.2f\nTemp 3: %6.2f\n\r",
                doc2["temperaturas"]["sensor1"].as<float>(),
                doc2["temperaturas"]["sensor2"].as<float>(),
                doc2["temperaturas"]["sensor3"].as<float>());

  if (doc2["nomeDispositivo"].is<const char *>())
  {
    Serial.printf("Nome do dispositivo: %s", doc2["nomeDispositivo"].as<const char *>());
  }

  else
  {
    Serial.println("Nome do dispositivo não encotrado");
  }

  Serial.printf("Final - Heap Livre: %u bytes\n\r", ESP.getFreeHeap());
  Serial.printf("Final - Maior bloco de memória livre: %u bytes\n\r", ESP.getMaxAllocHeap());
}

void loop()
{
}
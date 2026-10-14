#include <Arduino.h>

const int pinLedVermelho = 2;
const int pinLedVerde = 45;
const int pinLedAmarelo = 38;

void setup() {
    pinMode(pinLedVermelho, OUTPUT);
    pinMode(pinLedVerde, OUTPUT);
    pinMode(pinLedAmarelo, OUTPUT);

    // *x = x + 1 -> x++;
    // *x = x - 1 -> x--;
    // *x = x + 10 -> x += 10;
    // *x = x * 2 -> x *= 2;
    // *x = x / 2 -> x /= 2;
}

void loop() {
    for(int i= 0; i <5; i++ )
    {
        digitalWrite(pinLedVermelho, HIGH);
        delay(200);
        digitalWrite(pinLedVermelho, LOW);
        delay(200);
    }

    for(int i= 0; i <5; i++ )
    {
        digitalWrite(pinLedAmarelo, HIGH);
        delay(200);
        digitalWrite(pinLedAmarelo, LOW);
        delay(200);
    }

    for(int i= 0; i <5; i++ )
    {
        digitalWrite(pinLedVerde, HIGH);
        delay(200);
        digitalWrite(pinLedVerde, LOW);
        delay(200);
    }
}

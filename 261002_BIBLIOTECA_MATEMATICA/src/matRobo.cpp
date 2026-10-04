#include <Arduino.h>
#include "matRobo.h"

float calcularDobro(float valor)
{
    float resultado = (valor) * 2;
    return resultado;
}

bool ehPar(int valor)
{
    return (valor % 2 == 0);
}

float calculadoraMagica(float valor1, float valor2, int caso)
{
    switch (caso)
    {
    case 1:
        return valor1 + valor2;

    case 2:
        return valor1 - valor2;

    case 3:
        return valor1 * valor2;

    default:
        return 0;
    }
}

int numeroFatorial(int valor1)
{
    int resultado = 1;
    if (valor1 > 0)
    {
        while (valor1 > 1)
        {
            resultado = resultado * (valor1);
            valor1--;
        }
    }
    return resultado;
}
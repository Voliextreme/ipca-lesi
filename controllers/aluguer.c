#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "aluguer.h"
#include "conta.h"
#include "meio.h"

Aluguer *alugarMeio(Aluguer *inicio ,Meio *inicioMeio, int codigoMeio, int idCliente, User *inicioUser)
{
    bool meioDisponivel;
    bool meioExiste = existeMeio(inicioMeio, codigoMeio);
    printf("%d", meioExiste);

    if (!meioExiste)
    {
        printf("Meio nao existe");
    }
    else
    {
        meioDisponivel = disponibilidadeMeio(inicioMeio, codigoMeio);
        if (meioDisponivel)
        {
            Aluguer *novo = malloc(sizeof(struct aluga));
            if (novo != NULL)
            {
                novo->idMeio = codigoMeio;
                novo->idCliente = idCliente;
                novo->seguinte = inicio;
                return (novo);
            }
        }
    }
}

int disponibilidadeMeio(Meio *inicio, int cod)
{
    while (inicio != NULL)
    {
        if (inicio->codigo == cod && inicio->disponivel == true)
            return (1);
        inicio = inicio->seguinte;
    }
    return (0);
}

Aluguer *devolverMeio(Meio *inicio, int codigoMeio, int idCliente)
{
    return (NULL);
}
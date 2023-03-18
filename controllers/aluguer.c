#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "aluguer.h"
#include "conta.h"
#include "meio.h"

Aluguer *alugarMeio(Aluguer *inicio, Meio *inicioMeio, int codigoMeio, int idCliente, User *inicioUser)
{
    int cod = 1;
    bool meioDisponivel;
    bool meioExiste = existeMeio(inicioMeio, codigoMeio);

    if (!meioExiste)
    {
        printf("Meio nao existe");
    }
    else
    {
        meioDisponivel = disponibilidadeMeio(inicioMeio, codigoMeio);
        if (meioDisponivel && !existeAluguer(inicio, cod))
        {
            Aluguer *novo = malloc(sizeof(struct aluga));
            if (novo != NULL)
            {
                novo->idAluguer = cod;
                novo->idMeio = codigoMeio;
                novo->idCliente = idCliente;
                novo->seguinte = inicio;
                return (novo);
            }
            else
            {
                cod++;
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

int existeAluguer(Aluguer *inicio, int idAluguer)
{
    while (inicio != NULL)
    {
        if (inicio->idAluguer == idAluguer)
            return (1);
        inicio = inicio->seguinte;
    }
    return (0);
}

int devolverMeio(Meio *inicio, int codigoMeio, int idCliente)
{
    while (inicio != NULL)
    {
        if (inicio->codigo == codigoMeio && inicio->disponivel == false)
        {
            inicio->disponivel = true;
            return (1);
        }
        inicio = inicio->seguinte;
    }
    return (0);
}

void listarAlugueres(Aluguer *inicio)
{
    printf("ID Aluguer; ID Meio; ID Cliente\n");
    while (inicio != NULL)
    {
        printf("%d  %d  %d\n", inicio->idAluguer, inicio->idMeio, inicio->idCliente);
        inicio = inicio->seguinte;
    }
}

Aluguer *lerAlugueres()
{
    FILE *fp;
    int idAluguer, idMeio, idCliente;
    Aluguer *aux = NULL;
    fp = fopen("alugueres.txt", "r");
    if (fp != NULL)
    {
        while (!feof(fp))
        {
            fscanf(fp, "%d;%d;%d\n", &idAluguer, &idMeio, &idCliente);
            aux = alugarMeioFicheiro(aux, idAluguer, idMeio, idCliente);
        }
        fclose(fp);
    }else{
        printf("Erro ao abrir o ficheiro");
    }
    return (aux);
}

Aluguer *alugarMeioFicheiro(Aluguer *inicio, int idAluguer, int codigoMeio, int idCliente)
{
    if (!existeAluguer(inicio, idAluguer))
    {
        Aluguer *novo = malloc(sizeof(struct aluga));
        if (novo != NULL)
        {
            novo->idAluguer = idAluguer;
            novo->idMeio = codigoMeio;
            novo->idCliente = idCliente;
            novo->seguinte = inicio;
            return (novo);
        }
    }
}

int guardarAlugueres(Aluguer *inicio)
{
    FILE *fp;
    fp = fopen("alugueres.txt", "w");
    if (fp != NULL)
    {
        Aluguer *aux = inicio;
        while (aux != NULL)
        {
            fprintf(fp, "%d;%d;%d\n", aux->idAluguer, aux->idMeio, aux->idCliente);
            aux = aux->seguinte;
        }
        fclose(fp);
        return (1);
    }
    else
        return (0);
}


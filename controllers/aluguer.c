#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "aluguer.h"
#include "conta.h"
#include "meio.h"

Aluguer *alugarMeio(Aluguer *inicio, Meio *inicioMeio, int codigoMeio, int idCliente, User *inicioUser)
{
    int meioDisponivel = disponibilidadeMeio(inicioMeio, codigoMeio);
    int meioExiste = existeMeio(inicioMeio, codigoMeio);
    int cod = 1;

    if (!meioExiste)
    {
        printf("Meio nao existe");
    }
    else
    {
        while (1)
        {
            if (!userTemAluguer(inicio, idCliente))
            {
                if (!existeAluguer(inicio, cod))
                {
                    if (meioDisponivel)
                    {
                        Aluguer *novo = (struct aluga *)malloc(sizeof(struct aluga));
                        if (novo != NULL)
                        {
                            novo->idAluguer = cod;
                            novo->idMeio = codigoMeio;
                            novo->idCliente = idCliente;
                            novo->seguinte = inicio;
                            setMeioAlugado(&inicioMeio, codigoMeio);
                            return (novo);
                        }
                    }
                    else
                    {
                        printf("\nEste meio ja se encontra alugado \n");
                        return (inicio);
                    }
                }
                else
                {
                    cod++;
                }
            }
            else
            {
                printf("O utilizador ja tem um aluguer");
                return (inicio);
            }
        }
    }
    return (inicio);
}

int userTemAluguer(Aluguer *inicio, int idCliente)
{
    while (inicio != NULL)
    {
        if (inicio->idCliente == idCliente)
            return (1);
        inicio = inicio->seguinte;
    }
    return (0);
}

int disponibilidadeMeio(Meio *inicio, int cod)
{
    while (inicio != NULL)
    {
        if (inicio->codigo == cod && inicio->disponivel == 1)
            return (1);
        inicio = inicio->seguinte;
    }
    return (0);
}

void setMeioAlugado(Meio **inicio, int cod)
{
    while (*inicio != NULL)
    {
        if ((*inicio)->codigo == cod)
        {
            (*inicio)->disponivel = 0;
        }
        inicio = &(*inicio)->seguinte;
    }
}

Aluguer *removerAluguer(Aluguer *inicio, int idAluguer)
{
    Aluguer *aux = inicio;
    Aluguer *anterior = NULL;

    printf("Aqui %d", idAluguer);

    while (aux != NULL)
    {
        if (aux->idAluguer == idAluguer)
        {
            if (anterior == NULL)
            {
                inicio = aux->seguinte;
            }
            else
            {
                anterior->seguinte = aux->seguinte;
            }
            free(aux);
            return (inicio);
        }
        anterior = aux;
        aux = aux->seguinte;
    }
    return (inicio);
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

int devolverMeio(Meio **inicio, Aluguer *alugueres, int codigoAluguer)
{
    while (alugueres != NULL)
    {
        if (alugueres->idAluguer == codigoAluguer)
        {
            while (*inicio != NULL)
            {
                if ((*inicio)->codigo == alugueres->idMeio)
                {
                    (*inicio)->disponivel = 1;
                    return (1);
                }
                inicio = &(*inicio)->seguinte;
            }
        }
        alugueres = alugueres->seguinte;
    }
    return (0);
}

void listarAlugueres(Aluguer *inicio)
{
    printf("\nID Aluguer ID Meio ID Cliente\n");
    while (inicio != NULL)
    {
        printf("Aluguer:%d  Meio:%d  Cliente:%d\n", inicio->idAluguer, inicio->idMeio, inicio->idCliente);
        inicio = inicio->seguinte;
    }
}
// Listar apenas os alugueres do user
int listarAlugueresUser(Aluguer *inicio, int idCliente)
{
    printf("\nID Aluguer | ID Meio \n");
    while (inicio != NULL)
    {
        // Verificar se o aluguer é do cliente que esta a ser usado
        if (inicio->idCliente == idCliente && inicio->idAluguer != 0)
        {
            printf("Aluguer:%d  Meio:%d\n", inicio->idAluguer, inicio->idMeio);
            // retornar o id do Aluguer disponivel do user
            return (inicio->idAluguer);
        }
        inicio = inicio->seguinte;
    }
    return (0);
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
    }
    else
    {
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

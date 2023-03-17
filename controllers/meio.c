#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "meio.h"


int guardarMeios(Meio *inicio)
{
    FILE *fp;
    fp = fopen("meios.txt", "w");
    if (fp != NULL)
    {
        Meio *aux = inicio;
        while (aux != NULL)
        {
            fprintf(fp, "%d;%f;%f;%s\n", aux->codigo, aux->bateria,
                    aux->autonomia, aux->tipo);
            aux = aux->seguinte;
        }
        fclose(fp);
        return (1);
    }
    else
        return (0);
}

Meio *lerMeios()
{
    FILE *fp;
    int cod;
    float bat, aut, custo;
    char tipo[50], geoCodigo[50];
    bool disponivel;
    Meio *aux = NULL;
    fp = fopen("meios.txt", "r");
    if (fp != NULL)
    {
        while (!feof(fp))
        {
            fscanf(fp, "%d;%f;%f;%s;%f;%s;%d\n", &cod, &bat, &aut, tipo, &custo, geoCodigo, &disponivel);
            aux = inserirMeio(aux, cod, tipo, bat, aut, custo, geoCodigo, disponivel);
        }
        fclose(fp);
    }
    return (aux);
}

// Inserção de um novo registo
Meio *inserirMeio(Meio *inicio, int codigo, char tipo[], float bateria, float autonomia, float custo, char geoCodigo[], bool disponivel)
{
    if (!existeMeio(inicio, codigo))
    {
        Meio *novo = malloc(sizeof(struct registo));
        if (novo != NULL)
        {
            novo->codigo = codigo;
            strcpy(novo->tipo, tipo);
            novo->bateria = bateria;
            novo->autonomia = autonomia;
            novo->custo = custo;
            strcpy(novo->geoCodigo, geoCodigo);
            novo->disponivel = true;
            novo->seguinte = inicio;
            return (novo);
        }
    }
    return (inicio);
}

// listar na consola o conteúdo da lista ligada
void listarMeios(Meio *inicio)
{
    while (inicio != NULL)
    {
        printf("%d %s %.2f %.2f %.2f %s %d\n", inicio->codigo, inicio->tipo,
               inicio->bateria, inicio->autonomia, inicio->custo, inicio->geoCodigo, inicio->disponivel);
        inicio = inicio->seguinte;
    }
}

// Determinar existência do 'codigo' na lista ligada 'inicio'
// devolve 1 se existir ou 0 caso contrário
int existeMeio(Meio *inicio, int cod)
{
    while (inicio != NULL)
    {
        if (inicio->codigo == cod)
            return (1);
        inicio = inicio->seguinte;
    }
    return (0);
}

// Remover um meio a partir do seu código{
Meio *removerMeio(Meio *inicio, int cod)
{
    Meio *anterior = inicio, *atual = inicio, *aux;

    if (atual == NULL)
        return (NULL);
    else if (atual->codigo == cod) // remoção do 1º registo
    {
        aux = atual->seguinte;
        free(atual);
        return (aux);
    }
    else
    {
        while ((atual != NULL) && (atual->codigo != cod))
        {
            anterior = atual;
            atual = atual->seguinte;
        }
        if (atual == NULL)
            return (inicio);
        else
        {
            anterior->seguinte = atual->seguinte;
            free(atual);
            return (inicio);
        }
    }
}

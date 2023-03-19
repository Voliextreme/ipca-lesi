#include <stdlib.h>
#include <string.h>

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
            fprintf(fp, "%d;%s;%f;%f;%f;%s;%d\n", aux->codigo, aux->tipo, aux->bateria,
                    aux->autonomia, aux->custo, aux->geoCodigo, aux->disponivel);
            aux = aux->seguinte;
        }
        fclose(fp);
        return (1);
    }
    return (0);
}

int guardarMeiosBin(Meio *inicio)
{
    FILE *fp;
    fp = fopen("./FicheirosBin/meios.bin", "wb");
    if (fp != NULL)
    {
        Meio *aux = inicio;
        while (aux != NULL)
        {
            fwrite(aux, sizeof(Meio), 1, fp);
            aux = aux->seguinte;
        }
        fclose(fp);
        return (1);
    }
    return (0);
}

Meio *lerMeios()
{
    FILE *fp;
    int codigo;
    float bateria, autonomia, custo;
    char tipo[50], geoCodigo[50];
    int disponivel;
    Meio *aux = NULL;
    
    fp = fopen("meios.txt", "r");
    if (fp != NULL)
    {
        while (!feof(fp))
        {
            fscanf(fp, "%d;%[^;];%f;%f;%f;%[^;];%d;\n",&codigo, tipo, &bateria, &autonomia, &custo, geoCodigo, &disponivel);
            aux = inserirMeio(aux,codigo, tipo, bateria, autonomia, custo, geoCodigo, disponivel);
        }
        fclose(fp);
    }
    else
        printf("Nao foi possivel ler o ficheiro de veiculos"); 
    
    return (aux);
}

// Inserção de um novo registo
Meio *inserirMeio(Meio *inicio, int codigo, char tipo[], float bateria, float autonomia, float custo, char geoCodigo[], int disponivel)
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
            novo->disponivel = 1;
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
        printf("%d %s %f %f %f %s %d\n", inicio->codigo, inicio->tipo,
               inicio->bateria, inicio->autonomia, inicio->custo, inicio->geoCodigo, inicio->disponivel);
        inicio = inicio->seguinte;
    }
}


void listarMeiosOrganizados(Meio **inicio)
{
    Meio *aux = *inicio;
    while (aux != NULL)
    {
        printf("%d %s %f %f %f %s %d\n", aux->codigo, aux->tipo,
               aux->bateria, aux->autonomia, aux->custo, aux->geoCodigo, aux->disponivel);
        *inicio = aux->seguinte;
        aux = aux->seguinte;
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


void listMeiosPorAutonomiaDecrescente(Meio **inicio)
{
    Meio *copia_inicio = NULL;
    Meio *atual = *inicio;


    while (atual != NULL)
    {
        Meio *novoMeio = malloc(sizeof(Meio));
        *novoMeio = *atual;
        novoMeio->seguinte = NULL;
        if (copia_inicio == NULL)
        {
            copia_inicio = novoMeio;
        }
        else
        {
            Meio *atual_copia = copia_inicio;
            while (atual_copia->seguinte != NULL)
            {
                atual_copia = atual_copia->seguinte;
            }
            atual_copia->seguinte = novoMeio;
        }
        atual = atual->seguinte;
    }

    Meio *meiosOrganizados = NULL;
    while (copia_inicio != NULL)
    {
        Meio *seguinte = copia_inicio->seguinte;
        Meio *novo_atual = meiosOrganizados;

        if (meiosOrganizados == NULL || meiosOrganizados->autonomia <= copia_inicio->autonomia)
        {
            copia_inicio->seguinte = meiosOrganizados;
            meiosOrganizados = copia_inicio;
        }
        else
        {
            while (novo_atual->seguinte != NULL && novo_atual->seguinte->autonomia > copia_inicio->autonomia)
            {
                novo_atual = novo_atual->seguinte;
            }
            copia_inicio->seguinte = novo_atual->seguinte;
            novo_atual->seguinte = copia_inicio;
        }
        copia_inicio = seguinte;
    }

    listarMeiosOrganizados(&meiosOrganizados);

    while (meiosOrganizados != NULL)
    {
        Meio *seguinte = meiosOrganizados->seguinte;
        free(meiosOrganizados);
        meiosOrganizados = meiosOrganizados->seguinte;
    }
}

void alterarMeio(Meio **inicio, int codigo)
{
    Meio *aux = *inicio;
    while (aux != NULL)
    {
        if (aux->codigo == codigo)
        {
            // Prompt user for new values
            printf("Digite o novo tipo: ");
            scanf("%s", aux->tipo);

            printf("Digite a nova capacidade da bateria: ");
            scanf("%f", &aux->bateria);

            printf("Digite a nova autonomia: ");
            scanf("%f", &aux->autonomia);

            printf("Digite o novo custo: ");
            scanf("%f", &aux->custo);

            printf("Digite o novo código geográfico: ");
            scanf("%s", aux->geoCodigo);

            printf("Meio atualizado com sucesso.\n");
            return;
        }
        aux = aux->seguinte;
    }
    printf("Meio não encontrado.\n");
}


void listarMeiosPorGeocodigo(Meio *inicio, char *geoCodigo)
{
    while (inicio != NULL)
    {
        if (strcmp(inicio->geoCodigo, geoCodigo) == 0)
        {
            printf("%d %s %f %f %f %s %d\n", inicio->codigo, inicio->tipo,
                   inicio->bateria, inicio->autonomia, inicio->custo, inicio->geoCodigo, inicio->disponivel);
        }
        inicio = inicio->seguinte;
    }
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo.h"
#include "meio.h"

// Criar um novo vértice
// Devolve 1 em caso de sucesso ou 0 caso contrário
int criarVertice(Grafo **g, char novoId[])
{
    Grafo *novo = malloc(sizeof(struct Grafo));
    if (novo != NULL)
    {
        strcpy(novo->vertice, novoId);
        novo->meios = NULL;
        novo->adjacentes = NULL;
        novo->seguinte = *g;
        *g = novo;

        return 1;
    }
    else
    {
        return 0;
    }
}

// Devolve 1 se o vertice existe no grafo ou 0 caso contrário
int existeVertice(Grafo *g, char vertice[])
{
    while (g != NULL)
    {
        if (strcmp(g->vertice, vertice) == 0)
            return (1);
        else
            g = g->seguinte;
    }
    return (0);
}

// Criar uma nova aresta
// Devolve 1 em caso de sucesso ou 0 caso contrário
int criarAresta(Grafo **g, char vOrigem[], char vDestino[], float peso)
{
    if (existeVertice(*g, vOrigem) && existeVertice(*g, vDestino))
    {
        // Encontra o vértice correto no grafo
        Grafo *verticeAtual = (*g);
        while (strcmp(verticeAtual->vertice, vOrigem) != 0)
            verticeAtual = verticeAtual->seguinte;

        Adjacente *novo = malloc(sizeof(struct Adjacente));
        if (novo != NULL)
        {
            strcpy(novo->vertice, vDestino);
            novo->peso = peso;
            novo->seguinte = verticeAtual->adjacentes;
            verticeAtual->adjacentes = novo;

            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

// Listar os vértices adjacentes
void listarAdjacentes(Grafo *g, char vertice[])
{
    if (existeVertice(g, vertice))
    {
        while (strcmp(g->vertice, vertice) != 0)
            g = g->seguinte;

        if (g == NULL)
        {
            printf("O vertice nao foi encontrado\n");
            return;
        }

        Adjacente *aux = g->adjacentes;
        while (aux != NULL)
        {
            printf("\nAdjacente:%s Peso:%.2f\n", aux->vertice, aux->peso);
            aux = aux->seguinte;
        }

        aux = g->adjacentes;
        while (aux != NULL)
        {
            Adjacente *next = aux->seguinte;
            free(aux);
            aux = next;
        }
    }
    else
    {
        printf("O vertice nao foi encontrado\n");
        return;
    }
}

// Inserir meio de transporte na localização com geocódigo passado por parâmetro
// Devolve 1 em caso de sucesso ou 0 caso contrário
int inserirMeioNoGrafo(Grafo **g, char geocodigo[], int codigoMeio)
{
    Grafo *verticeAtual = *g;

    while ((verticeAtual != NULL) && (strcmp(verticeAtual->vertice, geocodigo) != 0))
        verticeAtual = verticeAtual->seguinte;

    if (verticeAtual == NULL)
        return 0;
    else
    {
        Meios *novo = malloc(sizeof(struct registo3));
        if (novo != NULL)
        {
            novo->codigo = codigoMeio;
            novo->seguinte = verticeAtual->meios;
            verticeAtual->meios = novo;

            return 1;
        }
        else
        {
            return 0;
        }
    }
}

// Listar os códigos dos meios de transporte presente numa determinada localização passada por parâmetro
void listarMeiosNoGrafo(Grafo *g, char geocodigo[])
{
    printf("Meios de transporte na localizacao %s: \n", geocodigo);
    printf("%s", g->meios->codigo);
    while ((g != NULL) && (strcmp(g->vertice, geocodigo) != 0))
        g = g->seguinte;
    if (g != NULL)
    {
        Meios *aux = g->meios;
        if (aux == NULL)
            printf("sem meios de transporte\n");
        else
            while (aux != NULL)
            {
                printf("Codigo meio: %d\n", aux->codigo);
                aux = aux->seguinte;
            }
    }
    else
        printf("geocodigo inexistente\n");
}

void guardarGrafo(Grafo *grafo)
{
    FILE *fp;
    fp = fopen("grafo.txt", "w");
    if (fp == NULL)
    {
        printf("O ficheiro grafo.txt não pode ser aberto!\n");
        return;
    }

    Grafo *aux = grafo;
    printf("Vertice|Adjacentes\n");
    while (aux != NULL)
    {
        fprintf(fp, "%s", aux->vertice);

        Meios *meio = aux->meios;
        while (meio != NULL)
        {
            fprintf(fp, ";%d", meio->codigo);
            meio = meio->seguinte;
        }

        Adjacente *adj = aux->adjacentes;
        while (adj != NULL)
        {
            fprintf(fp, "|%s;%f", adj->vertice, adj->peso);
            adj = adj->seguinte;
        }

        fprintf(fp, "\n");
        aux = aux->seguinte;
    }

    fclose(fp);
    printf("Grafo guardado no ficheiro com sucesso!\n");
}
Grafo *lerGrafo()
{
    FILE *fp = fopen("grafo.txt", "r");
    Grafo *aux = NULL;
    char line[100];

    if (fp != NULL)
    {
        while (fgets(line, sizeof(line), fp) != NULL)
        {
            line[strcspn(line, "\n")] = '\0'; // Remove newline character

            char vertice[TAM];
            char meios[TAM];
            char adjacentes[TAM];
            sscanf(line, "%[^;];%[^|]|%[^\n]", vertice, meios, adjacentes);

            Grafo *novo = (Grafo *)malloc(sizeof(Grafo));
            strcpy(novo->vertice, vertice);
            novo->adjacentes = NULL;
            novo->meios = NULL;
            novo->seguinte = NULL;

            Meios *meio = NULL;

            char *token = strtok(meios, ";");
            while (token != NULL)
            {
                int codigo;
                sscanf(token, "%d", &codigo);

                Meios *novoMeio = (Meios *)malloc(sizeof(Meios));
                novoMeio->codigo = codigo;
                novoMeio->seguinte = NULL;

                if (meio == NULL)
                {
                    novo->meios = novoMeio;
                    meio = novoMeio;
                }
                else
                {
                    meio->seguinte = novoMeio;
                    meio = meio->seguinte;
                }

                token = strtok(NULL, ";");
            }

            Adjacente *adjacente = NULL;
            token = strtok(adjacentes, "|");
            while (token != NULL)
            {
                char adj[TAM];
                double peso;
                sscanf(token, "%[^;];%lf", adj, &peso);

                Adjacente *novoAdjacente = (Adjacente *)malloc(sizeof(Adjacente));
                strcpy(novoAdjacente->vertice, adj);
                novoAdjacente->peso = peso;
                novoAdjacente->seguinte = NULL;

                if (adjacente == NULL)
                {
                    novo->adjacentes = novoAdjacente;
                    adjacente = novoAdjacente;
                }
                else
                {
                    adjacente->seguinte = novoAdjacente;
                    adjacente = adjacente->seguinte;
                }

                token = strtok(NULL, "|");
            }

            if (aux == NULL)
            {
                aux = novo;
            }
            else
            {
                Grafo *temp = aux;
                while (temp->seguinte != NULL)
                {
                    temp = temp->seguinte;
                }
                temp->seguinte = novo;
            }
        }

        fclose(fp);
        return aux;
    }
    else
    {
        printf("Erro ao abrir o ficheiro\n");
    }

    return NULL;
}

// Listar os meios de transporte que se encontram a uma distância inferior a proximidade do utilizador

void listarMeiosPertoDoUser(Grafo *g, char geoCodigo[], int proximidade, char tipo[])
{
    if (proximidade < 0)
    {
        printf("A proximidade tem de ser um valor positivo\n");
        return;
    }
    // passar o vertice para visitado
    while ((g != NULL) && (strcmp(g->vertice, geoCodigo) != 0))
    {
        g->visitado = 1;
        g = g->seguinte;
    }
}

void listarGrafo(Grafo *grafo)
{
    Grafo *verticeAtual = grafo;
    while (verticeAtual != NULL)
    {
        printf("\nVertice: %s\n", verticeAtual->vertice);

        Adjacente *adjacente = verticeAtual->adjacentes;
        while (adjacente != NULL)
        {
            printf("Adjacentes:%s;Peso:%.6f  ", adjacente->vertice, adjacente->peso);
            adjacente = adjacente->seguinte;
        }
        printf("\n");

        Meios *meio = verticeAtual->meios;
        while (meio != NULL)
        {
            printf("Meios: ");
            printf("%d  ", meio->codigo);
            meio = meio->seguinte;
        }
        printf("\n");

        verticeAtual = verticeAtual->seguinte;
    }
}

void printMeiosDentroRaio(Grafo *grafo, Meio *inicio, char *vertice, float raio, char *tipo)
{
    // Start the traversal from the initial vertex
    traverseGraph(grafo, inicio, vertice, raio, tipo, 0.0);
}

void traverseGraph(Grafo *grafo, Meio *inicio, char *vertice, float raio, char *tipo, float distancia)
{
    // Find the current vertex in the graph
    Grafo *atual = grafo;
    while (atual != NULL && strcmp(atual->vertice, vertice) != 0)
    {
        atual = atual->seguinte;
    }

    if (atual == NULL)
    {
        printf("Vertice %s nao encontrado no grafo.\n", vertice);
        return;
    }

    // Traverse the linked list of associated meios
    Meios *meio = atual->meios;
    if (meio == NULL)
    {
        // No meios associated with the current vertex
        printf("Vertice %s nao possui meios associados.\n", vertice);
        return;
    }

    while (meio != NULL)
    {
        Meio *meioCorrespondente = getMeioPorCodigo(inicio, meio->codigo);
        if (meioCorrespondente != NULL && strcmp(meioCorrespondente->tipo, tipo) == 0)
        {
            // Print the information of the corresponding meio
            printf("Codigo do Meio: %d\n", meioCorrespondente->codigo);
            printf("Tipo: %s\n", meioCorrespondente->tipo);
            printf("Bateria: %.2f\n", meioCorrespondente->bateria);
            printf("Autonomia: %.2f\n", meioCorrespondente->autonomia);
            printf("Custo: %.2f\n", meioCorrespondente->custo);
            printf("Geo Codigo: %s\n", meioCorrespondente->geoCodigo);
            printf("Disponivel: %d\n", meioCorrespondente->disponivel);
            printf("Distancia: %.2f\n\n", distancia);
        }
        meio = meio->seguinte;
    }

    // Traverse the linked list of adjacencies
    Adjacente *adjacente = atual->adjacentes;
    while (adjacente != NULL)
    {
        // Calculate the distance between the vertices
        float novaDistancia = distancia + adjacente->peso;

        // Check if the distance is within the radius
        if (novaDistancia <= raio)
        {
            // Recursively traverse the adjacent vertex
            traverseGraph(grafo, inicio, adjacente->vertice, raio, tipo, novaDistancia);
        }
        adjacente = adjacente->seguinte;
    }
}

Meio *getMeioPorCodigo(Meio *inicio, int codigo)
{
    Meio *atual = inicio;

    while (atual != NULL)
    {
        if (atual->codigo == codigo)
        {
            return atual;
        }
        atual = atual->seguinte;
    }

    // Meio com o código fornecido não foi encontrado
    return NULL;
}

/*------------------/*------------------/*------------------/*------------------/*------------------*/

Grafo *encontrarVertice(Grafo *grafo, char *vertice)
{
    Grafo *temp = grafo;
    while (temp != NULL)
    {
        if (strcmp(temp->vertice, vertice) == 0)
        {
            return temp;
        }
        temp = temp->seguinte;
    }
    return NULL;
}

void desmarcarVisitados(Grafo *grafo)
{
    Grafo *temp = grafo;
    while (temp != NULL)
    {
        temp->visitado = 0;
        temp = temp->seguinte;
    }
}
Meio* percursoCamiao(Grafo* grafo, Meio* meios, int capacidadeCamiao) {
    int volta = 1; // Inicializar o contador de voltas
    int contaRecolhidos = 0; // Inicializar a contagem de meios recolhidos
    Grafo* verticeAtual = grafo; // Começar pelo primeiro vértice no grafo
    Grafo* primeiroVertice = grafo; // Guardar o primeiro vértice no grafo

    while (verticeAtual != NULL) { // Loop até que o vértice atual seja NULL (final do percurso)

        if (!verticeAtual->visitado) { // Verificar se o vertice atual não foi visitado
            Meio* meioAtual = meios; // Comecar pelo primeiro meio na lista

            while (meioAtual != NULL && contaRecolhidos < capacidadeCamiao) { // Loop até que não haja mais meios ou a capacidade do caminhão seja atingida
                if (meioAtual->disponivel == 1) { // Verificar se o meio está disponível
                    if (meioAtual->bateria < 50 &&
                        strcmp(meioAtual->geoCodigo, verticeAtual->vertice) == 0) { // Verificar se a bateria do meio é inferior a 50 e se o seu geoCodigo corresponde ao vértice atual

                        contaRecolhidos++; // Incrementar a contagem de meios recolhidos

                        printf("Volta %d:\n", volta);
                        printf("Veiculo %d coletado.\n", meioAtual->codigo);
                        printf("Bateria atual: %.2f\n", meioAtual->bateria);

                        strcpy(meioAtual->geoCodigo, primeiroVertice->vertice); // Definir o geoCodigo do meio como o geoCodigo do primeiro vértice
                        meioAtual->bateria = 100; // Recarregar a bateria do meio
                    }
                }

                meioAtual = meioAtual->seguinte; // Avançar para o próximo meio
            }

            verticeAtual->visitado = true; // Marcar o vértice atual como visitado
        }

        Grafo* next_vertex = NULL; // Inicializar um ponteiro para o próximo vértice como NULL
        Adjacente* adjacentes = verticeAtual->adjacentes; // Obter a lista de vértices adjacentes ao vértice atual
        int distanciaMaisCurta = INT_MAX; // Inicializar a menor distância como um valor grande

        while (adjacentes != NULL) { // Loop pelos vértices adjacentes
            Grafo* verticeAdjacente = encontrarVertice(grafo, adjacentes->vertice); // Encontrar o vértice adjacente no grafo

            if (!verticeAdjacente->visitado && adjacentes->peso < distanciaMaisCurta) { // Verificar se o vértice adjacente não foi visitado e sua distância é menor
                distanciaMaisCurta = adjacentes->peso; // Atualizar a menor distância
                next_vertex = verticeAdjacente; // Definir o próximo vértice como o vértice adjacente com a menor distância
            }

            adjacentes = adjacentes->seguinte; // Avançar para o próximo vértice adjacente
        }

        if (contaRecolhidos == capacidadeCamiao) { // Verificar se a capacidade do caminhão foi atingida
            volta++; // Incrementar o contador de voltas
            contaRecolhidos = 0; // Resetar a contagem de meios coletados
            verticeAtual = primeiroVertice; // Definir o vértice atual como o primeiro vértice
            desmarcarVisitados(grafo); // Marcar todos os vértices como não visitados
        } else {
            verticeAtual = next_vertex; // Definir o próximo vértice como o vértice atual para a próxima iteração
        }
    }

    desmarcarVisitados(grafo); // Marcar todos os vértices como não visitados

    return meios; // Retornar a lista de meios
}
#pragma once
// Representar um grafo orientado e pesado através da definição de
// uma lista ligada de listas ligadas

#define TAM 100

typedef struct registo3
{
  int codigo;

  struct registo3 *seguinte;
} Meios;

// Representação de um grafo orientado e pesado
typedef struct Adjacente
{
  char vertice[TAM]; // geocódigo what3words
  float peso;
  struct Adjacente *seguinte;
} Adjacente;

typedef struct Grafo
{
  char vertice[TAM]; // geocódigo what3words
  int visitado;
  Adjacente *adjacentes;
  Meios *meios; // Lista ligada com os códigos dos meios de transporte existente
               // neste geocódigo
  struct Grafo *seguinte;
} Grafo;

// Protótipos

// Criar um novo vértice
// Devolve 1 em caso de sucesso ou 0 caso contrário
int criarVertice(Grafo **g, char novoId[]);
// Criar uma nova aresta
// Devolve 1 em caso de sucesso ou 0 caso contrário
int criarAresta(Grafo **g, char vOrigem[], char vDestino[], float peso);
int existeVertice(Grafo *g, char vertice[]);
void listarAdjacentes(Grafo *g, char vertice[]);
// Inserir meio de transporte na localização com geocódigo passado por parâmetro
int inserirMeioNoGrafo(Grafo **g, char geocodigo[], int codigoMeio);
// Listar os códigos dos meios de transporte presente numa determinada localização passada por parâmetro
void listarMeiosNoGrafo(Grafo *g, char geocodigo[]);

void listarVeiculosProximos(Grafo* vertice, float proximidade, char tipo[]);

void guardarGrafo(Grafo *g);

Grafo *lerGrafo();

Grafo inserirGrafo(Grafo *g, char vertice[], char adjacente[], int peso);

void printMeiosDentroRaio(Grafo* grafo, Meio* inicio, char* vertice, float raio, char* tipo);
Meio* getMeioPorCodigo(Meio* inicio, int codigo) ;
void traverseGraph(Grafo* grafo, Meio* inicio, char* vertice, float raio, char* tipo, float distancia);

Meio* percursoCamiao(Grafo* grafo, Meio* lista_meios, int capacidadeCamiao);
void desmarcarVisitados(Grafo* grafo);
Grafo* encontrarVertice(Grafo* grafo, char* vertice);
Meio* encontrarMeio(Meio* lista_meios, int codigo);
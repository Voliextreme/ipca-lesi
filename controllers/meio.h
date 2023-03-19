#pragma once

#include <stdio.h>
#include <stdbool.h>

typedef struct registo
{int codigo; // código do meio de mobilidade elétrica
 char tipo[50];
 float bateria;
 float autonomia;
 float custo;
 char geoCodigo[50];
 bool disponivel;
 struct registo* seguinte;
} Meio;


Meio* inserirMeio(Meio* inicio, int codigo, char tipo[], float bateria, float autonomia, float custo, char geoCodigo[], bool disponivel); // Inserção de um novo registo
void listarMeios(Meio* inicio); // listar na consola o conteúdo da lista ligada
Meio* removerMeio(Meio* inicio, int cod); // Remover um meio a partir do seu código
int existeMeio(Meio* inicio, int codigo); // Determinar existência do 'codigo' na lista ligada 'inicio'
 
int guardarMeiosBin(Meio* inicio);

void listMeiosPorAutonomiaDecrescente(Meio** inicio);
void swapMeio(Meio* a, Meio* b);

int guardarMeios(Meio* inicio);
Meio* lerMeios();

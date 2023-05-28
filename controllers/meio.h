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
 int disponivel;
 struct registo* seguinte;
} Meio;


Meio* inserirMeio(Meio* inicio, int codigo, char tipo[], float bateria, float autonomia, float custo, char geoCodigo[], int disponivel); // Inserção de um novo registo
Meio* removerMeio(Meio* inicio, int cod); // Remover um meio a partir do seu código
int existeMeio(Meio* inicio, int codigo); // Determinar existência do 'codigo' na lista ligada 'inicio'

void alterarMeio(Meio** inicio, int codigo);

int guardarMeiosBin(Meio* inicio);

void listarMeios(Meio* inicio); // listar na consola o conteúdo da lista ligada
void listarMeiosDisponiveis(Meio* inicio); // listar na consola o conteúdo da lista ligada
void listarMeiosOrganizados(Meio** inicio);
void listMeiosPorAutonomiaDecrescente(Meio** inicio);
void listarMeiosPorGeocodigo(Meio *inicio, char *geoCodigo);

int guardarMeios(Meio* inicio);
Meio* lerMeios();

#pragma once
#include <stdio.h>

#include "conta.h"
#include "meio.h"

typedef struct aluga
{
 int idAluguer; // código do meio de mobilidade elétrica
 int idMeio;
 int idCliente;
 struct aluga* seguinte;
} Aluguer;


Aluguer* alugarMeio(Aluguer* inicio ,Meio* inicioMeio, int codigoMeio, int idCliente, User* inicioUser);
Aluguer* alugarMeioFicheiro(Aluguer* inicio ,int idAluguer, int codigoMeio, int idCliente);
int devolverMeio(Meio** inicio, Aluguer* inicioAluguer, int idAluguer);
Aluguer* lerAlugueres();

int userTemAluguer(Aluguer* inicio, int idCliente);
int existeAluguer(Aluguer* inicio, int idAluguer);

void setMeioAlugado(Meio **inicio, int cod);

int disponibilidadeMeio(Meio* inicio, int codigoMeio);
void listarAlugueres(Aluguer* inicio);
int listarAlugueresUser(Aluguer* inicio, int idCliente);
int guardarAlugueres(Aluguer* inicio);


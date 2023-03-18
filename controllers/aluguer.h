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
Aluguer* devolverMeio(Meio* inicio, int codigoMeio, int idCliente);
Aluguer* lerAlugueres();

int existeAluguer(Aluguer* inicio, int idAluguer);

int disponibilidadeMeio(Meio* inicio, int codigoMeio);
void listarAlugueres(Aluguer* inicio);
int guardarAlugueres(Aluguer* inicio);


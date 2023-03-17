#pragma once

#include <stdio.h>

typedef struct user
{
 int id; // código do cliente
 char nome[50];
 char nif[10];
 char morada[100];
 char email[50];
 int role;
 float saldo;
 struct user* seguinte;
}User;


User* createUser(User* inicio, int id, char nome[], char nif[], char morada[], char email[], int role, float saldo); // Inserção de um novo registo
void listUsers(User* inicio); // listar na consola o conteúdo da lista ligada
int findUser(User* inicio, int id); // Determinar existência do 'codigo' na lista ligada 'inicio'
User* removeUser(User* inicio, int id); // Remover um User a partir do seu código

int saveUsers(User* inicio);
User* readUsers();

User* loginUser(User* inicio, char email[]);
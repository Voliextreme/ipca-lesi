#include <stdlib.h>
#include <string.h>

#include "conta.h"

int saveUsers(User *inicio)
{
  FILE *fp;
  fp = fopen("contas.txt", "w");
  if (fp != NULL)
  {
    User *aux = inicio;
    while (aux != NULL)
    {
      fprintf(fp, "%d;%s;%s;%s;%s;%d;%.2f\n", aux->id, aux->nome,
              aux->nif, aux->morada, aux->email, aux->role, aux->saldo);
      aux = aux->seguinte;
    }
    fclose(fp);
    return (1);
  }
  else
    return (0);
}

User *readUsers()
{
  FILE *fp;
  int id, role;
  float saldo;
  char nome[50], nif[10], morada[100], email[50];
  User *aux = NULL;
  fp = fopen("contas.txt", "r");
  if (fp != NULL)
  {
    while (!feof(fp))
    {
      fscanf(fp, "%d;%[^;];%[^;];%[^;];%[^;];%d;%f;\n", &id, nome, nif, morada, email, &role, &saldo);
      aux = createUser(aux, id, nome, nif, morada, email, role, saldo);
    }
    fclose(fp);
  }
  return (aux);
}

//
int contarContas(User* inicio) {
    int contador = 0;
    User* atual = inicio;
    while (atual != NULL) {
        contador++;
        atual = atual->seguinte;
    }
    return contador;
}

// Inserção de um novo registo
User *createUser(User *inicio, int id, char nome[], char nif[], char morada[], char email[],int role, float saldo)
{
  if (!findUser(inicio, id))
  {
    User *novo = malloc(sizeof(struct user));
    if (novo != NULL)
    {
      novo->id = id;
      strcpy(novo->nome, nome);
      strcpy(novo->nif, nif);
      strcpy(novo->morada, morada);
      strcpy(novo->email, email);
      novo->role = 2;
      novo->saldo = saldo;
      novo->seguinte = inicio;
      return (novo);
    }
  }
  
  return (inicio);
}

// listar na consola o conteúdo da lista ligada
void listUsers(User *inicio)
{
  while (inicio != NULL)
  {
    printf("%d %s %s %s %s %d %.2f\n", inicio->id, inicio->nome,
           inicio->nif, inicio->morada, inicio->email, inicio->role, inicio->saldo);
    inicio = inicio->seguinte;
  }
}

// Determinar existência do 'codigo' na lista ligada 'inicio'
// devolve 1 se existir ou 0 caso contrário
int findUser(User *inicio, int id)
{
  while (inicio != NULL)
  {
    if (inicio->id == id)
      return (1);
    inicio = inicio->seguinte;
  }
  return (0);
}


// Remover um Cliente a partir do seu código{
User *removeUser(User *inicio, int id)
{
  User *anterior = inicio, *atual = inicio, *aux;

  if (atual == NULL)
    return (NULL);
  else if (atual->id == id) // remoção do 1º registo
  {
    aux = atual->seguinte;
    free(atual);
    return (aux);
  }
  else
  {
    while ((atual != NULL) && (atual->id != id))
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

User* loginUser(User *inicio, char email[])
{
  while (inicio != NULL)
  {
    printf("email : %s", inicio->email);
    if (strcmp(inicio->email, email) == 0)
     {
      return (inicio);
     }
    inicio = inicio->seguinte;
  }
    return 0;
}


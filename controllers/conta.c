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
      fprintf(fp, "%d;%s;%s;%s;%s;%d;%.2f;%s\n", aux->id, aux->nome,
              aux->nif, aux->morada, aux->email, aux->role, aux->saldo, aux->geoCodigo);
      aux = aux->seguinte;
    }
    fclose(fp);
    return (1);
  }
  else
    return (0);
}
int saveUsersBin(User *inicio)
{
  FILE *fp;
  fp = fopen("./FicheirosBin/contas.bin", "wb");
  if (fp != NULL)
  {
    User *aux = inicio;
    while (aux != NULL)
    {
      fprintf(fp, "%d;%s;%s;%s;%s;%d;%.2f;%s\n", aux->id, aux->nome,
              aux->nif, aux->morada, aux->email, aux->role, aux->saldo, aux->geoCodigo);
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
  char nome[50], nif[10], morada[100], email[50], geoCodigo[100];
  User *aux = NULL;
  fp = fopen("contas.txt", "r");
  if (fp != NULL)
  {
    while (!feof(fp))
    {
      fscanf(fp, "%d;%[^;];%[^;];%[^;];%[^;];%d;%f;%[^;];\n", &id, nome, nif, morada, email, &role, &saldo);
      aux = createUser(aux, id, nome, nif, morada, email, role, saldo, geoCodigo);
    }
    fclose(fp);
  }else{
        printf("Erro ao abrir o ficheiro");
  }
  return (aux);
}


// Inserção de um novo registo
User *createUser(User *inicio, int id, char nome[], char nif[], char morada[], char email[],int role, float saldo, char geoCodigo[])
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
      novo->role = role;
      novo->saldo = saldo;
      strcpy(novo->geoCodigo, geoCodigo);
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
    printf("%d %s %s %s %s %d %.2f %s\n", inicio->id, inicio->nome,
           inicio->nif, inicio->morada, inicio->email, inicio->role, inicio->saldo, inicio->geoCodigo);
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
    if (strcmp(inicio->email, email) == 0)
     {
      return (inicio);
     }
    inicio = inicio->seguinte;
  }
    return 0;
}



void alterarUser(User **inicio, int id)
{
    User *aux = *inicio;
    while (aux != NULL)
    {
        if (aux->id == id)
        {
            // Prompt user for new values
            printf("Digite o nome: ");
            scanf("%s", aux->nome);

            printf("Digite o nif: ");
            scanf("%s", aux->nif);

            printf("Digite a morada: ");
            scanf("%s", aux->morada);

            printf("Digite o role: [1-Gestor, 2-User]]");
            scanf("%d", &aux->role);

            printf("User atualizado com sucesso.\n");
            return;
        }
        aux = aux->seguinte;
    }
    printf("User não encontrado.\n");
}


void alterarUserCliente(User **inicio, int id)
{
    User *aux = *inicio;
    while (aux != NULL)
    {
        if (aux->id == id)
        {
            // Prompt user for new values
            printf("Digite o nome: ");
            scanf("%s", aux->nome);

            printf("Digite o nif: ");
            scanf("%s", aux->nif);

            printf("Digite a morada: ");
            scanf("%s", aux->morada);

            printf("Digite o email: ");
            scanf("%s", aux->email);

            printf("Digite o saldo: ");
            scanf("%f", &aux->saldo);

            printf("User atualizado com sucesso.\n");
            return;
        }
        aux = aux->seguinte;
    }
    printf("User não encontrado.\n");
}

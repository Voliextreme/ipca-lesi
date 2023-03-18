#include <stdio.h>

#include "./controllers/meio.h"
#include "./controllers/conta.h"
#include "./controllers/aluguer.h"
#include "./controllers/meio.c"
#include "./controllers/conta.c"
#include "./controllers/aluguer.c"

void menuPrincipal()
{
	printf("\n --- Menu ---\n");
	printf("1 Gestores\n");
	printf("2 Meios\n");
	printf("0 Sair\n");
	printf("Opcao:\n");
}

void menuMeios()
{
	printf("\n --- Menu Meios --- \n");
	printf("1 Inserir Meio\n");
	printf("2 Listar Meios\n");
	printf("3 Remover Meio\n");
	printf("4 Ler Meios\n");
	printf("0 Sair\n");
	printf("Opcao:\n");
}

void menuGestores()
{
	printf("\n --- Menu Gestores --- \n");
	printf("1 Inserir Gestor\n");
	printf("2 Listar Users\n");
	printf("3 Remover User\n");
	printf("4 Ler Users\n");
	printf("0 Sair\n");
	printf("Opcao:\n");
}

void menuClientes()
{
	printf("\n --- Menu Cliente --- \n");
	printf("1 Alugar Meio\n");
	printf("2 Devolver Meio\n");
	printf("3 Alterar Informacoes\n");
	printf("0 Sair\n");
	printf("Opcao:\n");
}

void menuLogin()
{
	printf("\n --- Login --- \n");
	printf("1 Iniciar Sessao\n");
	printf("2 Registar \n");
	printf("0 Sair\n");
	printf("Opcao:\n");
}

int main()
{
	Meio *meios = NULL;		   // Lista ligada vazia
	User *users = NULL;		   // Lista ligada vazia
	Aluguer *alugueres = NULL; // Lista ligada vazia
	User *userAtual = NULL;

	int op = 0, opP = 0, opG = 0, opC = 0, opM = 0, id, login = 0, role, codigo;
	float bateria, autonomia, saldo, custo;
	char tipo[50], nome[50], morada[100], nif[10], email[50], geoCodigo[50];
	bool disponivel;

	do
	{
		menuLogin();
		scanf("%d", &login);
		switch (login)
		{
		case 1:
			users = readUsers();
			printf("Email:");
			scanf("%s", email);
			userAtual = loginUser(users, email);
			if (userAtual->role == 0)
			{
				printf("Email nao encontrado");
				break;
			}
			if (userAtual->role == 1)
			{
				// Menu Gestor
				do
				{
					menuPrincipal();
					scanf("%d", &opP);
					switch (opP)
					{
					case 1:
						do
						{
							menuGestores();
							scanf("%d", &opG);
							switch (opG)
							{
							case 1:
								printf("Id:\n");
								scanf("%d", &id);
								scanf("%*c");
								printf("Nome:\n");
								scanf("%[^\n]s", nome);
								getchar();
								printf("NIF:\n");
								scanf("%[^\n]s", nif);
								getchar();
								printf("Morada:\n");
								scanf("%[^\n]s", morada);
								getchar();
								printf("Email:\n");
								scanf("%[^\n]s", email);
								getchar();
								printf("Saldo:\n");
								scanf("%f", &saldo);
								role = 1;
								users = createUser(users, id, nome, nif, morada, email, role, saldo);
								saveUsers(users);
								break;
							case 2:
								listUsers(users);
								break;
							case 3:
								printf("Id do user a remover?\n");
								scanf("%d", &id);
								users = removeUser(users, id);
								saveUsers(users);
								break;
							case 4:
								users = readUsers();
								break;
							}
						} while (opG != 0);
						break;
					case 2:
						do
						{
							menuMeios();
							scanf("%d", &opM);
							switch (opM)
							{
							case 1:
								printf("Codigo:\n");
								scanf("%d", &codigo);
								scanf("%*c");
								printf("Tipo:\n");
								scanf("%[^\n]s", tipo);
								getchar();
								printf("Bateria:\n");
								scanf("%f", &bateria);
								printf("Autonomia:\n");
								scanf("%f", &autonomia);
								printf("Custo:\n");
								scanf("%f", &custo);
								scanf("%*c");
								printf("GeoCodigo:\n");
								scanf("%[^\n]s", geoCodigo);
								getchar();
								disponivel = true;
								meios = inserirMeio(meios, codigo, tipo, bateria, autonomia, custo, geoCodigo, disponivel);
								guardarMeios(meios);
								break;
							case 2:
								listarMeios(meios);
								break;
							case 3:
								printf("Id do meio a remover?\n");
								scanf("%d", &id);
								meios = removerMeio(meios, id);
								guardarMeios(meios);
								break;
							case 4:
								meios = lerMeios();
								break;
							default:
								break;
							}
						} while (opM != 0);
						break;
					default:
						break;
					}

				} while (op != 0);
				break;
			}
			if (userAtual->role == 2)
			{
				// Menu Cliente
				meios = lerMeios();
				do
				{
					alugueres = lerAlugueres();
					menuClientes();
					scanf("%d", &opC);
					switch (opC)
					{
					case 1:
						listarMeios(meios);
						printf("Codigo do meio de mobilidade a alugar?\n");
						scanf("%d", &codigo);
						alugueres = alugarMeio(alugueres, meios, codigo, userAtual->id, users);
						guardarAlugueres(alugueres);
						break;
					case 2:
						listarAlugueres(alugueres);
						printf("Codigo do meio de mobilidade a devolver?\n");
						scanf("%d", &codigo);
						devolverMeio(meios, codigo, userAtual->id);
						break;
					case 3:
						printf("Id:\n");
						scanf("%d", &id);
						scanf("%*c");
						printf("Nome:\n");
						scanf("%s", nome);
						getchar();
						printf("NIF:\n");
						scanf("%s", nif);
						getchar();
						printf("Morada:\n");
						scanf("%s", morada);
						getchar();
						printf("Email:\n");
						scanf("%s", email);
						getchar();
						printf("Saldo:\n");
						scanf("%f", &saldo);
						role = 2;
						// users = alterarUser(users, id, nome, nif, morada, email, role, saldo);
						saveUsers(users);
						break;
					}
				} while (opC != 0);
			}
			break;
		case 2:
			users = readUsers();
			printf("Registar\n");
			printf("Id:\n");
			scanf("%d", &id);
			scanf("%*c");
			printf("Nome:\n");
			scanf("%[^\n]s", nome);
			getchar();
			printf("NIF:\n");
			scanf("%[^\n]s", nif);
			getchar();
			printf("Morada:\n");
			scanf("%[^\n]s", morada);
			getchar();
			printf("Email:\n");
			scanf("%[^\n]s", email);
			getchar();
			printf("Saldo:\n");
			scanf("%f", &saldo);
			role = 2;
			users = createUser(users, id, nome, nif, morada, email, role, saldo);
			listUsers(users);
			saveUsers(users);
			break;
		default:
			break;
		}

	} while (login != 0);

	return (0);
}
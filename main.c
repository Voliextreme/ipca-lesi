#include <stdio.h>

#include "./controllers/meio.h"
#include "./controllers/conta.h"
#include "./controllers/aluguer.h"
#include "./controllers/meio.c"
#include "./controllers/conta.c"
#include "./controllers/aluguer.c"

int menuPrincipal()
{
	int op;
	printf(" --- Menu ---\n");
	printf("1 Meios\n");
	printf("2 Gestores\n");
	printf("3 Clientes\n");
	printf("4 Aluguer\n");
	printf("0 Sair\n");
	printf("Opcao:\n");
	scanf("%d", &op);
	return (op);
}

int menuMeios()
{
	int op;
	printf(" --- Menu Meios --- \n");
	printf("1 Inserir Meio\n");
	printf("2 Listar Meios\n");
	printf("3 Remover Meio\n");
	printf("4 Ler Meios\n");
	printf("0 Sair\n");
	printf("Opcao:\n");
	scanf("%d", &op);
	return (op);
}

int menuGestores()
{
	int op;
	printf(" --- Menu Gestores --- \n");
	printf("1 Inserir Gestor\n");
	printf("2 Listar Users\n");
	printf("3 Remover User\n");
	printf("4 Ler Users\n");
	printf("0 Sair\n");
	printf("Opcao:\n");
	scanf("%d", &op);
	return (op);
}

int menuClientes()
{
	int op;
	printf("\n --- Menu Cliente --- \n");
	printf("1 Listar Meios\n");
	printf("2 Alugar Meio\n");
	printf("3 Devolver Meio\n");
	printf("4 Alterar Informaçoes\n");
	printf("0 Sair\n");
	printf("Opcao:\n");
	scanf("%d", &op);
	return (op);
}

int menuLogin()
{
	int login;
	printf("Login\n");
	printf("1 Iniciar Sessao\n");
	printf("2 Registar \n");
	printf("0 Sair\n");
	printf("Opcao:\n");
	scanf("%d", &login);
	return (login);
}

int main()
{
	Meio *meios = NULL;		 // Lista ligada vazia
	User *users = NULL;		 // Lista ligada vazia
	Aluguer *alugueres = NULL;		 // Lista ligada vazia
	User *userAtual = NULL;

	int op, id, login, role, codigo;
	float bateria, autonomia, saldo, custo;
	char tipo[50], nome[50], morada[100], nif[10], email[50], geoCodigo[20];

	do
	{
		login = menuLogin();
		switch (login)
		{
		case 1:
			users = readUsers();
			printf("Email:");
			scanf("%s",email);
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
					op = menuPrincipal();
					switch (op)
					{
					case 1:
						do
						{
							op = menuGestores();
							switch (op)
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
						} while (op != 0);
						break;
					case 2:
						do
						{
							op = menuMeios();
							switch (op)
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
								printf("GeoCodigo:\n");
								scanf("%[^\n]s", geoCodigo);
								getchar();
								meios = inserirMeio(meios, codigo, tipo, bateria, autonomia, custo, geoCodigo, false);
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
							}
						} while (op != 0);
					case 3:
						break;
					}
				} while (op != 0);
			}
			if (userAtual->role == 2)
			{
				// Menu Cliente
				do
				{
					op = menuClientes();
					switch (op)
					{
					case 1:
						listarMeios(meios);
						break;
					case 2:
						printf("Codigo do meio de mobilidade a alugar?\n");
						scanf("%d", &codigo);
						alugueres = alugarMeio(alugueres, meios, codigo, userAtual->id, users);
						break;
					case 3:
						printf("Codigo do meio de mobilidade a devolver?\n");
						scanf("%d", &codigo);
						alugueres = devolverMeio(meios, codigo, userAtual->id);
						break;
					case 4:
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
				} while (op != 0);
			}
		case 2:
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

	/*
	do
	{
		op = menuPrincipal();
		switch (op)
		{
		case 1:
			// ------------------- MEIOS ------------------
			do
			{
				opM = menuMeios();
				switch (opM)
				{
				case 1:
					printf("Codigo?\n");
					scanf("%d", &cod);
					scanf("%*c");
					printf("Tipo\n");
					scanf("%[^\n]s", tipo);
					printf("Nivel da bateria?\n");
					scanf("%f", &bat);
					printf("Autonomia\n");
					scanf("%f", &aut);
					meios = inserirMeio(meios, cod, tipo, bat, aut);
					break;
				case 2:
					listarMeios(meios);
					break;
				case 3:
					printf("Codigo do meio de mobilidade a remover?\n");
					scanf("%d", &cod);
					meios = removerMeio(meios, cod);
					break;
				case 4:
					guardarMeios(meios);
					break;
				case 5:
					meios = lerMeios();
					break;
				}
			} while (opM != 0);
			break;
		case 2:
			// ------------------- Gestores ------------------
			do
			{
				opG = menuGestores();
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
					printf("Saldo:\n");
					scanf("%f", &saldo);
					gestores = inserirGestor(gestores, id, nome, nif, morada, saldo);
					break;
				case 2:
					listarGestores(gestores);
					break;
				case 3:
					printf("Id do gestor a remover?\n");
					scanf("%d", &id);
					gestores = removerGestor(gestores, id);
					break;
				case 4:
					guardarGestores(gestores);
					break;
				case 5:
					gestores = lerGestores();
					break;
				}
			} while (opG != 0);
			break;
		case 3:
			// ------------------- Clientes ------------------
			do
			{
				opC = menuClientes();
				switch (opC)
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
					printf("Saldo:\n");
					scanf("%f", &saldo);
					clientes = inserirCliente(clientes, id, nome, nif, morada, saldo);
					break;
				case 2:
					listarClientes(clientes);
					break;
				case 3:
					printf("Id do cliente a remover?\n");
					scanf("%d", &id);
					clientes = removerCliente(clientes, id);
					break;
				case 4:
					guardarClientes(clientes);
					break;
				case 5:
					clientes = lerClientes();
					break;
				}
			} while (opC != 0);
			break;
		}

	} while (op != 0);
	*/
	return (0);
}
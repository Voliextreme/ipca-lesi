#include <stdio.h>
#include "./controllers/meio.h"
#include "./controllers/conta.h"
#include "./controllers/aluguer.h"
#include "./controllers/grafo.h"
#include "./controllers/meio.c"
#include "./controllers/conta.c"
#include "./controllers/aluguer.c"
#include "./controllers/grafo.c"

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
	printf("5 Alterar Meio\n");
	printf("6 Listar meios por ordem decrescente de autonomia\n");
	printf("7 Listar meios por Geocodigo\n");
	printf("0 Sair\n");
	printf("Opcao:\n");
}

void menuGestores()
{
	printf("\n --- Menu Gestores --- \n");
	printf("1 Inserir Gestor\n");
	printf("2 Listar Users\n");
	printf("3 Remover User\n");
	printf("4 Alterar Users\n");
	printf("5 Criar Grafo\n");
	printf("6 Listar Grafo\n");
	printf("7 Listar meios perto de um cliente\n");
	printf("8 Recolher meios com bateria inferior a 50\n");
	printf("0 Sair\n");
	printf("Opcao:\n");
}

void menuClientes()
{
	printf("\n --- Menu Cliente --- \n");
	printf("1 Alugar Meio\n");
	printf("2 Devolver Meio\n");
	printf("3 Alterar Informacoes do Cliente\n");
	printf("4 Listar Alugueres\n");

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

void criarGrafo(Grafo *grafo)
{

	if (grafo != NULL)
	{
		printf("Grafo ja existe\n");
		return;
	}
	else
	{

		// Inserir os vertices no grafo
		criarVertice(&grafo, "1.1.1");
		criarVertice(&grafo, "3.3.3");
		criarVertice(&grafo, "4.4.4");
		criarVertice(&grafo, "2.2.2");

		// Inserir as arestas no grafo
		criarAresta(&grafo, "1.1.1", "3.3.3", 50);
		criarAresta(&grafo, "2.2.2", "1.1.1", 30);
		criarAresta(&grafo, "2.2.2", "4.4.4", 20);
		criarAresta(&grafo, "4.4.4", "1.1.1", 40);

		// Inserir os meios no grafo
		inserirMeioNoGrafo(&grafo, "2.2.2", 1);
		inserirMeioNoGrafo(&grafo, "1.1.1", 2);
		inserirMeioNoGrafo(&grafo, "4.4.4", 3);
		inserirMeioNoGrafo(&grafo, "2.2.2", 4);
		inserirMeioNoGrafo(&grafo, "3.3.3", 5);

		listarGrafo(grafo);
		guardarGrafo(grafo);
	}
}

int main()
{
	Meio *meios = NULL;		   // Lista ligada vazia
	User *users = NULL;		   // Lista ligada vazia
	Aluguer *alugueres = NULL; // Lista ligada vazia
	User *userAtual = NULL;
	Grafo *grafo = NULL;

	int op = 0, opP = 0, opG = 0, opC = 0, opM = 0, id, login = 0, role = 0, codigo = 0;
	float bateria, autonomia, saldo, custo, proximidade;
	char tipo[50], nome[50], morada[100], nif[10], email[50], geoCodigo[50];
	int disponivel;

	// Menu Principal
	do
	{
		grafo = lerGrafo();
		meios = lerMeios();
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
								printf("GeoCodigo(ex: braga.ponte.rio):\n");
								scanf("%[^\n]s", geoCodigo);
								users = createUser(users, id, nome, nif, morada, email, role, saldo, geoCodigo);
								saveUsers(users);
								saveUsersBin(users);
								break;
							case 2:
								listUsers(users);
								break;
							case 3:
								printf("Id do user a remover?\n");
								scanf("%d", &id);
								users = removeUser(users, id);
								saveUsers(users);
								saveUsersBin(users);
								break;
							case 4:
								listUsers(users);
								printf("Id do user a alterar?\n");
								scanf("%d", &id);
								alterarUser(&users, id);
								saveUsers(users);
								saveUsersBin(users);
								break;
							case 5:
								criarGrafo(grafo);
							case 6:
								listarGrafo(grafo);
								break;
							case 7:
								printf("Em que proximidade:\n");
								scanf("%f", &proximidade);
								scanf("%*c");
								printf("Qual o meio que pretende encontrar(ex: trotinete):\n");
								scanf("%[^\n]s", tipo);
								printMeiosDentroRaio(grafo, meios, "2.2.2", proximidade, tipo);
								break;
							case 8:
								meios = percursoCamiao(grafo, meios, 50);
								guardarMeios(meios);
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
								printf("GeoCodigo(ex: braga.ponte.rio):\n");
								scanf("%[^\n]s", geoCodigo);
								getchar();
								disponivel = true;
								meios = inserirMeio(meios, codigo, tipo, bateria, autonomia, custo, geoCodigo, disponivel);
								guardarMeios(meios);
								guardarMeiosBin(meios);
								break;
							case 2:
								listarMeios(meios);
								break;
							case 3:
								printf("Codigo do meio a remover?\n");
								scanf("%d", &codigo);
								meios = removerMeio(meios, codigo);
								guardarMeios(meios);
								guardarMeiosBin(meios);
								break;
							case 4:
								meios = lerMeios();
								break;
							case 5:
								listarMeios(meios);
								printf("Codigo do meio de mobilidade a alterar?\n");
								scanf("%d", &codigo);
								alterarMeio(&meios, codigo);
								guardarMeios(meios);
								guardarMeiosBin(meios);
								break;
							case 6:
								listMeiosPorAutonomiaDecrescente(&meios);
								break;
							case 7:
								printf("GeoCodigo?\n");
								scanf("%s", geoCodigo);
								listarMeiosPorGeocodigo(meios, geoCodigo);
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
				do
				{
					meios = lerMeios();
					alugueres = lerAlugueres();
					int idAlugado = 0;
					menuClientes();
					scanf("%d", &opC);
					switch (opC)
					{
					case 1:
						listarMeiosDisponiveis(meios);
						printf("Codigo do meio de mobilidade a alugar?\n");
						scanf("%d", &codigo);
						alugueres = alugarMeio(alugueres, meios, codigo, userAtual->id, users);
						listarAlugueres(alugueres);
						guardarAlugueres(alugueres);
						guardarMeios(meios);
						break;
					case 2:
						idAlugado = listarAlugueresUser(alugueres, userAtual->id);
						devolverMeio(&meios, alugueres, idAlugado);
						removerAluguer(alugueres, idAlugado);
						guardarAlugueres(alugueres);
						guardarMeios(meios);
						break;
					case 3:
						users = readUsers();
						alterarUserCliente(&users, userAtual->id);
						saveUsers(users);
						saveUsersBin(users);
						break;
					case 4:
						listarAlugueres(alugueres);
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
			printf("GeoCodigo(ex: braga.ponte.rio):\n");
			scanf("%[^\n]s", geoCodigo);
			users = createUser(users, id, nome, nif, morada, email, role, saldo, geoCodigo);
			listUsers(users);
			saveUsers(users);
			break;
		default:
			break;
		}

	} while (login != 0);

	return (0);
}
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <stdlib.h>

#include "structs_const.h"

using namespace std;

/********/
/* MAIN */
/********/
int main()
{
	int opcao = 0, opcao2 = 0, opcao3 = 0;
	int teste_erro;
	bool bin_existe = false;
	string cand_user;					// Nome que o usuario possivlemente ira digitar
	TrieNode *raiz;						// Raiz da árvore Trie

	/* Menu do programa via seleção de opção */
	system("CLS");
	cout << "Bem vindo a pesquisa de candidatos das eleicoes de 2018!" << endl << endl;
	cout << "Nela, voce pode verificar os dados de todos os candidatos dessa eleicao" << endl;
	cout << "e tambem podera pesquisar e realizar estatisticas em cima dos candidatos" << endl << endl;

	do
	{
		cout << "Por favor, selecione uma opcao abaixo:" <<endl << endl;
		cout << "1 - Ler e inserir os dados do arquivo de candidatos no programa" << endl;
		cout << "2 - Ler os dados a partir de um arquivo binario" << endl;
		cout << "3 - Sair do programa" << endl << endl;

		cin >> opcao;
		switch(opcao)
		{
			case 1:
				teste_erro = abertura_arquivo();
				if(teste_erro == -1)
				{
					cout << "Certifique-se que o arquivo esta no mesmo diretorio do programa" << endl << endl;
				}
				break;
			case 2:
				if(!arquivo_existe())
				{
					cout << endl << "Nao existe um arquivo binario com os dados dos candidatos." << endl << endl;
					bin_existe = false;
				}
				else
				{
					cout << endl << "Arquivo encontrado!" << endl << endl;
					bin_existe = true;
				}
				break;
			case 3:
				cout << endl << "Encerrando o programa..." << endl;
				return 0;
				break;
			default:
				system("CLS");
				cout << "Selecione uma opcao valida!" << endl << endl;
				break;
		}
	} while((opcao != 1 && opcao != 3 && (opcao != 2 && bin_existe)) || teste_erro == -1 || (opcao == 2 && !bin_existe));
	
	if(!bin_existe)
	{
		/* Área de código após a abertura do arquivo de entrada obter sucesso */

		/* Inicialização da Trie */
		cout << "Lendo o arquivo de entrada e guardando" << endl;
		cout << "os novos dados em dados_candidatos.bin" << endl << endl;
		
		/* Leitura do arquivo com dados brutos */
		leitura_arquivo(teste_erro);
	}
	/* Criação da árvore de prefixos */
	cout << "Criando arvore de prefixos" << endl << endl;
	raiz = inicializa_trie();											// Inicializa a Trie somente com a raiz
	
	raiz = add_candidatos_trie(raiz);									// Adiciona os candidatos na arvore a partir do arquivo binario, retornando a raiz no fim
	cout << "Arvore de prefixos criada, todos os candidatos ja foram inseridos!" << endl << endl;
	
	do
	{
		cout << endl << "Por favor, selecione uma nova opcao abaixo:" <<endl << endl;
		cout << "1 - Pesquisar por um candidato" << endl;
		cout << "2 - Gerar novas tabelas" << endl;
		cout << "3 - Sair do programa" << endl << endl;
		
		cin >> opcao2;
		switch(opcao2)
		{
			case 1:
				cout << endl << "Digite o nome completo do candidato que esta procurando, sem acentos: ";
				cin.ignore();
				getline(cin, cand_user);
				cand_user = minusculas_para_maiusculas(cand_user);
				pesquisa_trie(raiz, cand_user);
				break;
			case 2:
				cout << endl<< "Selecione uma das seguintes tabelas:" << endl << endl;
				cout << "1 - Tabela de resultados dos candidatos que concorreram somente no 1o turno" << endl;
				cout << "2 - Tabela de resultados dos candidatos que concorreram no 2o turno" << endl;
				cout << "3 - Tabela de candidatos que tiveram sua candidatura anulada" << endl << endl;
				cin >> opcao3;
				if(opcao3 < 1 || opcao3 > 3)
					cout << endl << "Voce digitou uma opcao invalida!" << endl << endl;
				else
					if(opcao3 == 1)
					{
						abre_tabelas(raiz, opcao3);
						cout << endl << "Arquivo tabela_1_turno.csv criado com sucesso" << endl << endl;
					}
					if(opcao3 == 2)
					{
						abre_tabelas(raiz, opcao3);
						cout << endl << "Arquivo tabela_2_turno.csv criado com sucesso" << endl << endl;
					}
					if(opcao3 == 3)
					{
						abre_tabelas(raiz, opcao3);
						cout << endl << "Arquivo tabela_anulados.csv criado com sucesso" << endl << endl;
					}
				break;
			case 3:
				cout << endl << "Encerrando o programa..." << endl;
				return 0;
				break;
			default:
				system("CLS");
				cout << "Selecione uma opcao valida!" << endl << endl;
				break;
		}
	} while(opcao2 != 3);
	
	return 0;
}


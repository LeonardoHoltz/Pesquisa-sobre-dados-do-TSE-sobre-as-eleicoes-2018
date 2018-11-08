#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

/**************/
/* CABEÇALHOS */
/**************/
ifstream abertura_arquivo(); // Faz a leitura do arquivo onde estão os dados originalmente

class candidatos
{
	public: 
		int numero;
		string nome, partido, situacao, cargo, UF;
};



int main()
{
	int opcao = 0;
	ifstream teste_erro;
	
	teste_erro = NULL;
	
	system("CLS");
	cout << "Bem vindo a pesquisa de candidatos das eleicoes de 2018!" << endl << endl;
	cout << "Nela, voce pode verificar os dados de todos os candidatos dessa eleicao" << endl;
	cout << "e tambem podera pesquisar e realizar estatisticas em cima dos candidatos" << endl << endl;
	
	do
	{	
		cout << "Por favor, selecione uma opcao abaixo:" <<endl << endl;
		cout << "1 - Ler e inserir os dados do arquivo de candidatos no programa" << endl;
		cout << "2 - Sair do programa" << endl << endl;
		
		cin >> opcao;
		switch(opcao)
		{
			case 1:
				teste_erro = abertura_arquivo();
				if(teste_erro == NULL)
				{
					cout << "Certifique-se que o arquivo esta no mesmo diretorio do programa" << endl << endl;
				}
				break;
			case 2:
				cout << endl << "Encerrando o programa..." << endl;
				return 0;
				break;
			default:
				system("CLS");
				cout << "Selecione uma opcao valida!" << endl << endl;
				break;
		}
	} while((opcao != 1 && opcao != 2) || teste_erro == NULL);
	return 0;
}

ifstream abertura_arquivo()
{
	
	cout << endl << "Acessando arquivo de dados..." << endl << endl;
	ifstream DataFile;
	DataFile.open("candidatos_2018_BRASIL_updated.csv");
	if(!DataFile)
	{
		cerr << "O arquivo de dados nao pode ser acessado!" << endl;
		return NULL;   // chama o sistema para interrromper o programa
	}
	else
	{
		cout << "Arquivo de dados acessado com sucesso!" << endl;
		
		return DataFile;
	}
}
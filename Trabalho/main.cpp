#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

/**************/
/* CABEÇALHOS */
/**************/
int leitura_arquivo(); // Faz a leitura do arquivo onde estão os dados originalmente

int main()
{
	int opcao, teste_erro = 0;
	
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
				teste_erro = leitura_arquivo();
				if(teste_erro == -1)
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
	} while((opcao != 1 && opcao != 2) || teste_erro == -1);
	return 0;
}

int leitura_arquivo()
{
	long int linhas = 0;
	string line;
	cout << endl << "Acessando arquivo de dados..." << endl << endl;
	ifstream DataFile;
	DataFile.open("candidatos_2018_BRASIL_updated.csv");
	if(!DataFile)
	{
    cerr << "O arquivo de dados nao pode ser acessado!" << endl;
    return -1;   // chama o sistema para interrromper o programa
	}
	else
	{
		cout << "Arquivo de dados acessado com sucesso!" << endl;
		while(!DataFile.eof())
			getline(DataFile, line);
		DataFile.close();
		return 0;
	}
}
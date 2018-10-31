#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

/**************/
/* CABEÇALHOS */
/**************/
void leitura_arquivo(); // Faz a leitura do arquivo onde estão os dados originalmente

int main()
{
	system("CLS");
	cout << "Bem vindo a pesquisa de candidatos das eleicoes de 2018!" << endl << endl;
	cout << "Nela, voce pode verificar os dados de todos os candidatos dessa eleicao" << endl;
	cout << "e tambem podera pesquisar e realizar estatisticas em cima dos candidatos" << endl << endl;
	cout << "Por favor, selecione uma opcao abaixo:" <<endl;
	return 0;
}

void leitura_arquivo()
{
	long int linhas = 0;
	string line;
	cout << "Acessando arquivo de dados..." << endl;
	ifstream DataFile;
	DataFile.open("candidatos_2018_BRASIL.csv");
	if(!DataFile)
	{
    cerr << "O arquivo de dados não pode ser acessado!";
    //return -1;   // chama o sistema para interrromper o programa
	}
	else
	{
		cout << "Arquivo de dados acessado com sucesso!" << endl;
		while(!DataFile.eof())
		{
			getline(DataFile, line);
			cout << line << endl;
			linhas++;
		}
		cout << linhas << endl;
		DataFile.close();
	}
}
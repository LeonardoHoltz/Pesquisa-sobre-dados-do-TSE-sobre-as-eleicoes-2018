#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>
using namespace std;

const int ALPHABET_TAM = 27;
const int MAX_TAM = 30;

/**************/
/* CABEÇALHOS */
/**************/
int abertura_arquivo(); // Faz a leitura do arquivo onde estão os dados originalmente
void leitura_arquivo();

class candidatos
{
	public: 
		int numero; 
		string nome, partido, situacao, cargo, UF;
		
};

typedef struct
{
	candidato *filhos[ALPHABET_TAM];
	bool eh_palavra; //flag que indica se o conteudo do nodo é uma palavra ou apenas um prefixo 
}TrieNode;

ifstream DataFile;

/********/
/* MAIN */
/********/
int main()
{
	int opcao = 0;
	int teste_erro;
	
	
	
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
	
	leitura_arquivo();
	
	return 0;
}

<<<<<<< HEAD
/***********/
/* FUNÇÕES */
/***********/

int leitura_arquivo()
=======


int abertura_arquivo()
>>>>>>> da8ec20b5aafd74d79e0aa31cd652b138171437a
{
	
	cout << endl << "Acessando arquivo de dados..." << endl << endl;
	
	DataFile.open("candidatos_2018_BRASIL_updated.csv");
	cout << "batata";
	if(!DataFile)
	{
		cout << "nigga why isnt this shit workin ??";
		cerr << "O arquivo de dados nao pode ser acessado!" << endl;
		return -1;   // chama o sistema para interrromper o programa
	}
	else
	{
		cout << "Arquivo de dados acessado com sucesso!" << endl;
		
		return 0;
	}
}

void leitura_arquivo()
{
	string line;
	
	while(!(DataFile.eof()))
	{
		getline(DataFile, line, ';');// vai passando pelo arquivo, separando palavra por palavra com o token ';'
		
		
		
		//cout << line;, tempo de espera muito longo para printar tudo
	}
	
	cout << "deu bom taoquei?";
}















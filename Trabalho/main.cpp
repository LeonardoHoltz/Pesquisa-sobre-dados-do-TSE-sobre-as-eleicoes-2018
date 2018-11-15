#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>
using namespace std;

/**************/
/* CONSTANTES */
/**************/

/* ALPHABET_TAM representa todos os caracteres que podem constar no nome de um
	candidato. Dentro de um array, o índice 0 representa a letra 'A', 1 a letra
	'B' e assim por diante até o índice 25 com a letra 'Z', o 26° índice
	representará o caractere SPACE, que servirá para separar os nomes e sobrenomes
	dos candidatos */
const int ALPHABET_TAM = 27;

const int MAX_TAM = 30;


/***********************/
/* CLASSE DO CANDIDATO */
/***********************/

class candidatos
{
	public:
		int numero;
		string nome, partido, situacao, cargo, UF;
};

/*********************/
/* ESTRUTURA DA TRIE */
/*********************/
struct Nodo_Trie
{
	bool eh_raiz;										// flag que indica se o nodo da árvore é a raíz ou não.
	bool possui_candidato;					// flag que indica se o nodo da árvore possuí o dado de um candidato. Pode ser um nodo folha.
	char letra;											// Letra guardará uma das letras do nome de um candidato.
	candidatos *pessoa;							// Caso possui_candidato seja True, pessoa guardará os dados de um candidato.
	Nodo_Trie *filhos[ALPHABET_TAM];	// Array de ponteiros para os filhos daquele nodo. Cada indice representa um caractere. NULL indica que o nodo não possui um filho para o caractere representado pelo índice.
};
typedef struct Nodo_Trie TrieNode;

/**************/
/* CABEÇALHOS */
/**************/
int abertura_arquivo(); // Abre o arquivo onde estão os dados originalmente
TrieNode inicializa_trie(); // Inicializa a árvore Trie com a criação da raíz
void leitura_arquivo();


/* Ponteiro do arquivo de entrada */
ifstream DataFile;

/********/
/* MAIN */
/********/
int main()
{
	int opcao = 0;
	int teste_erro;


	/* Menu do programa via seleção de opção */
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

	/* Área de código após a abertura do arquivo obter sucesso */

	/* Inicialização da Trie */
	cout << "Criando arvore de prefixos." << endl << endl;
	TrieNode raiz = inicializa_trie();
	return 0;
	/* Leitura de dados do arquivo */
	leitura_arquivo();

	return 0;
}

/***********/
/* FUNÇÕES */
/***********/

/* Abertura do arquivo de dados */
int abertura_arquivo()
{
	cout << endl << "Acessando arquivo de dados..." << endl << endl;

	DataFile.open("candidatos_2018_BRASIL_updated.csv");
	if(!DataFile)
	{
		cerr << "O arquivo de dados nao pode ser acessado!" << endl;
		return -1;   // chama o sistema para interrromper o programa
	}
	else
	{
		cout << "Arquivo de dados acessado com sucesso!" << endl << endl;
		return 0;
	}
}

/* Inicialização da Árvore de Prefixos */
TrieNode inicializa_trie()
{
	TrieNode raiz;	// Inicializa o nodo.
	raiz.eh_raiz = 1;		// Indica que o nodo a ser criado é a raíz da árvore
	raiz.possui_candidato = 0; // A raíz não possui nenhum candidato
	raiz.letra = '0';	// A raíz não inicia com uma letra
	raiz.pessoa = NULL;	// A raíz não possui nenhum candidato
	for(int i = 0; i < ALPHABET_TAM; i++)
		raiz.filhos[i] = NULL;	// Para cada caractere, a raíz ainda não possui um filho associado a aquele caractere.
	return raiz;
}

/* Leitura dos dados do arquivo */
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

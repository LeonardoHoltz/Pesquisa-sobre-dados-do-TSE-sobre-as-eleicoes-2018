#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
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
	/* Candidato terá os seguintes dados:
		Número: O número do candidato na urna para a eleição
		Nome: Nome do candidato
		Partido: Partido do candidato
		Situação: Situação do candidato após as votações
		Cargo: Cargo ao qual o candidato está tentando se eleger
		UF: Estado/Distrito no qual o candidato estará representando */
	public:
		string nome, partido, situacao, cargo, UF, numero;
};

/*********************/
/* ESTRUTURA DA TRIE */
/*********************/
struct Nodo_Trie
{
	bool eh_raiz;										// flag que indica se o nodo da árvore é a raíz ou não.
	bool possui_candidato;					// flag que indica se o nodo da árvore possuí o dado de um candidato. Pode ser um nodo folha.
	char letra;											// Letra guardará uma das letras do nome de um candidato.
	candidatos pessoa;							// Caso possui_candidato seja True, pessoa guardará os dados de um candidato.
	Nodo_Trie *filhos[ALPHABET_TAM];	// Array de ponteiros para os filhos daquele nodo. Cada indice representa um caractere. NULL indica que o nodo não possui um filho para o caractere representado pelo índice.
};
typedef struct Nodo_Trie TrieNode;

/**************/
/* CABEÇALHOS */
/**************/

/**********************/
/* FUNÇÕES PRINCIPAIS */
/**********************/
int abertura_arquivo(); // Abre o arquivo onde estão os dados originalmente
TrieNode *inicializa_trie(); // Inicializa a árvore Trie com a criação da raíz
void leitura_arquivo(TrieNode *raiz); // Função que realiza a leitura do arquivo e guarda os dados na Trie
TrieNode *novo_nodo(); // Função que cria um novo nodo da Trie
void insere_Trie(TrieNode *raiz, string dado); //insere um candidato na arvore Trie
bool pesquisa(TrieNode *raiz, string chave); // procura um candidato na arvore Trie

/**********************/
/* FUNÇÕES AUXILIARES */
/**********************/
string retira_aspas(string palavra);	// Função que retira as aspas no começo e fim de uma palavra e a retorna

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
	TrieNode *raiz = inicializa_trie();
	
	/* Leitura de dados do arquivo */
	leitura_arquivo(raiz);
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
TrieNode *inicializa_trie()
{
	TrieNode *raiz = new TrieNode;	// Inicializa o nodo.
	raiz->eh_raiz = 1;		// Indica que o nodo a ser criado é a raíz da árvore
	raiz->possui_candidato = 0; // A raíz não possui nenhum candidato
	raiz->letra = ' ';	// A raíz não inicia com uma letra
	
	/* A raíz não inicia com os dados do candidato */
	raiz->pessoa.numero = ' ';
	raiz->pessoa.nome = ' ';
	raiz->pessoa.situacao = ' ';
	raiz->pessoa.cargo = ' ';
	raiz->pessoa.UF = ' ';
	raiz->pessoa.partido = ' ';
	
	for(int i = 0; i < ALPHABET_TAM; i++)
		raiz->filhos[i] = NULL;	// Para cada caractere, a raíz ainda não possui um filho associado a aquele caractere.
	return raiz;
}

/*
void insere_Trie(TrieNode *raiz, string dado)
{
	TrieNode *auxiliar = raiz;
	int cont, indice;
	
	for(cont = 0; cont < dado.lenght();cont++)
	{
		indice = dado[cont] - 'a';
		if(!(auxiliar->filhos[indice]))
			auxiliar->filhos[indice] = inicializa_trie();
		auxiliar = auxiliar->filhos[indice];
	}
	
	auxiliar->eh_raiz = false;
	auxiliar->possui_candidato = true;
	
}

bool pesquisa(TrieNode *raiz, string chave)
{
	TrieNode *auxiliar = raiz;
	int cont, indice;
	
	for(cont = 0; cont<chave.lenght(); cont++)
	{
		indice = chave[cont]-'a';
		if(!(auxiliar->filhos[indice]))
			return false;
		auxiliar = auxiliar->filhos[indice];
		
	}
	return (auxiliar != NULL && auxiliar->possui_candidato);
}
*/

/* Leitura dos dados do arquivo */
void leitura_arquivo(TrieNode *raiz)
{
	// Strings para guardar os dados relevantes de cada candidato.
	string line, estado_cand, cargo_cand, numero_cand, nome_cand, partido_cand, situacao_cand;
	int i;	// Variavel para laços
	
	//while(!(DataFile.eof()))
	//{
		TrieNode *novo_candidato = novo_nodo();
		
		/* Atribuição da Unidade de Federação */
		getline(DataFile, line);
		for(i = 0; i < 12; i++)
			getline(DataFile, line, ';'); 					// vai passando pelo arquivo, separando palavra por palavra com o token ';', eliminando os dados irrelevantes para a pesquisa
		getline(DataFile, line, ';');						// Recebe o dado da UF
		estado_cand = retira_aspas(line);					// Retira as aspas da palavra
		novo_candidato->pessoa.UF = estado_cand;			// Define a unidade de federação do candidato
		
		/* Atribuição do Cargo */
		getline(DataFile, line, ';');						// Pula o próximo dado, irrelevante para a nossa pesquisa
		getline(DataFile, line, ';');						// Recebe o dado do cargo
		cargo_cand = retira_aspas(line);					// Retira as aspas da palavra
		novo_candidato->pessoa.cargo = cargo_cand;			// Define o cargo para o qual o candidato está concorrendo
		
		/* Atribuição do Número */
		getline(DataFile, line, ';');						// Pula o próximo dado, irrelevante para a nossa pesquisa
		getline(DataFile, line, ';');						// Recebe o dado do número
		numero_cand = retira_aspas(line);					// Retira as aspas da palavra
		novo_candidato->pessoa.numero = numero_cand;		// Define o numero do candidato na urna
		
		/* Atribuição do Nome */
		getline(DataFile, line, ';');						// Recebe o dado do nome
		nome_cand = retira_aspas(line);						// Retira as aspas da palavra
		novo_candidato->pessoa.nome = nome_cand;			// Define o numero do candidato na urna
		
		/* Atribuição do Partido */
		for(i = 0; i < 11; i++)
			getline(DataFile, line, ';'); 					// vai passando pelo arquivo, separando palavra por palavra com o token ';', eliminando os dados irrelevantes para a pesquisa
		getline(DataFile, line, ';');						// Recebe o dado do partido
		partido_cand = retira_aspas(line);					// Retira as aspas da palavra
		novo_candidato->pessoa.partido = partido_cand;		// Define o partido do candidato
		
		/* Atribuição da Situação do candidato após as eleições */
		for(i = 0; i < 23; i++)
			getline(DataFile, line, ';'); 					// vai passando pelo arquivo, separando palavra por palavra com o token ';', eliminando os dados irrelevantes para a pesquisa
		getline(DataFile, line, ';');						// Recebe o dado do partido
		situacao_cand = retira_aspas(line);					// Retira as aspas da palavra
		novo_candidato->pessoa.situacao = situacao_cand;	// Define o partido do candidato
		
		cout << novo_candidato->pessoa.UF << endl;
		cout << novo_candidato->pessoa.cargo << endl;
		cout << novo_candidato->pessoa.numero << endl;
		cout << novo_candidato->pessoa.nome << endl;
		cout << novo_candidato->pessoa.partido << endl;
		cout << novo_candidato->pessoa.situacao << endl;
}

/* Criação de um novo nodo da Trie */
TrieNode *novo_nodo()
{
	TrieNode *novo = new TrieNode;
	
	novo->eh_raiz = false;
	novo->possui_candidato = false;
	novo->letra = 0;
	novo->pessoa.numero = ' ';
	novo->pessoa.nome = ' ';
	novo->pessoa.partido = ' ';
	novo->pessoa.situacao = ' ';
	novo->pessoa.cargo = ' ';
	novo->pessoa.UF = ' ';
	for(int i = 0; i < ALPHABET_TAM; i++)
		novo->filhos[i] = NULL;
	return novo;
}

/**********************/
/* FUNÇÕES AUXILIARES */
/**********************/

/* Retira as aspas duplas que estão a direita e a esquerda da palavra */
string retira_aspas(string palavra)
{
	palavra.erase(find(palavra.begin(),palavra.end(), '"'));
	palavra.erase(find(palavra.begin(),palavra.end(), '"'));
	return palavra;
}

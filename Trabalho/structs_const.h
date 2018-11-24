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
	candidato. Dentro de um array, o índice 0 representa o caractere espaço,
	índice 1 até o 26 representam o alfabeto de A até Z */
const int ALPHABET_TAM = 27;

/* QUANTIDADE_CANDIDATOS representa o total de candidatos que há no arquivo bruto, essa
	constante existe porque o end of file em alguns arquivos nao é muito preciso em
	algumas funções, e portanto, devemos utilizar um contador que chega até esta constante */

const int QUANTIDADE_CANDIDATOS = 29145;


/***********************/
/* CLASSE DO CANDIDATO */
/***********************/

class candidatos
{
	/* Candidato terá os seguintes dados:
		Número: O número do candidato na urna para a eleição
		Nome: Nome do candidato
		Partido: Partido do candidato
		Situação: Situação do candidato após as votações no turno indicado
		Cargo: Cargo ao qual o candidato está tentando se eleger
		UF: Estado/Distrito no qual o candidato estará representando
		Turno: Turno no qual o candidato teve sua situação final definida */
	public:
		string nome, partido, situacao, cargo, UF, numero, turno;
};


/*********************/
/* ESTRUTURA DA TRIE */
/*********************/

struct Nodo_Trie
{
	bool eh_raiz;													// flag que indica se o nodo da árvore é a raíz ou não.
	bool possui_candidato;											// flag que indica se o nodo da árvore possuí o dado de um candidato. Pode ser um nodo folha.
	char letra;														// Letra guardará uma das letras do nome de um candidato.
	candidatos pessoa;												// Caso possui_candidato seja True, pessoa guardará os dados de um candidato.
	Nodo_Trie *filhos[ALPHABET_TAM];								// Array de ponteiros para os filhos daquele nodo. Cada indice representa um caractere. NULL indica que o nodo não possui um filho para o caractere representado pelo índice.
};
typedef struct Nodo_Trie TrieNode;


/**************/
/* CABEÇALHOS */
/**************/

/**********************/
/* FUNÇÕES PRINCIPAIS */
/**********************/

int abertura_arquivo(); 											// Abre o arquivo onde estão os dados originalmente

TrieNode *inicializa_trie(); 										// Inicializa a árvore Trie com a criação da raíz

void leitura_arquivo(int quantidade_linhas); 						// Função que realiza a leitura do arquivo bruto e guarda os dados em um arquivo binario

TrieNode *novo_nodo(); 												// Função que cria um novo nodo da Trie

TrieNode *add_candidatos_trie(TrieNode *raiz);					 	// Função que adiciona os candidatos na árvore a partir do arquivo binário

void pesquisa_trie(TrieNode *raiz, string nome_usuario);			// Função que pesquisa um candidato na Trie e mostra os dados dele na tela

void abre_tabelas(TrieNode *nodo, int opcao);						// Função que abre a tabela referente a opcao selecionada e escreve o cabeçalho dela

void cria_tabelas_trie(TrieNode *nodo, int opcao);					// Função que cria novas tabelas, mais organizadas que a original, a partir da trie

/**********************/
/* FUNÇÕES AUXILIARES */
/**********************/

bool arquivo_existe();												// Função que retorna true se o arquivo binário existe e false caso o contrário

string retira_aspas(string palavra);								// Função que retira as aspas no começo e fim de uma palavra e a retorna

string minusculas_para_maiusculas(string palavra);					//Função que transforma as letras minúsculas da string de entrada em letras maiúsculas

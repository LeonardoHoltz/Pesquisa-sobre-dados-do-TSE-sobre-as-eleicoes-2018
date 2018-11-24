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

class candidatos
{
	/* Candidato terá os seguintes dados:
		Número: O número do candidato na urna para a eleição
		Nome: Nome do candidato
		Partido: Partido do candidato
		Situação: Situação do candidato após as votações
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
	bool eh_raiz;						// flag que indica se o nodo da árvore é a raíz ou não.
	bool possui_candidato;				// flag que indica se o nodo da árvore possuí o dado de um candidato. Pode ser um nodo folha.
	char letra;							// Letra guardará uma das letras do nome de um candidato.
	candidatos pessoa;					// Caso possui_candidato seja True, pessoa guardará os dados de um candidato.
	Nodo_Trie *filhos[ALPHABET_TAM];	// Array de ponteiros para os filhos daquele nodo. Cada indice representa um caractere. NULL indica que o nodo não possui um filho para o caractere representado pelo índice.
};
typedef struct Nodo_Trie TrieNode;


TrieNode *novo_nodo()
{
	TrieNode *novo = new TrieNode;
	
	novo->eh_raiz = false;
	novo->possui_candidato = false;
	novo->letra = '0';
	novo->pessoa.numero = '0';
	novo->pessoa.nome = '0';
	novo->pessoa.partido = '0';
	novo->pessoa.situacao = '0';
	novo->pessoa.cargo = '0';
	novo->pessoa.UF = '0';
	novo->pessoa.turno = '0';
	for(int i = 0; i < ALPHABET_TAM; i++)
		novo->filhos[i] = NULL;
	return novo;
}

int main()
{
	TrieNode *novo_candidato;
	ifstream BinaryFile;
	BinaryFile.open("dados_candidatos.bin", ios::in | ios::binary);
	if(BinaryFile.is_open())
	while(!BinaryFile.eof())
	{
		BinaryFile.read((char *) &novo_candidato, sizeof(TrieNode));
		cout << novo_candidato->pessoa.numero << " " << novo_candidato->pessoa.nome << " ";
		cout << novo_candidato->pessoa.partido << " " << novo_candidato->pessoa.situacao << " " << novo_candidato->pessoa.cargo << " ";
		cout << novo_candidato->pessoa.UF << " " << novo_candidato->pessoa.turno << endl;
	}
	BinaryFile.close();
	cout << "teste" << endl;
	return 0;
}

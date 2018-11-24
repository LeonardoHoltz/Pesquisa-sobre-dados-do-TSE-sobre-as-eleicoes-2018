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

/**************/
/* CABEÇALHOS */
/**************/

/**********************/
/* FUNÇÕES PRINCIPAIS */
/**********************/
int abertura_arquivo(); 											// Abre o arquivo onde estão os dados originalmente

TrieNode *inicializa_trie(); 										// Inicializa a árvore Trie com a criação da raíz

void leitura_arquivo(int quantidade_linhas); 						// Função que realiza a leitura do arquivo e guarda os dados na Trie

TrieNode *novo_nodo(); 												// Função que cria um novo nodo da Trie
void le_arquivo();

TrieNode *add_candidatos_trie(TrieNode *raiz);					 	// Função que adiciona os candidatos na árvore

void transfere_arq_bin(TrieNode *raiz);								// Função que transfere os dados da Trie para um arquivo binário

void recursive_write(TrieNode *nodo);								// Função recursiva que guarda um nodo e seus filhos em um arquivo binario

TrieNode *recarregar_trie();										// Função que recarrega a Trie a partir do arquivo binario

void recarrega_trie_recursive(TrieNode *nodo_pai, int indice);		// Função recursiva que recupera os nodos de uma trie

/**********************/
/* FUNÇÕES AUXILIARES */
/**********************/
bool arquivo_existe();									// Função que retorna true se o arquivo binário existe e false caso o contrário

string retira_aspas(string palavra);					// Função que retira as aspas no começo e fim de uma palavra e a retorna

string minusculas_para_maiusculas(string palavra);		//Função que transforma as letras minúsculas da string de entrada em letras maiúsculas

/***********************/
/* HANDLES DE ARQUIVOS */
/***********************/

/* Stream do arquivo de entrada */
ifstream DataFile;

/********/
/* MAIN */
/********/
int main()
{
	int opcao = 0, opcao2 = 0, opcao3 = 0;
	int teste_erro;
	bool bin_existe = false;
	string cand_user;
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
	
	le_arquivo();
	
	//raiz = add_candidatos_trie(raiz);									// Adiciona os candidatos na arvore a partir do arquivo binario, retornando a raiz no fim
	cout << "Arvore de prefixos criada, todos os candidatos ja foram inseridos!" << endl << endl;
	/*
	do
	{
		cout << "Por favor, selecione uma nova opcao abaixo:" <<endl << endl;
		cout << "1 - Pesquisar por um candidato" << endl;
		cout << "2 - Gerar novas tabelas" << endl;
		cout << "3 - Sair do programa" << endl << endl;
		
		cin >> opcao2;
		switch(opcao2)
		{
			case 1:
				cout << "Digite o nome completo do candidato que esta procurando, sem acentos: ";
				cin.ignore();
				getline(cin, cand_user);
				cand_user = minusculas_para_maiusculas(cand_user);
				break;
			case 2:
				cout << "Selecione uma das seguintes tabelas:" << endl << endl;
				cout << "1 - Tabela de resultados dos candidatos que concorreram somente no 1o turno" << endl;
				cout << "2 - Tabela de resultados dos candidatos que concorreram no 2o turno" << endl;
				cout << "3 - Tabela de candidatos que tiveram sua candidatura anulada" << endl << endl;
				cin >> opcao3;
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
	*/
	return 0;
}

/***********/
/* FUNÇÕES */
/***********/

/* Abertura do arquivo de dados */
int abertura_arquivo()
{
	int quantidade_linhas = 0;
	string line;
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
		while(!DataFile.eof())
		{
			getline(DataFile, line);
			quantidade_linhas++;
		}
		DataFile.clear();
		DataFile.seekg(0, ios::beg);
		return quantidade_linhas;
	}
}

/* Inicialização da Árvore de Prefixos */
TrieNode *inicializa_trie()
{
	TrieNode *raiz = new TrieNode;	// Inicializa o nodo.
	raiz->eh_raiz = 1;		// Indica que o nodo a ser criado é a raíz da árvore
	raiz->possui_candidato = 0; // A raíz não possui nenhum candidato
	raiz->letra = '0';	// A raíz não inicia com uma letra
	
	/* A raíz não inicia com os dados do candidato */
	raiz->pessoa.numero = '0';
	raiz->pessoa.nome = '0';
	raiz->pessoa.situacao = '0';
	raiz->pessoa.cargo = '0';
	raiz->pessoa.UF = '0';
	raiz->pessoa.partido = '0';
	raiz->pessoa.turno = '0';
	
	for(int i = 0; i < ALPHABET_TAM; i++)
		raiz->filhos[i] = NULL;	// Para cada caractere, a raíz ainda não possui um filho associado a aquele caractere.
	return raiz;
}

/* Leitura dos dados do arquivo */
void leitura_arquivo(int quantidade_linhas)
{
	// Strings para guardar os dados relevantes de cada candidato.
	string line, turno_cand, estado_cand, cargo_cand, numero_cand, nome_cand, partido_cand, situacao_cand;
	// Variaveis para laços
	int i, j, k;
	size_t tamanho;
	ofstream BinaryFile;
	BinaryFile.open("dados_candidatos.bin", ios::binary | ios::out | ios::trunc);	// Abre o arquivo binário para inserção de dados
	
	getline(DataFile, line);														// Pula a primeira linha
	
	for(j = 0; j < quantidade_linhas - 2; j++)
	{	
		/* Atribuição do turno do candidato */
		for(i = 0; i < 5; i++)
			getline(DataFile, line, ';'); 					// vai passando pelo arquivo, separando palavra por palavra com o token ';', eliminando os dados irrelevantes para a pesquisa
		getline(DataFile, line, ';');						// Recebe o dado do turno
		turno_cand = retira_aspas(line);					// Retira as aspas da palavra
		tamanho = turno_cand.size();
		BinaryFile.write((char *)&tamanho, sizeof(tamanho));
		BinaryFile.write((char *)&turno_cand[0], tamanho);
		
		/* Atribuição da Unidade de Federação */
		for(i = 0; i < 6; i++)
			getline(DataFile, line, ';'); 					// vai passando pelo arquivo, separando palavra por palavra com o token ';', eliminando os dados irrelevantes para a pesquisa
		getline(DataFile, line, ';');						// Recebe o dado da UF
		estado_cand = retira_aspas(line);					// Retira as aspas da palavra
		tamanho = estado_cand.size();
		BinaryFile.write((char *)&tamanho, sizeof(tamanho));
		BinaryFile.write((char *)&estado_cand[0], tamanho);
		
		/* Atribuição do Cargo */
		getline(DataFile, line, ';');						// Pula o próximo dado, irrelevante para a nossa pesquisa
		getline(DataFile, line, ';');						// Recebe o dado do cargo
		cargo_cand = retira_aspas(line);					// Retira as aspas da palavra
		tamanho = cargo_cand.size();
		BinaryFile.write((char *)&tamanho, sizeof(tamanho));
		BinaryFile.write((char *)&cargo_cand[0], tamanho);
		
		/* Atribuição do Número */
		getline(DataFile, line, ';');						// Pula o próximo dado, irrelevante para a nossa pesquisa
		getline(DataFile, line, ';');						// Recebe o dado do número
		numero_cand = retira_aspas(line);					// Retira as aspas da palavra
		tamanho = numero_cand.size();
		BinaryFile.write((char *)&tamanho, sizeof(tamanho));
		BinaryFile.write((char *)&numero_cand[0], tamanho);
		
		/* Atribuição do Nome */
		getline(DataFile, line, ';');						// Recebe o dado do nome
		nome_cand = retira_aspas(line);						// Retira as aspas da palavra
		tamanho = nome_cand.size();
		BinaryFile.write((char *)&tamanho, sizeof(tamanho));
		BinaryFile.write((char *)&nome_cand[0], tamanho);
		
		/* Atribuição do Partido */
		for(i = 0; i < 11; i++)
			getline(DataFile, line, ';'); 					// vai passando pelo arquivo, separando palavra por palavra com o token ';', eliminando os dados irrelevantes para a pesquisa
		getline(DataFile, line, ';');						// Recebe o dado do partido
		partido_cand = retira_aspas(line);					// Retira as aspas da palavra
		tamanho = partido_cand.size();
		BinaryFile.write((char *)&tamanho, sizeof(tamanho));
		BinaryFile.write((char *)&partido_cand[0], tamanho);
		
		/* Atribuição da Situação do candidato após as eleições */
		for(i = 0; i < 23; i++)
			getline(DataFile, line, ';'); 					// vai passando pelo arquivo, separando palavra por palavra com o token ';', eliminando os dados irrelevantes para a pesquisa
		getline(DataFile, line, ';');						// Recebe o dado do partido
		situacao_cand = retira_aspas(line);					// Retira as aspas da palavra
		tamanho = situacao_cand.size();
		BinaryFile.write((char *)&tamanho, sizeof(tamanho));
		BinaryFile.write((char *)&situacao_cand[0], tamanho);
		
		getline(DataFile, line);
	}
	
	/* Fecha os dois arquivos */
	BinaryFile.close();
	DataFile.close();
}

/* Criação de um novo nodo da Trie */
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

void le_arquivo()
{
	size_t tamanho;
	int i = 0;
	string new_string;
	TrieNode novo_candidato;
	ifstream BinaryFile;
	BinaryFile.open("dados_candidatos.bin", ios::in | ios::binary);
	while(i < 29145)
	{
		BinaryFile.read((char *)&tamanho, sizeof(tamanho));
		new_string.resize(tamanho);
		BinaryFile.read((char *)&new_string[0], tamanho);
		novo_candidato.pessoa.turno = new_string;
		
		BinaryFile.read((char *)&tamanho, sizeof(tamanho));
		new_string.resize(tamanho);
		BinaryFile.read((char *)&new_string[0], tamanho);
		novo_candidato.pessoa.UF = new_string;
		
		BinaryFile.read((char *)&tamanho, sizeof(tamanho));
		new_string.resize(tamanho);
		BinaryFile.read((char *)&new_string[0], tamanho);
		novo_candidato.pessoa.cargo = new_string;
		
		BinaryFile.read((char *)&tamanho, sizeof(tamanho));
		new_string.resize(tamanho);
		BinaryFile.read((char *)&new_string[0], tamanho);
		novo_candidato.pessoa.numero = new_string;
		
		BinaryFile.read((char *)&tamanho, sizeof(tamanho));
		new_string.resize(tamanho);
		BinaryFile.read((char *)&new_string[0], tamanho);
		novo_candidato.pessoa.nome = new_string;
		
		BinaryFile.read((char *)&tamanho, sizeof(tamanho));
		new_string.resize(tamanho);
		BinaryFile.read((char *)&new_string[0], tamanho);
		novo_candidato.pessoa.partido = new_string;
		
		BinaryFile.read((char *)&tamanho, sizeof(tamanho));
		new_string.resize(tamanho);
		BinaryFile.read((char *)&new_string[0], tamanho);
		novo_candidato.pessoa.situacao = new_string;
		
		cout << novo_candidato.pessoa.numero << " " << novo_candidato.pessoa.nome << " ";
		cout << novo_candidato.pessoa.partido << " " << novo_candidato.pessoa.cargo << " ";
		cout << novo_candidato.pessoa.UF << " " << novo_candidato.pessoa.turno << endl;
		
		i++;
	}
	BinaryFile.close();
	cout << "teste" << endl;
}

/* Criação de Prefixos na árvore, sempre que se adiciona um novo  candidato e seu nome na árvore */
TrieNode *add_candidatos_trie(TrieNode *raiz)
{
	int nome_tam;					// Variável para o tamanho do nome do candidato
	TrieNode *aux;					// Ponteiro auxiliar para a raíz
	TrieNode *novo_candidato;		// Estrutura onde o candidato será mantido quando ele for lido do arquivo
	string new_string;
	size_t tamanho;					// Tamanho da próxima string a ser lida do arquivo
	int i;							// Variavel para laço
	
	/* Abertura do arquivo para leitura */
	ifstream BinaryFile;
	BinaryFile.open("dados_candidatos.bin", ios::in | ios::binary);
	
	while(i < 29145)
		BinaryFile.read((char *) &novo_candidato, sizeof(TrieNode));
		cout << "teste" << endl;
		nome_cand = novo_candidato->pessoa.nome;
		cout << nome_cand << endl;
		nome_tam = nome_cand.length();
		aux = raiz;													// Colocamos o ponteiro auxiliar na raiz
		for(int i = 0; i < nome_tam; i++)
		{
			/* Primeiro testamos o caso onde o caractere que estamos lidando no momento do laço
			não é um espaço. Devemos fazer isso pois convencionamos para este programa que o 27°
			índice guardará somente um filho nodo com o caractere espaço, e como o espaço está
			posicionado na tabela ASCII de forma diferente da qual convencionamos para o array
			de filhos (antes das letras maiusculas => num 32 na tabela ASCII, e depois das letras
			maiusculas => indice 26 no nosso array), devemos fazer um caso especial para o caractere. */
			if(nome_cand[i] != 32)									// Caso o caractere não seja um espaço
			{
				// 65 = 'A' => conseguimos transformar o char em um índice
				if(aux->filhos[nome_cand[i] - 65] == NULL)			// Caso o nodo ainda não tenha um filho daquela letra
				{
					TrieNode *nova_letra = novo_nodo();				// Criamos um novo nodo para ser um dos filhos do nodo pai (aux)
					nova_letra->letra = nome_cand[i];				// Atribuímos a letra correta que representa aquele nodo
					aux->filhos[nome_cand[i] - 65] = nova_letra;	// Fazemos a ligação entre o nodo pai e o nodo filho
					aux = nova_letra;								// Atualizamos o ponteiro
				}
				else												// Caso o nodo pai já tenha um filho com aquela letra
				{
					aux = aux->filhos[nome_cand[i] - 65];			// Somente atualizamos o ponteiro auxiliar
				}
			}
			else													// Caso o caractere seja um espaço
			{
				if(aux->filhos[nome_cand[i] - 6] == NULL)			// Caso o nodo ainda não tenha um filho daquela letra
				{
					TrieNode *nova_letra = novo_nodo();				// Criamos um novo nodo para ser um dos filhos do nodo pai (aux)
					nova_letra->letra = nome_cand[i];				// Atribuímos a letra correta que representa aquele nodo
					aux->filhos[nome_cand[i] - 6] = nova_letra;		// Fazemos a ligação entre o nodo pai e o nodo filho
					aux = nova_letra;								// Atualizamos o ponteiro
				}
				else
				{
					aux = aux->filhos[nome_cand[i] - 6];			// Somente atualizamos o ponteiro auxiliar
				}
			}
		}
		
		/* Coloca os dados do novo candidato no auxiliar */
		
		/*Se já houver um candidato no fim do nome, devemos fazer um
		teste para podermos substituírmos alguns dos dados dele */
		if(aux->possui_candidato)
		{
			/* Se a situacao do novo candidato for "SUPLENTE", "ELEITO", "ELEITO POR QP", "ELEITO POR MEDIA" ou "NAO ELEITO", devemos atualizar suas informações, pois as antigas não servem mais */
			if(novo_candidato->pessoa.situacao == "SUPLENTE" || novo_candidato->pessoa.situacao == "ELEITO" || novo_candidato->pessoa.situacao == "ELEITO POR QP" || novo_candidato->pessoa.situacao == "ELEITO POR MEDIA" || novo_candidato->pessoa.situacao == "NAO ELEITO")
			{
				aux->pessoa.numero = novo_candidato->pessoa.numero;
				aux->pessoa.nome = novo_candidato->pessoa.nome;
				aux->pessoa.partido = novo_candidato->pessoa.partido;
				aux->pessoa.situacao = novo_candidato->pessoa.situacao;
				aux->pessoa.cargo = novo_candidato->pessoa.cargo;
				aux->pessoa.UF = novo_candidato->pessoa.UF;
				aux->pessoa.turno = novo_candidato->pessoa.turno;
			}
		}
		/* Se não houver um candidato ainda no final do nome, somente
		adiciona os dados do novo candidato através do ponteiro auxiliar */
		else
		{
			aux->pessoa.numero = novo_candidato->pessoa.numero;
			aux->pessoa.nome = novo_candidato->pessoa.nome;
			aux->pessoa.partido = novo_candidato->pessoa.partido;
			aux->pessoa.situacao = novo_candidato->pessoa.situacao;
			aux->pessoa.cargo = novo_candidato->pessoa.cargo;
			aux->pessoa.UF = novo_candidato->pessoa.UF;
			aux->pessoa.turno = novo_candidato->pessoa.turno;
			aux->possui_candidato = true;								// O nodo de novo_candidato tem o dado de um candidato
		}
	}
	BinaryFile.close();
	return raiz;
}

/**********************/
/* FUNÇÕES AUXILIARES */
/**********************/

/* Verifica a existencia de um arquivo, retornando true caso ele e xiste e false caso o contrário */
bool arquivo_existe()
{
    if (FILE *file = fopen("dados_candidatos.bin", "r"))
	{
        fclose(file);
        return true;
    }
	else
        return false;
}

/* Retira as aspas duplas que estão a direita e a esquerda da palavra */
string retira_aspas(string palavra)
{
	palavra.erase(find(palavra.begin(),palavra.end(), '"'));
	palavra.erase(find(palavra.begin(),palavra.end(), '"'));
	return palavra;
}

/* Transforma as letras minúsculas da string de entrada em letras maiúsculas */
string minusculas_para_maiusculas(string palavra)
{
	int tamanho_palavra = palavra.length();
	for(int i = 0; i < tamanho_palavra; i++)
	{
		if(palavra[i] >= 97 && palavra[i] <= 122)
			palavra[i] = palavra[i] - 32;
	}
	return palavra;
}

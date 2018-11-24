#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <stdlib.h>

#include "structs_const.h"

using namespace std;

/**********/
/* HANDLE */
/**********/
ofstream tabela;		// Handle dos arquivos de tabelas

/***********/
/* FUNÇÕES */
/***********/

/* Abertura do arquivo de dados */
int abertura_arquivo()
{
	int quantidade_linhas = 0;
	string line;
	cout << endl << "Acessando arquivo de dados..." << endl << endl;
	ifstream DataFile;		// Handle do arquivo de leitura
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
	raiz->eh_raiz = 1;				// Indica que o nodo a ser criado é a raíz da árvore
	raiz->possui_candidato = 0; 	// A raíz não possui nenhum candidato
	raiz->letra = '0';				// A raíz não inicia com uma letra
	
	/* A raíz não inicia com os dados do candidato */
	raiz->pessoa.numero = '0';
	raiz->pessoa.nome = '0';
	raiz->pessoa.situacao = '0';
	raiz->pessoa.cargo = '0';
	raiz->pessoa.UF = '0';
	raiz->pessoa.partido = '0';
	raiz->pessoa.turno = '0';
	
	for(int i = 0; i < ALPHABET_TAM; i++)
		raiz->filhos[i] = NULL;		// Para cada caractere, a raíz ainda não possui um filho associado a aquele caractere.
	return raiz;
}

/* Leitura dos dados do arquivo */
void leitura_arquivo(int quantidade_linhas)
{
	/* Strings para guardar os dados relevantes de cada candidato */
	string line, turno_cand, estado_cand, cargo_cand, numero_cand, nome_cand, partido_cand, situacao_cand;
	/* Variaveis para laços */
	int i, j, k;
	size_t tamanho;
	ifstream DataFile;																// Handle do arquivo de leitura
	ofstream BinaryFile;															// Handle para o arquivo binário de dados
	DataFile.open("candidatos_2018_BRASIL_updated.csv");
	BinaryFile.open("dados_candidatos.bin", ios::binary | ios::out | ios::trunc);	// Abre o arquivo binário para inserção de dados
	
	getline(DataFile, line);														// Pula a primeira linha
	
	for(j = 0; j < quantidade_linhas - 2; j++)
	{	
		/* Atribuição do turno do candidato */
		for(i = 0; i < 5; i++)
			getline(DataFile, line, ';'); 						// vai passando pelo arquivo, separando palavra por palavra com o token ';', eliminando os dados irrelevantes para a pesquisa
		getline(DataFile, line, ';');							// Recebe o dado do turno
		turno_cand = retira_aspas(line);						// Retira as aspas da palavra
		tamanho = turno_cand.size();
		BinaryFile.write((char *)&tamanho, sizeof(tamanho));	// Escreve o tamanho da proxima string
		BinaryFile.write((char *)&turno_cand[0], tamanho);		// Escreve a string
		
		/* Atribuição da Unidade de Federação */
		for(i = 0; i < 6; i++)
			getline(DataFile, line, ';'); 						// vai passando pelo arquivo, separando palavra por palavra com o token ';', eliminando os dados irrelevantes para a pesquisa
		getline(DataFile, line, ';');							// Recebe o dado da UF
		estado_cand = retira_aspas(line);						// Retira as aspas da palavra
		tamanho = estado_cand.size();
		BinaryFile.write((char *)&tamanho, sizeof(tamanho));	// Escreve o tamanho da proxima string
		BinaryFile.write((char *)&estado_cand[0], tamanho);		// Escreve a string
		
		/* Atribuição do Cargo */
		getline(DataFile, line, ';');							// Pula o próximo dado, irrelevante para a nossa pesquisa
		getline(DataFile, line, ';');							// Recebe o dado do cargo
		cargo_cand = retira_aspas(line);						// Retira as aspas da palavra
		tamanho = cargo_cand.size();
		BinaryFile.write((char *)&tamanho, sizeof(tamanho));	// Escreve o tamanho da proxima string
		BinaryFile.write((char *)&cargo_cand[0], tamanho);		// Escreve a string
		
		/* Atribuição do Número */
		getline(DataFile, line, ';');							// Pula o próximo dado, irrelevante para a nossa pesquisa
		getline(DataFile, line, ';');							// Recebe o dado do número
		numero_cand = retira_aspas(line);						// Retira as aspas da palavra
		tamanho = numero_cand.size();
		BinaryFile.write((char *)&tamanho, sizeof(tamanho));	// Escreve o tamanho da proxima string
		BinaryFile.write((char *)&numero_cand[0], tamanho);		// Escreve a string
		
		/* Atribuição do Nome */
		getline(DataFile, line, ';');							// Recebe o dado do nome
		nome_cand = retira_aspas(line);							// Retira as aspas da palavra
		tamanho = nome_cand.size();
		BinaryFile.write((char *)&tamanho, sizeof(tamanho));	// Escreve o tamanho da proxima string
		BinaryFile.write((char *)&nome_cand[0], tamanho);		// Escreve a string
		
		/* Atribuição do Partido */
		for(i = 0; i < 11; i++)
			getline(DataFile, line, ';'); 						// vai passando pelo arquivo, separando palavra por palavra com o token ';', eliminando os dados irrelevantes para a pesquisa
		getline(DataFile, line, ';');							// Recebe o dado do partido
		partido_cand = retira_aspas(line);						// Retira as aspas da palavra
		tamanho = partido_cand.size();
		BinaryFile.write((char *)&tamanho, sizeof(tamanho));	// Escreve o tamanho da proxima string
		BinaryFile.write((char *)&partido_cand[0], tamanho);	// Escreve a string
		
		/* Atribuição da Situação do candidato após as eleições */
		for(i = 0; i < 23; i++)
			getline(DataFile, line, ';'); 						// vai passando pelo arquivo, separando palavra por palavra com o token ';', eliminando os dados irrelevantes para a pesquisa
		getline(DataFile, line, ';');							// Recebe o dado do partido
		situacao_cand = retira_aspas(line);						// Retira as aspas da palavra
		tamanho = situacao_cand.size();
		BinaryFile.write((char *)&tamanho, sizeof(tamanho));	// Escreve o tamanho da proxima string
		BinaryFile.write((char *)&situacao_cand[0], tamanho);	// Escreve a string
		
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
	/* O nodo criado não começa com nenhuma nova informação */
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

/* Criação de Prefixos na árvore, sempre que se adiciona um novo  candidato e seu nome na árvore */
TrieNode *add_candidatos_trie(TrieNode *raiz)
{
	int nome_tam;					// Variável para o tamanho do nome do candidato
	TrieNode *aux;					// Ponteiro auxiliar para a raíz
	TrieNode novo_candidato;		// Estrutura onde o candidato será mantido quando ele for lido do arquivo
	string new_string, nome_cand;	// Variáveis para guardar strings
	size_t tamanho;					// Tamanho da próxima string a ser lida do arquivo
	int j = 0;						// Variavel para laço
	
	ifstream BinaryFile;			// Handle para o arquivo binário de dados
	BinaryFile.open("dados_candidatos.bin", ios::in | ios::binary);
	
	while(j < QUANTIDADE_CANDIDATOS)
	{	
		/* A leitura sempre começa com o tamanho da próxima string a ser lida e a própria string */
		BinaryFile.read((char *)&tamanho, sizeof(tamanho));
		new_string.resize(tamanho);
		BinaryFile.read((char *)&new_string[0], tamanho);
		novo_candidato.pessoa.turno = new_string;					// Atribui o turno do candidato
		
		BinaryFile.read((char *)&tamanho, sizeof(tamanho));
		new_string.resize(tamanho);
		BinaryFile.read((char *)&new_string[0], tamanho);
		novo_candidato.pessoa.UF = new_string;						// Atribui o local do candidato
		
		BinaryFile.read((char *)&tamanho, sizeof(tamanho));
		new_string.resize(tamanho);
		BinaryFile.read((char *)&new_string[0], tamanho);
		novo_candidato.pessoa.cargo = new_string;					// Atribui o cargo do candidato
		
		BinaryFile.read((char *)&tamanho, sizeof(tamanho));
		new_string.resize(tamanho);
		BinaryFile.read((char *)&new_string[0], tamanho);
		novo_candidato.pessoa.numero = new_string;					// Atribui o numero do candidato
		
		BinaryFile.read((char *)&tamanho, sizeof(tamanho));
		new_string.resize(tamanho);
		BinaryFile.read((char *)&new_string[0], tamanho);
		novo_candidato.pessoa.nome = new_string;					// Atribui o nome do candidato
		
		BinaryFile.read((char *)&tamanho, sizeof(tamanho));
		new_string.resize(tamanho);
		BinaryFile.read((char *)&new_string[0], tamanho);
		novo_candidato.pessoa.partido = new_string;					// Atribui o partido do candidato
		
		BinaryFile.read((char *)&tamanho, sizeof(tamanho));
		new_string.resize(tamanho);
		BinaryFile.read((char *)&new_string[0], tamanho);
		novo_candidato.pessoa.situacao = new_string;				// Atribui a situação do candidato
		
		nome_cand = novo_candidato.pessoa.nome;
		nome_tam = nome_cand.length();
		
		aux = raiz;													// Colocamos o ponteiro auxiliar na raiz
		for(int i = 0; i < nome_tam; i++)
		{
			/* Primeiro testamos o caso onde o caractere que estamos lidando no momento do laço
			não é um espaço. Devemos fazer isso pois convencionamos para este programa que o 1°
			índice guardará somente um filho nodo com o caractere espaço */
			if(nome_cand[i] != 32)									// Caso o caractere não seja um espaço
			{
				// 65 = 'A' => conseguimos transformar o char em um índice se fizermos (caractere - 64)
				if(aux->filhos[nome_cand[i] - 64] == NULL)			// Caso o nodo ainda não tenha um filho daquela letra
				{
					TrieNode *nova_letra = novo_nodo();				// Criamos um novo nodo para ser um dos filhos do nodo pai (aux)
					nova_letra->letra = nome_cand[i];				// Atribuímos a letra correta que representa aquele nodo
					aux->filhos[nome_cand[i] - 64] = nova_letra;	// Fazemos a ligação entre o nodo pai e o nodo filho
					aux = nova_letra;								// Atualizamos o ponteiro
				}
				else												// Caso o nodo pai já tenha um filho com aquela letra
				{
					aux = aux->filhos[nome_cand[i] - 64];			// Somente atualizamos o ponteiro auxiliar
				}
			}
			else													// Caso o caractere seja um espaço
			{
				if(aux->filhos[nome_cand[i] - 32] == NULL)			// Caso o nodo ainda não tenha um filho daquela letra
				{
					TrieNode *nova_letra = novo_nodo();				// Criamos um novo nodo para ser um dos filhos do nodo pai (aux)
					nova_letra->letra = nome_cand[i];				// Atribuímos a letra correta que representa aquele nodo
					aux->filhos[nome_cand[i] - 32] = nova_letra;	// Fazemos a ligação entre o nodo pai e o nodo filho
					aux = nova_letra;								// Atualizamos o ponteiro
				}
				else
				{
					aux = aux->filhos[nome_cand[i] - 32];			// Somente atualizamos o ponteiro auxiliar
				}
			}
		}
		
		/* Coloca os dados do novo candidato no auxiliar */
		
		/*Se já houver um candidato no fim do nome, devemos fazer um
		teste para podermos substituírmos alguns dos dados dele */
		if(aux->possui_candidato)
		{
			/* Se a situacao do novo candidato for "SUPLENTE", "ELEITO", "ELEITO POR QP", "ELEITO POR MEDIA" ou "NAO ELEITO", devemos atualizar suas informações, pois as antigas não servem mais */
			if(novo_candidato.pessoa.situacao == "SUPLENTE" || novo_candidato.pessoa.situacao == "ELEITO" || novo_candidato.pessoa.situacao == "ELEITO POR QP" || novo_candidato.pessoa.situacao == "ELEITO POR MEDIA" || novo_candidato.pessoa.situacao == "NAO ELEITO")
			{
				aux->pessoa.numero = novo_candidato.pessoa.numero;
				aux->pessoa.nome = novo_candidato.pessoa.nome;
				aux->pessoa.partido = novo_candidato.pessoa.partido;
				aux->pessoa.situacao = novo_candidato.pessoa.situacao;
				aux->pessoa.cargo = novo_candidato.pessoa.cargo;
				aux->pessoa.UF = novo_candidato.pessoa.UF;
				aux->pessoa.turno = novo_candidato.pessoa.turno;
			}
		}
		/* Se não houver um candidato ainda no final do nome, somente
		adiciona os dados do novo candidato através do ponteiro auxiliar */
		else
		{
			aux->pessoa.numero = novo_candidato.pessoa.numero;
			aux->pessoa.nome = novo_candidato.pessoa.nome;
			aux->pessoa.partido = novo_candidato.pessoa.partido;
			aux->pessoa.situacao = novo_candidato.pessoa.situacao;
			aux->pessoa.cargo = novo_candidato.pessoa.cargo;
			aux->pessoa.UF = novo_candidato.pessoa.UF;
			aux->pessoa.turno = novo_candidato.pessoa.turno;
			aux->possui_candidato = true;								// O nodo de novo_candidato tem o dado de um candidato
		}
		j++;															// Passa para o próximo candidato
	}
	BinaryFile.close();
	return raiz;
}

/* Pesquisa um candidato na Trie e mostra os dados dele na tela */
void pesquisa_trie(TrieNode *raiz, string nome_usuario)
{
	TrieNode *aux = raiz;												// Criamos um ponteiro que aponta para a raíz da árvore
	int tamanho_nome = nome_usuario.length();
	bool nao_achou = false;
	for(int i = 0; i < tamanho_nome; i++)
	{
		/* Testa se existe um filho referente a letra do laço */
		if(nome_usuario[i] != 32)										// Se o caractere não for um espaço
		{
			if(aux->filhos[nome_usuario[i] - 64] == NULL)				// Se aux nao possuir um filho com o indice equivalente a letra do nome, então o nome procurado não está na árvore
				nao_achou = true;
			else
				aux = aux->filhos[nome_usuario[i] - 64];				// Atualizamos o ponteiro auxliar para apontar agora para seu filho
		}
		else															// Se o caractere for um espaço
		{
			if(aux->filhos[nome_usuario[i] - 32] == NULL)				// Se aux nao possuir um filho com o indice equivalente a espaço, então o nome procurado não está na árvore
				nao_achou = true;
			else
				aux = aux->filhos[nome_usuario[i] - 32];				// Atualizamos o ponteiro auxliar para apontar agora para seu filho
		}
	}
	/* Se chegou no final do nome na Trie, verifica se há um candidato no nodo com o mesmo nome de entrada */
	if(!nao_achou)
	{
		if(aux->pessoa.nome == nome_usuario)
		{
			/* Printa na tela as informações do candidato encontrado */
			cout << endl << nome_usuario << " encontrado:" << endl << endl;
			cout << "Nome: " << aux->pessoa.nome << endl;
			cout << "Local que quer representar: " << aux->pessoa.UF << endl;
			cout << "Cargo ao qual se candidatou: " << aux->pessoa.cargo << endl;
			cout << "Numero: " << aux->pessoa.numero << endl;
			cout << "Partido: " << aux->pessoa.partido << endl;
			cout << "Turno: " << aux->pessoa.turno << "o TURNO" << endl;
			cout << "Situacao: " << aux->pessoa.situacao << endl;
		}
		else
			cout << endl << "Nao foi possivel encontrar " << nome_usuario << " dentro da arvore" << endl << endl;
	}
	else
		cout << endl << "Nao foi possivel encontrar " << nome_usuario << " dentro da arvore" << endl << endl;
}

/* Abre a tabela referente a opcao selecionada e escreve o cabeçalho dela */
void abre_tabelas(TrieNode *raiz, int opcao)
{
	if(opcao == 1)
	{
		tabela.open("tabela_1_turno.csv", ios::trunc);
		tabela << "\"NOME\";\"UNIDADE DE FEDERACAO/PAIS\";\"CARGO\";\"NUMERO\";\"PARTIDO\";\"SITUACAO\"\n";
		cria_tabelas_trie(raiz, opcao);
	}
	if(opcao == 2)
	{
		tabela.open("tabela_2_turno.csv", ios::trunc);
		tabela << "\"NOME\";\"UNIDADE DE FEDERACAO/PAIS\";\"CARGO\";\"NUMERO\";\"PARTIDO\";\"SITUACAO\"\n";
		cria_tabelas_trie(raiz, opcao);
	}
	if(opcao == 3)
	{
		tabela.open("tabela_anulados.csv", ios::trunc);
		tabela << "\"NOME\";\"UNIDADE DE FEDERACAO/PAIS\";\"CARGO\";\"NUMERO\";\"PARTIDO\"\n";
		cria_tabelas_trie(raiz, opcao);
	}
	tabela.close();
}

/* Função que cria novas tabelas, mais organizadas que a original, a partir da trie */
void cria_tabelas_trie(TrieNode *nodo, int opcao)
{
	TrieNode *aux = nodo;
	/* Se o nodo recebido por parâmetro possuir o dado de um candidato, coloca na tabela adequada */
	if(aux->possui_candidato)
	{
		/* Se a opção selecionada for a criação da tabela de resultados dos candidatos que concorreram somente no 1° turno */
		if(opcao == 1 && aux->pessoa.turno == "1" && aux->pessoa.situacao != "2° TURNO" && aux->pessoa.situacao != "#NULO#")
		{
			tabela << "\"" << aux->pessoa.nome << "\";\"";
			tabela << aux->pessoa.UF << "\";\"";
			tabela << aux->pessoa.cargo << "\";\"";
			tabela << aux->pessoa.numero << "\";\"";
			tabela << aux->pessoa.partido << "\";\"";
			tabela << aux->pessoa.turno << "\";\"";
			tabela << aux->pessoa.situacao << "\"\n";
		}
		/* Se a opção selecionada for a criação da tabela de resultados dos candidatos que concorreram no 2° turno */
		if(opcao == 2 && aux->pessoa.turno == "2")
		{
			tabela << "\"" << aux->pessoa.nome << "\";\"";
			tabela << aux->pessoa.UF << "\";\"";
			tabela << aux->pessoa.cargo << "\";\"";
			tabela << aux->pessoa.numero << "\";\"";
			tabela << aux->pessoa.partido << "\";\"";
			tabela << aux->pessoa.situacao << "\"\n";
		}
		/* Se a opção selecionada for a criação da tabela de resultados dos candidatos que tiveram sua candidatura anulada */
		if(opcao == 3 && aux->pessoa.situacao == "#NULO#")
		{
			tabela << "\"" << aux->pessoa.nome << "\";\"";
			tabela << aux->pessoa.UF << "\";\"";
			tabela << aux->pessoa.cargo << "\";\"";
			tabela << aux->pessoa.numero << "\";\"";
			tabela << aux->pessoa.partido << "\"\n";
		}
	}
	/* Chama a função recursivamente para todos os filhos existentes */
	for(int i = 0; i < ALPHABET_TAM; i++)
	{
		if(aux->filhos[i] != NULL)
			cria_tabelas_trie(aux->filhos[i], opcao);
	}
}

/**********************/
/* FUNÇÕES AUXILIARES */
/**********************/

/* Verifica a existencia de um arquivo, retornando true caso ele exista e false caso o contrário */
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
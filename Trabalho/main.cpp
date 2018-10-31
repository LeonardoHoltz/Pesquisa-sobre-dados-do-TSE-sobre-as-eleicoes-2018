#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	long int linhas = 0;
	string line;
	cout << "Acessando arquivo de dados..." << endl;
	ifstream DataFile;
	DataFile.open("candidatos_2018_BRASIL.csv");
	if(!DataFile)
	{
    cerr << "O arquivo de dados não pode ser acessado!";
    return -1;   // chama o sistema para interrromper o programa
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
	return 0;
}
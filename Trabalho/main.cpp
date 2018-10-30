#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	string line = "oi";
	long long int linhas = 0;
	cout << "Acessando arquivo de dados..." << endl;
	ifstream DataFile;
	DataFile.open("perfil_eleitor_secao_2018_RS.csv");
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
			line0 = line
			getline(DataFile, line);
			linhas++;
		}
	}
	cout << linhas << endl;
	cout << line0 << endl;
	getline(DataFile, line);
	linhas++;
	cout << line << endl;
	cout << linhas << endl;
	return 0;
}
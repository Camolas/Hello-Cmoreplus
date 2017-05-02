#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <istream>
#include <cstring>
#include "string.h"


using namespace std;

typedef unsigned int idNum;
idNum idDriver = 0;

struct driver
{
	idNum id;
	string name;
	int hCombo;
	int hMax;
	int hRest;

};

struct bline
{
	idNum id;
	int freqTime;
	vector <string> spots;
	vector <int> timeSpots;

};


void trimSpaces(string &str)
{
	while (str.front() == ' ')
		str.erase(str.begin());

	while (str.back() == ' ')
		str.erase(str.end() - 1);
}
/*
if (fileDrive.is_open())
{
	while (getline(fileDrive, line))
	{
		cout << line << endl;
	}
	fileDrive.close();
}
else cout << "Unable to open file";
*/


void readBlines(ifstream &fileB, vector <bline> bLines)//, bline busP);
{
	bline blineSTCP;
	istringstream iStrStream;

	if (fileB.is_open())
	{
		string ln;

		for (int cnt = 1; getline(fileB, ln, ';'); cnt++)
		{
			stringstream ss(ln);

			switch (cnt)
			{
			case 1: {
				ss >> blineSTCP.id;
				break;

			}
			case 2: {
				ss >> blineSTCP.freqTime;
				break;
			}
			case 3: {
				//getline(ss, ln, ',');
				////ss >> station;
				//trimSpaces(ln);
				//blineSTCP.spots.push_back(ln);
				getline(ss, ln, ';');
				ln.erase(ln.begin());
				iStrStream.str(ln);
				while (iStrStream.good()) // um do while ... mas se o itenerário não contiver paragens originará um erro!!?
				{
					getline(iStrStream, ln, ',');
					trimSpaces(ln);
					blineSTCP.spots.push_back(ln);
				}
				break;
			}
			case 4: // time to hold in station/spots
			{
				/*
				int time;
				getline(ss, ln, '\n'); // o conteúdo das stringstream não é visível, tentámos add a watch com iStreamstring.str();
				*/
				/*ln.erase(ln.begin());
				iStrStream.str(ln);
				cout << iStrStream.str();
				while (iStrStream.good())
				{
					getline(iStrStream, ln, ',');
					char * cstr = new char[ln.length() + 1];
					char *p = strtok(cstr, ",");
					int time = atoi(p);
					blineSTCP.timeSpots.push_back(time);
				}*/
				/*ln.erase(ln.begin());
				iStrStream.str(ln);
				while(iStrStream.eof())
				{
					getline(iStrStream, ln, ',');
					trimSpaces(ln);
					time = stoi(ln);
					blineSTCP.timeSpots.push_back(time);*/
					//getline(ss, ln, '\n'); // o conteúdo das stringstream não é visível, tentámos add a watch com iStreamstring.str();
				int time;
				
				iStrStream.clear();
				iStrStream.str(ln);
				cout << iStrStream.str() << "\n";
				while (iStrStream.good())
				{
					getline(iStrStream, ln, ',');
					ln.erase(ln.begin());
					blineSTCP.timeSpots.push_back(stoi(ln));
				}
				cnt = 0;
				bLines.push_back(blineSTCP);
				bline blineSTCP;
				break;
			}
			}
		}

	}
	else
		cerr << "error to open drivers file" << endl; // with this output fuction,it can show the message with red colour 

}

void readDrivers(ifstream &fileD, vector <driver> &driversB) // não posso ter parametros com o mesmo nome
{
	driver driverB;


	if (fileD.is_open())
	{

		string line;
		int counter = 1;

		/*getline(cli, line, '\0');
		cout << "BusDriver:\n" << line <<  endl; erase of file..*/
		for (int counter = 1; getline(fileD, line, ';'); counter++)
		{
			stringstream ss(line); // There ss have value.. "" see

								   //trimSpaces(line);
			switch (counter)
			{
			case 1: // save id of driver
				ss >> driverB.id;
				if (driverB.id > idDriver) //faço  this mean that idMax is actualized cout << ss; 
					idDriver = driverB.id;

				break;
			case 2: // save name of driver
			{
				trimSpaces(line);
				driverB.name = line;
				//string s = ss.str();

				//ss.ignore(1, ';');
				break;
			}
			case 3: // save horas
				//trimSpaces(line);
				string lixo;
				ss >> driverB.hCombo;

				getline(fileD, line, ';');
				ss = stringstream(line);
				ss >> driverB.hMax;

				getline(fileD, line);
				ss = stringstream(line);
				ss >> driverB.hRest;
				/*char * cstr = new char[line.length() + 1];
				strcpy_s(cstr, line.c_str());

				char * p = strtok(cstr, ";");

				while (p != 0)
				{
					cout << p << '\n';
					p = strtok(NULL, ";");

					// leixo code: int time;
                getline(ss, ln, '\n'); // o conteúdo das stringstream não é visível, tentámos add a watch com iStreamstring.str();
                ln.erase(ln.begin());
                iStrStream.str(ln);
                while (!iStrStream.good())
                {
                    getline(iStrStream, ln, ',');
                    char * cstr = new char[ln.length() + 1];
                    char *p = strtok(cstr, ",");
                    int time = atoi(p);
                    blineSTCP.timeSpots.push_back(time);
                }
				}*/
				counter = 0;
				driversB.push_back(driverB);
				driver driverB;
			}
		}
	}
	else
		cerr << "error to open drivers file" << endl; // with this output fuction,it can show the message with red colour 
}

int main()
{
	string line;
	ifstream fileDriver("BusDriver.txt"), fileBline("BusLine.txt");
	driver driv;
	bline bus;

	vector<driver> drivers;
	vector<bline> blines;

	readDrivers(fileDriver, drivers);//, driv);
	readBlines(fileBline, blines);

	int pause;
	cin >> pause;
	return 0;
}

/*
//fich.open("..");
while( getline(fich,line))

}
fich.close
}
// tokennalyser, separa cada uma das partes
// strtok(str
//char str[]
//chr *pt


// ler para linhas e é C tradicional e l~e cada tipo de linha.. linha.c.str() converte a string do c++
pt = strtok(str, ';');



streamstring ss;
string linha;
int numero;

do{
	cout << "escreva numero: "; // os carateres tem de ficar a ser lidos... em qq sítio e o buffer de teclado o cin , o buffer de teclado é automáticamente criado
	getline(cin, liha);
	ss.clear(); // uma região de memória pode guardar strings!!
	ss.str(linha);
} while(!(ss>> numero)// limpa a região de memória!!
	// como só leio um número inteiro para preencher aquele valor etc

	int leInteiro( int min, int max)
{
	streamstring ss;
	string linha;
	int numero;

	do
	do
	{
		cout << "Escreva numero:";
		getline(cin, linha);
		ss.clear()

			ss.str(linha);


	} while (!(ss >> numero));
	while (num >> min && num <= max);
	*/
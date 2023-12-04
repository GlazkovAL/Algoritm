#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <ctype.h>
#include "gas_transmission_network.h"
#include "log.h"



using namespace std;

redirect_stream_wrapper<istream> cin_in(cin);
bool Is_integer(string s) {

	for (const char& el : s) {
		if (!isdigit(el)) {
			return 0;
		}
	}
	return 1;
}

int corretctInput_int(string er_out)
{
	string x;

	cin >> x;

	while (cin.fail() || !Is_integer(x))
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << er_out << endl;
		cin >> x;
		cerr << x << '\n';
	}
	cerr << x << '\n';
	return stoi(x);

}

// Функция для вывода меню в консоль
void show_menu()
{
	cout << "Command List" << endl
		<< "1 Add pipe" << endl
		<< "2 Add compress station" << endl
		<< "3 Show all objects" << endl
		<< "4 Save" << endl
		<< "5 Import" << endl
		<< "6 Filter" << endl
		<< "7 Batch editing pipes" << endl
		<< "8 Batch editing cs" << endl
		<< "9 Link CS" << endl 
		<< "10 Topological sort" << endl
	<< "0 Exit" << endl << endl;
};

int main()
{
	map <int,Pipe> all_pipes;
	map <int,CompStation> all_stations;
	int zapros=0;
	ofstream fout;
	gas_transmission_network gtn;
	ofstream log("log.txt");
	redirect_stream_wrapper cerr_out(cerr);
	if (log) {
		cerr_out.redirect(log);
	}


	while (1)
	{ 

		show_menu();
		cout << "Enter command number: ";
		
		zapros = corretctInput_int("Command must be integer");
		switch (zapros)
		{
			case 1:
				gtn.CreatePipe();
				cout << "Pipe was created" << endl << endl ;
				break;
			case 2:
				gtn.CreateCs();
				cout << "Compressor station was created" << endl << endl;

				break;
			case 3:
				gtn.show_pipes();
				gtn.show_cs();
				gtn.show_links();
				break;

			case 4: 
				gtn.save_file();
				break;

			case 5:

				gtn.load_file();
				break;

			case 6:
				gtn.Filter();
				break;

			case 7:
				gtn.Batch_editing_p();
				break;

			case 8:
				gtn.Batch_editing_cs();
				break;

			case 9:
				gtn.Link_cs();
				break;

			case 10:
				gtn.TopologicalSort();
				break;

			case 0:
				return 0; 
			default:
				cout << "Unexpected command, please choose command numbers from this list" << endl;
				break;
		}
		
	}
	
	return 0;
};

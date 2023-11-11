#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <map>
#include "Pipe.h"
#include "CompStation.h"


using namespace std;

ostream& operator << (ostream& out, Pipe p) {
	return out << p.name << endl << p.lenght << endl << p.diam << endl << p.repair << endl;

}

ostream& operator << (ostream& out, CompStation cs) {
	return out << cs.name << endl << cs.workshops << endl << cs.working_workshops << endl << cs.efficiency << endl;

}

double correctInput(double max ,string er_out)
{
	string x;
	bool fl_double1 = 0;
	bool fl_double2 = 0;
	string s1;
	string s2;

	cin >> x;

	


	while (cin.fail() || fl_double2 || fl_double1  || stod(x)<= 0)
	{
		cin.clear();
		cin.ignore(10000000, '\n');
		cout << er_out << endl;
		cin >> x;
		fl_double1 = 0;
		fl_double2 = 0;


		auto pos = x.find(".");
		if (pos != string::npos)
		{	
			 pos = string::npos;
			 s1 = x.substr(0, pos);
			 s2 = x.substr(pos + 1);
			 for (const char& el : s1) {
				 if (!isdigit(el)) {
					 fl_double1 = 1;
					 break;
				 }
			 }
			 for (const char& el : s2) {
				 if (!isdigit(el)) {
					 fl_double2 = 1;
					 break;
				 }
			 }

		}
		else {
			pos = string::npos;
			for (const char& el : x) {
				if (!isdigit(el)) {
					fl_double1 = 1;
					break;
				}
			}

		}


	}

	return stod(x);

}

int corretctInput_int(int max, string er_out)
{
	string x;
	bool fl_int;
	fl_int = 0;
	
	cin >> x;
	for (const char& el : x) {
		if (!isdigit(el)) {
			fl_int = 1;
			break;
		}
	}
	while (cin.fail() || fl_int || stoi(x)<0)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << er_out << endl;
		cin >> x;
		fl_int = 0;
		for (const char& el : x) {
			if (!isdigit(el)) {
				fl_int = 1;
			}
		}

	}

	return stoi(x);

}






// Функция для вывода меню в консоль
void show_menu()
{
	cout << "Command List" << endl
	<< "1 Add pipe" << endl
	<< "2 Add compress station" << endl
	<< "3 Show all objects" << endl
	<< "4 Edit pipe" << endl
	<< "5 Edit compress station" << endl
	<< "6 Save" << endl
	<< "7 Import" << endl
	<< "0 Exit" << endl << endl;
};

// Функция для создания трубы
void createPipe(map <int, Pipe> &all_pipes)
{
	string p_name;
	double p_lenght;
	int p_diam;
	bool p_repair;
	string er_output;

	cout << "Enter pipe name: ";
	getline(cin, p_name);
	getline(cin, p_name);
	cout << "Enter pipe lenght in meters: ";
	p_lenght = correctInput(1. ,"Lenght must be double");
	cout << "Enter pipe diametr in milimeters: ";
	p_diam = corretctInput_int(1, "Diametr must be integer");
	cout << "Enter 0 if pipe is working or another integer if repairing: ";
	p_repair = corretctInput_int(1, "Repairing status must be integer");

	Pipe pipe(p_name,p_lenght,p_diam,p_repair);

	pipe.Push(all_pipes);
	
};

// Функция для создания компрессорной станции
CompStation createCS(map <int, CompStation>& all_stations)
{
	string cs_name;
	int cs_workshops;
	int cs_working_workshops;
	double cs_efficiency;

	cout << "Enter comressor station name: ";
	getline(cin, cs_name);
	getline(cin, cs_name);
	cout << "Enter number of workshops: ";
	cs_workshops = corretctInput_int(1, "Workshops quantity must be integer");
	cout << "Enter number of  working workshops: ";
	cs_working_workshops = corretctInput_int(1, "Working workshops quantity must be integer");
	while (cs_working_workshops > cs_workshops) 
	{
		if (cs_working_workshops > cs_workshops)
		{
			cout << "nubmer of working worshops must be less then number of workshops" << endl;
			cout << "Enter number of  working workshops: ";
			cs_working_workshops = corretctInput_int(1, "Working workshops quantity must be integer");
		};
	};
	cout << "Enter compressor station efficiency: ";
	cs_efficiency = correctInput(1., "Efficiency must be double");


	CompStation cs(cs_name, cs_workshops, cs_working_workshops, cs_efficiency );
	cs.Push(all_stations);
};

// Функция для показа всех труб
void show_pipes( map <int, Pipe> all_p)
{
	cout << "Pipes: " << endl;

	for ( auto& pipe : all_p) {
		pipe.second.Print(); 
	}

	
	cout << endl;
		
};

// Функция для показа всех компрессорных ствнций
void show_cs(map <int, CompStation> all_cs)
{

	cout << "Compressor stations: " << endl;

	for (auto& cs : all_cs) {
		cs.second.Print();
	}

	cout << endl;

};

//Функция редактирования трубы
void edit_pipe(map <int, Pipe>& all_pipes)
{
	int id_edit;

	show_pipes(all_pipes);
	cout << "Enter pipe id from the list above:" ;
	id_edit= corretctInput_int(1, "Id must be integer");
	
	if (all_pipes.find(id_edit) != all_pipes.end()) {
		all_pipes[id_edit].repair = !all_pipes[id_edit].repair;
	}
	else 
	{
		cout << "Wrong pipe id" << endl;
	}

}

//Функция редактирования КС
void edit_cs(map <int, CompStation>& all_cs)
{
	int id_edit;;
	int cs_working_workshops;
	bool searched = false;

	show_cs(all_cs);
	cout << "Enter cs id from the list above:";
	id_edit = corretctInput_int(1, "Id must be integer");
	if (all_cs.find(id_edit)!= all_cs.end()) {
		
		CompStation cs = all_cs[id_edit];
		cout << "Enter 0 if you want to repair workshop or another positive integer to add working workshop: ";
		cs_working_workshops = corretctInput_int(1, "Command must be integer");
		if(cs.working_workshops+1 > cs.workshops && cs_working_workshops)
		{
			cout << "nubmer of working worshops must be less then number of workshops" << endl;
				
		}
		else if (cs.working_workshops - 1 < 0 && !cs_working_workshops) {
			cs.working_workshops++;
			cout << "Number of working workshops must be >0" << endl << endl;
		}
		else if (cs.working_workshops + 1 <= cs.workshops && cs_working_workshops) {
			cs.working_workshops++;
			cout << "Compressor station has been edited" << endl << endl;
		}
		else {
			cs.working_workshops--;
			cout << "Compressor station has been edited" << endl << endl;
		}
		
	}
	else
	{
		cout << "Wrong compressor station id" << endl;
	}

}

// Функция для сохранения объектов в файл
void save_file( const map <int, Pipe>& all_p, const map <int, CompStation>& all_cs)
{
	ofstream out;
	string f_name;
	if (all_p.size() > 0 && all_cs.size() > 0) {
		cout << "Enter file name: ";
		cin >> f_name;
		out.open("saves/" + f_name + ".txt");
		if (out.is_open() && all_p.size() > 0 && all_cs.size() > 0) {
			out << all_p.size();
			for (auto& pipe : all_p) {
				out << pipe.second;
			}
			out << all_cs.size();
			for (auto& cs : all_cs) {
				out << cs.second;
			}

		}
		out.close();
		cout << "File has been saved " << endl;
	}
	else {
		cout << "There are now objects, create some objects before saving" << endl;
	};

	

};

//Функция для импортирования данных из файла
void LoadFile(map <int, Pipe>& all_p, map <int, CompStation>& all_cs)
{
	ifstream fin;
	string path = "saves";
	vector <filesystem::path> file_names;
	bool searched = false;
	string searshing_file;
	int number;

	for (const auto& entry : filesystem::directory_iterator(path))
	{
		file_names.push_back(entry.path().filename());
		cout << entry.path().filename() << endl;
	}

	cout << "Enter file name: ";
	cin >> searshing_file;

	for (filesystem::path& fname : file_names) {
		if (fname == searshing_file)
		{
			searched = true;

			fin.open("saves/" + searshing_file);
			if (fin.is_open()) {
				cout << "start importing" << endl;
				fin >> number;
				for (int i = 0; i < number; i++) {
					string p_name;
					double p_lenght;
					int p_diam;
					bool p_repair;

					fin >> p_name >> p_lenght >> p_diam >> p_repair;
					Pipe p(p_name, p_lenght, p_diam, p_repair);
					p.Push(all_p);
				}
				fin >> number;
				for (int i = 0; i < number; i++) {
					string cs_name;
					int cs_workshops;
					int cs_working_workshops;
					double cs_efficiency;

					fin >> cs_name >> cs_workshops >> cs_working_workshops >> cs_efficiency;
					CompStation cs(cs_name, cs_workshops, cs_working_workshops, cs_efficiency);
					cs.Push(all_cs);
				}
				cout << "File has been imported" << endl;
			}
			else {
				cout << "ERROR" << endl;
			}
			fin.close();
		};
	}
	if (!searched)
	{
		cout << "Wrong file name" << endl;
	}

}

int main()
{
	map <int,Pipe> all_pipes;
	map <int,CompStation> all_stations;
	int zapros=0;
	int cs_id = 0;
	

	while (1)
	{
		show_menu();
		cout << "Enter command number: ";
		zapros = corretctInput_int(1, "Unexpected command, command number must be integer");
	

		switch (zapros)
		{
			case 1:
				createPipe(all_pipes);
				cout << "Pipe was created" << endl << endl ;
				break;
			case 2:
				createCS(all_stations);
				cout << "Compressor station was created" << endl << endl;
				cs_id++;

				break;
			case 3:
				show_pipes(all_pipes);
				show_cs(all_stations);
				break;
			case 4:
				edit_pipe(all_pipes);
				break;
			case 5:
				edit_cs(all_stations);
				break;
			case 6: 
				save_file(all_pipes, all_stations);
				break;

			case 7:

				LoadFile(all_pipes, all_stations);
				break;

			case 0:
				return 0;
			default:
				cout << "Unexpected command, please choose command numbers from this list";
				break;
		}
		
	}
	
	return 0;
};

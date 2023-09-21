#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>


using namespace std;

// структура для Трубы
struct Pipe
{
	int id;
	string name;
	double lenght;
	int diam;
	bool repair;

};

// структура для Компрессорной станции
struct CompStation
{
	int id;
	string name;
	int workshops;
	int working_workshops;
	double efficiency;

};

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
Pipe createPipe(int p_id)
{
	string p_name;
	double p_lenght;
	int p_diam;
	bool p_repair;

	cout << "Enter pipe name: ";
	cin >> p_name;
	cout << "Enter pipe lenght in meters: ";
	cin >> p_lenght;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Lenght muxt be double";
		cin >> p_lenght;
	}
	cout << "Enter pipe diametr in milimeters: ";
	cin >> p_diam;
	cout << "Enter 1 if pipe is on repairing or 0 if pipe is working: ";
	cin >> p_repair;


	return { p_id, p_name, p_lenght, p_diam, p_repair };
};

// Функция для создания компрессорной станции
CompStation createCS(int cs_id)
{
	string cs_name;
	int cs_workshops;
	int cs_working_workshops;
	double cs_efficiency;

	cout << "Enter comressor station name: ";
	cin >> cs_name;
	cout << "Enter number of workshops: ";
	cin >> cs_workshops;
	cout << "Enter number of  working workshops: ";
	cin >> cs_working_workshops;
	while (cs_working_workshops > cs_workshops) 
	{
		if (cs_working_workshops > cs_workshops)
		{
			cout << "nubmer of working worshops must be less then number of workshops" << endl;
			cout << "Enter number of  working workshops: ";
			cin >> cs_working_workshops;
		};
	};
	cout << "Enter compressor station efficiency: ";
	cin >> cs_efficiency;


	return { cs_id ,cs_name, cs_workshops, cs_working_workshops, cs_efficiency };
};

// Функция для показа всех труб
void show_pipes(vector <Pipe> all_p)
{
	string work;
	cout << "Pipes: " << endl;

	for (const Pipe& pipe : all_p) {
		if (pipe.repair) { work = "repairing" ; }
		else { work = "working"; };
		cout << pipe.id << " " << pipe.name << " " << pipe.lenght << " " << pipe.diam << " " << work << endl;
	}

	
	cout << endl;
		
};

// Функция для показа всех компрессорных ствнций
void show_cs( vector <CompStation> all_cs)
{

	cout << "Compressor stations: " << endl;

	for (const CompStation& cs : all_cs) {
		cout << cs.id << " " << cs.name << " " << cs.workshops << " " << cs.working_workshops << " " << cs.efficiency << endl;
	}

	cout << endl;

};

//Функция редактирования трубы
void edit_pipe(vector <Pipe>& all_pipes)
{
	string name_edit;
	int working_status;
	bool searched = false;

	show_pipes(all_pipes);
	cout << "Enter pipe name from the list above:" ;
	cin >> name_edit;
	for (Pipe& pipe : all_pipes) {
		if (pipe.name == name_edit)
		{
			searched = true;
			cout << "Enter 1 if pipe is on repairing or 0 if pipe is working: " ;
			cin >> working_status;
			pipe.repair = working_status;
			cout << "Pipe has been edited" << endl;
			break;
		};
	}
	if (!searched) 
	{
		cout << "Wrong pipe name" << endl;
	}

}

// Функция для сохранения объектов в файл
void save_file(vector <Pipe> all_pipes, vector <CompStation> all_cs)
{
	ofstream out;
	string f_name;
	cout << "Enter file name: ";
	cin >> f_name;
	out.open("saves/"+ f_name + ".txt");
	if (out.is_open()) {
		for (const Pipe& pipe : all_pipes) {
			out << pipe.id << endl << pipe.name << endl << pipe.lenght << endl << pipe.diam << endl << pipe.repair << endl;
		}
		out << "CStation";

		for (const CompStation& cs : all_cs) {
			out << cs.id << endl << cs.name << endl << cs.workshops << endl << cs.working_workshops << endl << cs.efficiency << endl;
		}
		out << "END";
	}
	out.close();

	cout << "File has been saved " << endl;
};


void LoadFile() 
{
	string path = "saves";

	for (const auto& entry : filesystem::directory_iterator(path))
		cout << entry.path().filename() << endl; 

}

int main()
{
	vector <Pipe> all_pipes;
	vector <CompStation> all_stations;
	int zapros=0;
	int pipe_id=0;
	int cs_id = 0;
	

	while (1)
	{
		show_menu();
		cout << "Enter command number: ";
		cin >> zapros;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Unexpected command, please choose command numbers from this list" << endl;
			show_menu();
			cin >> zapros;
		} 

	

		switch (zapros)
		{
			case 1:
				all_pipes.resize(pipe_id+1);
				all_pipes[pipe_id]=createPipe(pipe_id);
				cout << "Pipe was created" << endl << endl ;
				pipe_id++;
				break;
			case 2:
				all_stations.resize(cs_id + 1);
				all_stations[cs_id] = createCS(cs_id);
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
			case 6: 
				save_file(all_pipes, all_stations);
				break;

			case 7:

				break;

			case 0:
				return 0;
			default:
				cout << "Unexpected command, please choose command numbers from this list";
				show_menu();
				break;
		}
		
	}
	
	return 0;
};

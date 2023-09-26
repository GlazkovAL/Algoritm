#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>


using namespace std;
template <typename T>

T corretctInput( T max ,string er_out)
{
	T x;
	cin >> x;

	while (cin.fail() || x <= 0)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << er_out << endl;
		cin >> x;
	}
	return x;

}


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
	string er_output;

	cout << "Enter pipe name: ";
	getline(cin, p_name);
	getline(cin, p_name);
	cout << "Enter pipe lenght in meters: ";
	p_lenght = corretctInput(1.,"Lenght must be double");
	cout << "Enter pipe diametr in milimeters: ";
	p_diam = corretctInput(1, "Diametr must be integer");
	cout << "Enter 1 if pipe is on repairing or 0 if pipe is working: ";
	p_repair = corretctInput(1, "Repairing status must be integer");


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
	getline(cin, cs_name);
	getline(cin, cs_name);
	cout << "Enter number of workshops: ";
	cs_workshops = corretctInput(1, "Workshops quantity must be integer");
	cout << "Enter number of  working workshops: ";
	cs_working_workshops = corretctInput(1, "Working workshops quantity must be integer");
	while (cs_working_workshops > cs_workshops) 
	{
		if (cs_working_workshops > cs_workshops)
		{
			cout << "nubmer of working worshops must be less then number of workshops" << endl;
			cout << "Enter number of  working workshops: ";
			cs_working_workshops = corretctInput(1, "Working workshops quantity must be integer");
		};
	};
	cout << "Enter compressor station efficiency: ";
	cs_efficiency = corretctInput(1., "Efficiency must be double");


	return { cs_id ,cs_name, cs_workshops, cs_working_workshops, cs_efficiency };
};

// Функция для показа всех труб
void show_pipes( const vector <Pipe>& all_p)
{
	string work;
	cout << "Pipes: " << endl;

	for (const Pipe& pipe : all_p) {
		if (pipe.repair) { work = "repairing" ; }
		else { work = "working"; };
		cout << pipe.id << " Name: " << pipe.name << " Lenght: " << pipe.lenght << " Diametr: " << pipe.diam << " Working status: " << work << endl;
	}

	
	cout << endl;
		
};

// Функция для показа всех компрессорных ствнций
void show_cs( const vector <CompStation>& all_cs)
{

	cout << "Compressor stations: " << endl;

	for (const CompStation& cs : all_cs) {
		cout << cs.id << " Name: " << cs.name << " Workshops: " << cs.workshops << " Working workshops: " << cs.working_workshops << " Efficiency: " << cs.efficiency << endl;
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
	getline(cin, name_edit);
	getline(cin, name_edit);
	for (Pipe& pipe : all_pipes) {
		if (pipe.name == name_edit)
		{
			searched = true;
			pipe.repair = !pipe.repair;
			break;
		};
	}
	if (!searched) 
	{
		cout << "Wrong pipe name" << endl;
	}

}

//Функция редактирования КС
void edit_cs(vector <CompStation>& all_cs)
{
	string name_edit;
	int cs_working_workshops;
	bool searched = false;

	show_cs(all_cs);
	cout << "Enter pipe name from the list above:";
	getline(cin, name_edit);
	getline(cin, name_edit);
	for (CompStation& cs : all_cs) {
		if (cs.name == name_edit)
		{
			searched = true;
			cout << "Enter 0 if you want to repair workshop or another positive integer to add working workshop: ";
			cs_working_workshops = corretctInput(1, "Command must be integer");
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
			break;
		};
	}
	if (!searched)
	{
		cout << "Wrong compressor station name" << endl;
	}

}

// Функция для сохранения объектов в файл
void save_file( const vector <Pipe>& all_pipes, const vector <CompStation>& all_cs)
{
	ofstream out;
	string f_name;
	if (all_pipes.size() > 0 && all_cs.size() > 0) {
		cout << "Enter file name: ";
		cin >> f_name;
		out.open("saves/" + f_name + ".txt");
		if (out.is_open() && all_pipes.size() > 0 && all_cs.size() > 0) {
			//out << "PIPE" << endl;

			for (const Pipe& pipe : all_pipes) {
				out << pipe.id << endl << pipe.name << endl << pipe.lenght << endl << pipe.diam << endl << pipe.repair << endl;
			}

			out << "999" << endl;

			for (const CompStation& cs : all_cs) {
				out << cs.id << endl << cs.name << endl << cs.workshops << endl << cs.working_workshops << endl << cs.efficiency << endl;
			}

			out << "888";

		}
		out.close();
		cout << "File has been saved " << endl;
	}
	else {
		cout << "There are now objects, create some objects before saving" << endl;
	};

	

};

//Функция для импортирования данных из файла
void LoadFile(vector <Pipe>& all_pipes, vector <CompStation>& all_cs)
{
	ifstream fin;
	string path = "saves";
	vector <filesystem::path> file_names;
	bool searched = false;
	string searshing_file;
	int load_switch;

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
				fin >> load_switch;
				while (load_switch != 999) {

					Pipe p;
					p.id = load_switch;
					getline(fin,p.name);
					getline(fin, p.name);
					fin >> p.lenght;
					fin >> p.diam;
					fin >> p.repair;
					fin >> load_switch;
					all_pipes.push_back(p);
				}

				fin >> load_switch;

				while (load_switch != 888) {

					CompStation cs;
					cs.id = load_switch;
					getline(fin, cs.name);
					getline(fin, cs.name);
					fin >> cs.workshops;
					fin >> cs.working_workshops;
					fin >> cs.efficiency;
					fin >> load_switch;
					all_cs.push_back(cs);
				}


			}
			else {
				cout << "ERROR" << endl;
			}
			fin.close();
			cout << "File has been imported"<< endl;
		};
	}
	if (!searched)
	{
		cout << "Wrong file name" << endl;
	}

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
		zapros = corretctInput(1, "Unexpected command, command number must be integer");
	

		switch (zapros)
		{
			case 1:
				all_pipes.push_back(createPipe(pipe_id));
				cout << "Pipe was created" << endl << endl ;
				pipe_id++;
				break;
			case 2:
				all_stations.push_back(createCS(cs_id));
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

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
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

bool Is_int(string s) {

	for (const char& el : s) {
		if (!isdigit(el)) {
			return 0;
		}
	}
	return 1;
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

	
	cin >> x;
	
	while (cin.fail() || !Is_int(x) || stoi(x)<0)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << er_out << endl;
		cin >> x;
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
	<< "8 Remove pipe" << endl
	<< "9 Remove cs" << endl
	<< "10 Filter" << endl
	<< "11 Batch editing pipes" << endl
	<< "12 Batch editing cs" << endl
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

	pipe.Push(all_pipes, pipe);
	
};

// Функция для создания компрессорной станции
void createCS(map <int, CompStation>& all_stations)
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
	cs.Push(all_stations, cs);
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
			all_cs[id_edit].working_workshops++;
			cout << "Number of working workshops must be >0" << endl << endl;
		}
		else if (cs.working_workshops + 1 <= cs.workshops && cs_working_workshops) {
			all_cs[id_edit].working_workshops++;
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
			out << all_p.size()<< endl;
			for (auto& pipe : all_p) {
				out << pipe.second;
			}
			out << all_cs.size() << endl ;
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
					p.Push(all_p, p);
				}
				fin >> number;
				for (int i = 0; i < number; i++) {
					string cs_name;
					int cs_workshops;
					int cs_working_workshops;
					double cs_efficiency;

					fin >> cs_name >> cs_workshops >> cs_working_workshops >> cs_efficiency;
					CompStation cs(cs_name, cs_workshops, cs_working_workshops, cs_efficiency);
					cs.Push(all_cs, cs);
				}
				cout << "File has been imported" << endl << endl;
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

void Remove_p(map <int, Pipe>& all_p) {
	int id_edit;

	show_pipes(all_p);
	cout << "Enter pipe id from the list above:";
	id_edit = corretctInput_int(1, "Id must be integer");

	if (all_p.find(id_edit) != all_p.end()) {
		all_p.erase(id_edit);
	}
	else
	{
		cout << "Wrong pipe id" << endl;
	}

}
void Remove_cs(map <int, CompStation>& all_cs) {
	int id_edit;

	show_cs(all_cs);
	cout << "Enter cs id from the list above:";
	id_edit = corretctInput_int(1, "Id must be integer");

	if (all_cs.find(id_edit) != all_cs.end()) {
		all_cs.erase(id_edit);
	}
	else
	{
		cout << "Wrong cs id" << endl;
	}
}

void Edit_or_remove_p(map <int, Pipe>& all_p, vector <int> editing_id) {
	string fun;
	cout << "Enter remove(r) or change repairing status(c) ";
	cin >> fun;
	if (fun == "r") {
		for (int id : editing_id) {
			all_p.erase(id);
		}
		cout << "Pipes has been removed" << endl << endl;
	}
	else if (fun == "c") {
		for (int id : editing_id) {
			all_p[id].repair = !all_p[id].repair;
		}
		cout << "Pipes has been changed" << endl << endl;
	}
	else {
		cout << "Wrong command";
	}
}

void Edit_or_remove_cs(map <int, CompStation>& all_cs, vector <int> editing_id) {
	string fun;
	cout << "Enter remove(r) , add (+) or reduce(-) working workshop ";
	cin >> fun;
	if (fun == "r") {
		for (int id : editing_id) {
			all_cs.erase(id);
		}
		cout << "Pipes has been removed" << endl << endl;
	}
	else if (fun == "+") {
		for (int id : editing_id) {
			if (all_cs[id].working_workshops + 1 <= all_cs[id].workshops) {
				all_cs[id].working_workshops++;
			}
		}
		cout << "Cs has been changed" << endl << endl;
	}
	else if (fun == "-") {
		for (int id : editing_id) {
			if (all_cs[id].working_workshops - 1 >0) {
				all_cs[id].working_workshops--;
			}
		}
		cout << "Cs has been changed" << endl << endl;
	}
	else {
		cout << "Wrong command";
	}
}

void Filter_pipes_name(map <int, Pipe>& all_p) {
	map <int, Pipe> filter_p;
	string name_part;
	vector <int> editing_id;

	cout << "Enter name for filter: ";
	cin >> name_part;

	for (auto& pipe : all_p) {
		if (pipe.second.name.find(name_part) != string::npos) {
			pipe.second.Push(filter_p, pipe.second);
			editing_id.push_back(pipe.first);
		}
	}
	if (filter_p.size() == 0) {
		cout << "There are no pipes with such pipe name" << endl;
	}
	else {
		show_pipes(filter_p);
		cout << endl;
	}

	cout << "Enter yes if you want to edit these pipes ";
	cin >> name_part;
	if (name_part == "yes") {
		Edit_or_remove_p(all_p, editing_id);
	}
}

void Filter_pipes_repair(map <int, Pipe>& all_p) {
	map <int, Pipe> filter_p;
	string repairing_status;
	vector <int> editing_id;

	cout << "Enter you want filter repairing(enter r) or working(enter w) pipes: ";
	cin >> repairing_status;

	while (1) {
		if (repairing_status == "r") {
			for (auto& pipe : all_p) {
				if (pipe.second.repair) {
					pipe.second.Push(filter_p, pipe.second);
					editing_id.push_back(pipe.first);
				}
			}
			if (filter_p.size() == 0) {
				cout << "There are no repairing pipes " << endl;
				break;
			}
			else {
				show_pipes(filter_p);
				cout << endl;
				break;
			}
		}
		else if(repairing_status == "w"){
			for (auto& pipe : all_p) {
				if (!pipe.second.repair) {
					pipe.second.Push(filter_p, pipe.second);
					editing_id.push_back(pipe.first);
				}
			}
			if (filter_p.size() == 0) {
				cout << "There are no working pipes " << endl;
				break;
			}
			else {
				show_pipes(filter_p);
				cout << endl;
				break;
			}
		}
		else {
			cout << "Wrong command" << endl;
			cout << "Enter you want filter repairing(enter r) or working(enter w) pipes: ";
			cin >> repairing_status;
		}
	}
	cout << "Enter yes if you want to edit these pipes ";
	cin >> repairing_status;
	if (repairing_status == "yes") {
		Edit_or_remove_p(all_p, editing_id);
	}
}

void Filter_cs_name(map <int, CompStation>& all_cs) {
	map <int, CompStation> filter_cs;
	string name_part;
	vector <int> editing_id;

	cout << "Enter name for filter: ";
	cin >> name_part;

	for (auto& cs : all_cs) {
		if (cs.second.name.find(name_part) != string::npos) {
			cs.second.Push(filter_cs, cs.second);
			editing_id.push_back(cs.first);
		}
	}
	if (filter_cs.size() == 0) {
		cout << "There are no cs with such cs name" << endl;
	}
	else {
		show_cs(filter_cs);
		cout << endl;
	}

	cout << "Enter yes if you want to edit these cs ";
	cin >> name_part;
	if (name_part == "yes") {
		Edit_or_remove_cs(all_cs, editing_id);
	}

}

void Filter_cs_percent(map <int, CompStation>& all_cs) {
	map <int, CompStation> filter_cs;
	string func;
	int per;
	vector <int> editing_id;

	cout << "Enter the condition: equal(e) less(l) or more(r) ";
	cin >> func;
	cout << "Enter percent:  ";
	per = corretctInput_int(1,"Percent must be integer");

	if (func == "e") {
		for (auto& cs : all_cs) {
			if ((cs.second.working_workshops*100)/cs.second.workshops == per) {
				cs.second.Push(filter_cs, cs.second);
				editing_id.push_back(cs.first);
			}
		}
		if (filter_cs.size() == 0) {
			cout << "There are no such cs" << endl;
		}
		else {
			show_cs(filter_cs);
			cout << endl;
		}
	}
	else if (func == "l") {
		for (auto& cs : all_cs) {
			if ((cs.second.working_workshops * 100) / cs.second.workshops < per) {
				cs.second.Push(filter_cs, cs.second);
				editing_id.push_back(cs.first);
			}
		}
		if (filter_cs.size() == 0) {
			cout << "There are no such cs" << endl;
		}
		else {
			show_cs(filter_cs);
			cout << endl;
		}

	}
	else if (func == "m") {
		for (auto& cs : all_cs) {
			if ((cs.second.working_workshops * 100) / cs.second.workshops > per) {
				cs.second.Push(filter_cs, cs.second);
				editing_id.push_back(cs.first);
			}
		}
		if (filter_cs.size() == 0) {
			cout << "There are no such cs" << endl;
		}
		else {
			show_cs(filter_cs);
			cout << endl;
		}
	}
	else {
		cout << "Wrong condition" << endl;
	}
	cout << "Enter yes if you want to edit these cs ";
	cin >> func;
	if (func == "yes") {
		Edit_or_remove_cs(all_cs, editing_id);
	}

}

void Filter(map <int, Pipe>& all_p, map <int, CompStation>& all_cs) {
	int filter_num;

	cout << "1 Filter pipes by name" << endl
		<< "2 Filter pipes by repairing status" << endl
		<< "3 Filter cs by name" << endl
		<< "4 Filter cs by % of working workshops" << endl << endl;

	cout << "Enter command number: ";
	filter_num = corretctInput_int(1, "Unexpected command, command number must be integer");

	switch (filter_num) {
	case 1:
		Filter_pipes_name(all_p);
		break;
	case 2:
		Filter_pipes_repair(all_p);
		break;
	case 3:
		Filter_cs_name(all_cs);
		break;
	case 4:
		Filter_cs_percent(all_cs);
		break;
	
	default:
		cout << "Unexpected command";
		break;

	}
}


void Batch_editing_p(map <int, Pipe>& all_p) {
	string line_id;
	char *str_id;
	int id_p;
	vector <int> editing_id;
	stringstream ss;

	show_pipes(all_p);
	cout << "Enter id of pipes: ";
	cin.ignore();
	getline(cin, line_id);
	char *l_id= _strdup(line_id.c_str());
	 #pragma warning(suppress : 4996)
	str_id = strtok(l_id, " , ");

	while (str_id) {
		if (Is_int(str_id)) {
			id_p = stoi(str_id);
			if (all_p.find(id_p) != all_p.end()) {
				editing_id.push_back(id_p);


			}
			else {
				cout << "No such id" << endl;
				editing_id = {};
				break;
			}
		}
		else {
			cout << "Id must be integer" << endl;
			editing_id = {};
			break;
		}
		#pragma warning(suppress : 4996)
		str_id = strtok(0, " , ");
	}
	if (editing_id.size() != 0) {
		Edit_or_remove_p(all_p, editing_id);
	}
}

void Batch_editing_cs(map <int, CompStation>& all_cs) {
	string line_id;
	char* str_id;
	int id_cs;
	vector <int> editing_id;
	stringstream ss;

	show_cs(all_cs);
	cout << "Enter id of cs: ";
	cin.ignore();
	getline(cin, line_id);
	char* l_id = _strdup(line_id.c_str());
#pragma warning(suppress : 4996)
	str_id = strtok(l_id, " , ");

	while (str_id) {
		if (Is_int(str_id)) {
			id_cs = stoi(str_id);
			if (all_cs.find(id_cs) != all_cs.end()) {
				editing_id.push_back(id_cs);


			}
			else {
				cout << "No such id" << endl;
				editing_id = {};
				break;
			}
		}
		else {
			cout << "Id must be integer" << endl;
			editing_id = {};
			break;
		}
#pragma warning(suppress : 4996)
		str_id = strtok(0, " , ");
	}
	if (editing_id.size() != 0) {
		Edit_or_remove_cs(all_cs, editing_id);
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
			case 8:
				Remove_p(all_pipes);
				break;

			case 9:
				Remove_cs(all_stations);
				break;

			case 10:
				Filter(all_pipes, all_stations);
				break;

			case 11:
				Batch_editing_p(all_pipes);
				break;

			case 12:
				Batch_editing_cs(all_stations);
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

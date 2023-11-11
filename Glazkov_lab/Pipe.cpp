#include "Pipe.h"
#include <iostream>

using namespace std;

void Pipe::Print() {
	string work;

	if (repair) { work = "repairing"; }
	else { work = "working"; };
	cout << id << " Name: " << name << " Lenght: " << lenght << " Diametr: " << diam << " Working status: " << work << endl;

}

void Pipe::Push(std::map<int, Pipe>& myMap)
{
	myMap.emplace(id, this);
}


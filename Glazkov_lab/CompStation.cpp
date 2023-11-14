#include "CompStation.h"
#include <iostream>
using namespace std;


void CompStation::Print()
{
	cout << id << " Name: " << name << " Workshops: " << workshops << " Working workshops: " << working_workshops << " Efficiency: " << efficiency << endl;
}

void CompStation::Push(std::map<int, CompStation>& myMap, CompStation cs)
{
	myMap.emplace(id, cs);
}

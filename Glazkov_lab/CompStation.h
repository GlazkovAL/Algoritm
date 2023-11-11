#pragma once
#include <string>
#include <map>
class CompStation
{	
	static inline int id{};
public:
	std::string name;
	int workshops;
	int working_workshops;
	double efficiency;

	CompStation(std::string cs_name, int cs_workshops, int cs_working_workshops, double cs_efficiency) {
		id++;
		name = cs_name;
		workshops = cs_workshops;
		working_workshops = cs_working_workshops;
		efficiency = cs_efficiency;
	}
	void Print();
	void Push(std::map <int, CompStation>& myMap);
};


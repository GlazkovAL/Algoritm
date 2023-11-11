#pragma once

#include <map>
#include <string>

class Pipe
{
	static inline int id{};
public:
	std::string name;
	double lenght;
	int diam;
	bool repair;

	Pipe(std::string p_name, double p_lenght, int p_diam, bool p_repair) {
		++id;
		name = p_name;
		lenght = p_lenght;
		diam = p_diam;
		repair = p_repair;

	}

	void Print();
	void Push(std::map <int, Pipe>& myMap);
};


#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>

using namespace std;

void ReadCSV(char* csvName)
{
	ifstream fin;
	string name = csvName;
	name += ".csv";
	fin.open(name, ios::in);

}
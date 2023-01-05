#include <fstream>
#include <iostream>
using namespace std;

class Data
{
public:
	virtual void create(char* name) = 0;
	virtual void write(char* name, string s) = 0;
};

class CommandData : public Data
{
public:
	void create(char* name) override
	{
		ofstream f;
		//string commandName = name;
		//commandName += ".txt";
		//f.open(commandName.c_str());
		f.open(name);
	}
	void write(char* name, string s) override
	{
		ofstream f;
		//string commandName = name;
		//commandName += ".txt";
		//f.open(commandName.c_str());
		f.open(name);
		f << s << endl;
	}
};

class DataImport : public Data
{
public:
	void create(char* name) override
	{
		ofstream f;
		string nameCSV = name;
		nameCSV += ".csv";
		f.open(nameCSV.c_str());
		//f.open(name);
	}
	void write(char* name, string s) override
	{
		ofstream f;
		string nameCSV = name;
		nameCSV += ".csv";
		f.open(nameCSV.c_str());
		//f.open(name);
		f << s << endl;
	}
};
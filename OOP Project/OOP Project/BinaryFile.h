#define _CRT_SECURE_NO_WARNINGS
#include <map>
#include <set>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class BinaryFile
{
private:
	char* fileName;
	char* info;
public:
	void fileBinaryCreate(char* tableName, char* tableInfo);
	void checkCSV(char* csvName, int& rez);
	void fileBinaryDisplay(char* tableName, map<string, multiset<int>> mapInt, map<string, multiset<float>> mapFloat, map<string, multiset<string>> mapString);
	//void fileBinaryInsert(char* tableName, char* values, map<string, multiset<int>> mapInt, map<string, multiset<float>> mapFloat, map<string, multiset<string>> mapString);
	//void deserialization(char* tableName);
	void display(char* tableName);
	void importCSV(char* tableName, char* csvName, int& rez)

	{
		ifstream fCSV;
		rez = 1;

		string text;
		string name = csvName;
		name += ".csv";
		string newTableName = tableName;
		newTableName += ".bin";
		ofstream fTXT;
		fTXT.open(newTableName, ios::out | ios::app | ios::binary);
		fCSV.open(name, ios::in);
		while (!fCSV.eof())
		{
			getline(fCSV, text);
			(fCSV, text);
			fTXT << text << " ";
		}
	};
};
void checkCSV(char* csvName, int& rez);


class BinaryFileOut : public BinaryFile
{
public:
	void fileBinaryInsert(char* tableName, char* values, map<string, multiset<int>> mapInt, map<string, multiset<float>> mapFloat, map<string, multiset<string>> mapString);
};
#include "BinaryFile.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
using namespace std;

void BinaryFile::fileBinaryDisplay(char* tableName, map<string, multiset<int>> mapInt, map<string, multiset<float>> mapFloat, map<string, multiset<string>> mapString)
{
	string binaryName = tableName;
	binaryName += ".bin";
	//fstream file(binaryName, ios::binary);
	ofstream file(binaryName, ios::trunc | ios::binary);
	for (map<string, multiset<int>>::iterator itI = mapInt.begin(); itI != mapInt.end(); itI++)
		for (multiset<int>::iterator iti = itI->second.begin(); iti != itI->second.end(); iti++)
			file << *iti << " ";
	for (map<string, multiset<float>>::iterator itF = mapFloat.begin(); itF != mapFloat.end(); itF++)
		for (multiset<float>::iterator itf = itF->second.begin(); itf != itF->second.end(); itf++)
			file << *itf << " ";
	for (map<string, multiset<string>>::iterator itS = mapString.begin(); itS != mapString.end(); itS++)
		for (multiset<string>::iterator its = itS->second.begin(); its != itS->second.end(); its++)
			file << *its << " ";
	file.close();
}

void BinaryFile::display(char* tableName)
{
	string binaryName = tableName;
	binaryName += ".bin";
	ifstream file;
	file.open(tableName, ios::binary | ios::in);
	ofstream displayFile;
	displayFile.open("display.txt");
	int buffer[2];
	while (file.read((char*)&buffer, sizeof(buffer)))
	{
		displayFile << buffer;
		//displayFile.write((char*)&buffer, sizeof(buffer));
	}
	//displayFile << binaryName;
	file.close();
	displayFile.close();
}

void BinaryFile::fileBinaryCreate(char* tableName, char* tabelInfo)
{
	string binaryName = tableName;
	binaryName += ".bin";
	ofstream g(binaryName, ios::binary);
	g.close();
}

void BinaryFileOut::fileBinaryInsert(char* tableName, char* values, map<string, multiset<int>> mapInt, map<string, multiset<float>> mapFloat, map<string, multiset<string>> mapString)
{
	string binaryName = tableName;
	binaryName += ".bin";
	ofstream file(binaryName, ios::trunc | ios::binary);
	for (map<string, multiset<int>>::iterator itI = mapInt.begin(); itI != mapInt.end(); itI++)
		for (multiset<int>::iterator iti = itI->second.begin(); iti != itI->second.end(); iti++)
			file << *iti << " ";
	for (map<string, multiset<float>>::iterator itF = mapFloat.begin(); itF != mapFloat.end(); itF++)
		for (multiset<float>::iterator itf = itF->second.begin(); itf != itF->second.end(); itf++)
			file << *itf << " ";
	for (map<string, multiset<string>>::iterator itS = mapString.begin(); itS != mapString.end(); itS++)
		for (multiset<string>::iterator its = itS->second.begin(); its != itS->second.end(); its++)
			file << *its << " ";
}

void BinaryFile::importCSV(char* tableName, char* csvName, int& rez)
{
	ifstream fCSV;
	rez = 1;

	string text;
	string name = csvName;
	name += ".csv";
	string tableName = tableName;
	tableName += ".bin";
	ofstream fTXT;
	fTXT.open(tableName, ios::out | ios::app | ios::binary);
	fCSV.open(name, ios::in);
	while (!fCSV.eof())
	{
		//fCSV >> text;
		getline(fCSV, text);
		fTXT << text << " ";
		//cout << text << " ";
	}




	/*fin.open(name, ios::in);
	vector<string> row;
	string line, word, temp;
	ofstream myFile;
	myFile.open("inserabil.txt");

	while (fin >> temp)
	{

		row.clear();
		getline(fin, line);
		stringstream s(line);
		while (getline(s, word, ','))
		{
			myFile << word;
			row.push_back(word);
			rez = 1;
		}

	}

	string binaryName = tableName;
	binaryName += ".bin";
	ofstream file(binaryName, ios::app | ios::binary);
	file.seekp(0, ios::end);
	file.write((char*)&row[0], row.size() + 1);*/
}

void BinaryFile::checkCSV(char* csvName, int& rez)
{
	ifstream fCSV;
	string name = csvName;
	name += ".csv";
	fCSV.open(csvName, ios::in | ios::binary);
	string af;
	bool ok = 1;
	while (!fCSV.eof())
	{
		getline(fCSV, af);
		//cout << af << endl;// << " " << af.find(',') << "//";
		char* o;
		o = strtok((char*)af.c_str(), " ");
		while (o != NULL)
		{
			if (o[strlen(o) - 1] == ',')
			{
				//	cout << o << " " << o[strlen(o) - 1] << endl;
				o = strtok(NULL, " ");
			}
			else
			{
				ok = 0;
				break;
			}
		}
		//		cout << o << endl;
		string aff;
		aff = af.substr(af.length() - 1);
		//cout << aff << aff.c_str() << endl;

		if (ok == 0)
			if (strcmp(o, aff.c_str()))
				rez = 0;
			else
				rez = 1;
	}
}
/*
void BinaryFile::deserialization(char* tableName)
{
	string binaryName = tableName;
	binaryName += ".bin";
	ifstream file;
	file.open(binaryName, ios::trunc | ios::binary);
	int buffer[2];
	file.read((char*)&buffer, sizeof(buffer));
	file.close();
}*/

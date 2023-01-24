#define _CRT_SECURE_NO_WARNINGS
#include "TextFile.h"
#include "identificator.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>


using namespace std;
/*
int CreateTable(char* tableName, char* tableInfo, int* size, char* command);
int DropTable(char* tableName, char* command, int tokenType);
int DisplayTable(char* tableName, char* command);
char Delete(char check, char* tableName, char* nameColumnWhere, char* valueWhere, char* command, int tokenType);
int Update(char* tableName, char* columnNameSet, char* valueSet, char* nameColumnWhere, char* valueWhere, char* command, char* tableInfo);
int Select(char* tableName, char* command, char* columns);
int Insert(char* tableName, char* command, char* values);
int Import(char* tableName, char* command, char* fileName);
int DropIndex(char* command, char* tableName, char* indexName, int tokenType);
int CreateIndex(char* tableName, char* indexName, char* columnName, char* command);
*/
void TextFile::fileTextCreate(char* fileName, char* info)
{
	ofstream myFile;
	string name = fileName;
	name += ".txt";
	myFile.open(name);
	myFile << info;
	myFile << endl;
}

void TextFile::fileTextDrop(char* fileName, int& rez)
{
	string textName = fileName;
	textName += ".txt";
	string binaryName = fileName;
	binaryName += ".bin";
	if (remove(textName.c_str()) == 0)
		rez = 1;
	remove(textName.c_str());
	remove(binaryName.c_str());
}

void TextFile::fileTextDisplay(char* fileName, char* info)
{
	string textName = fileName;
	textName += ".txt";
	ifstream f(textName);
	char tableInfo[100] = { '\0' };
	while (!f.eof())
	{
		f >> info;
		strcat(tableInfo, info);
		strcat(tableInfo, " ");
	}
	strcpy(info, tableInfo);
}

char* TextFile::getFileName()
{
	return fileName;
}

void TextFile::setFileName(char* fileName)
{
	strcpy(this->fileName, fileName);
}

char* TextFile::getInfo()
{
	return info;
}
void TextFile::deserialization(char* fileName, char* info)
{
	string binaryName = fileName;
	binaryName += ".bin";
	ifstream g(binaryName, ios::binary);
	int length = 0;
	g.read((char*)&length, sizeof(length));
	delete[] info;
	info = new char[length + 1];
	g.read(info, length + 1);
	g.close();
}

void TextFileCommands::fileTextRead(int argc, char* argv[], int i)
{
	//for (int i = 1;i < argc;i++)
	//{

	string name = argv[i];
	fstream fcommands;
	fcommands.open(name, ios::in); string tmp;
	cout << "You displayed the following: " << argv[i] << endl;
	while (!fcommands.eof())
	{
		getline(fcommands, tmp);
		cout << tmp << endl;
	}
	fcommands.close();
	//}
}
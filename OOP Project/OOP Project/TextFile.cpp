#include "TextFile.h"
#include "identificator.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>


using namespace std;

void TextFile::createTextFile(char* nameOfTheFile, char* info)
{
	ofstream myFile;
	string name = nameOfTheFile;
	name += ".txt";
	myFile.open(name);
	myFile << info;
	myFile << endl;
}

void TextFile::dropTextFile(char* nameOfTheFile, int& result)
{
	string textName = nameOfTheFile;
	textName += ".txt";
	string binaryName = nameOfTheFile;
	binaryName += ".bin";
	if (remove(textName.c_str()) == 0)
		result = 1;
	remove(textName.c_str());
	remove(binaryName.c_str());
}

void TextFile::displayTextFile(char* nameOfTheFile, char* info)
{
	string textName = nameOfTheFile;
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
void TextFile::deserialize(char* nameOfTheFile, char* info)
{
	string binaryName = nameOfTheFile;
	binaryName += ".bin";
	ifstream g(binaryName, ios::binary);
	int length = 0;
	g.read((char*)&length, sizeof(length));
	delete[] info;
	info = new char[length + 1];
	g.read(info, length + 1);
	g.close();
}

void TextFileCommands::readTextFile(int argc, char* argv[], int i)
{
	//for (int i = 1;i < argc;i++)
	//{

	string name = argv[i];
	fstream fcommands;
	fcommands.open(name, ios::in); string tmp;
	cout << "You displayed the content: " << argv[i] << endl;
	while (!fcommands.eof())
	{
		getline(fcommands, tmp);
		cout << tmp << endl;
	}
	fcommands.close();
	//}
}
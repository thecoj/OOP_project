#include <string>
#include <iostream>

using namespace std;

class TextFile
{
private:
	char* fileName;
	char* info;
public:
	/*TextFile()
	{
		fileName = nullptr;
		info = nullptr;
	}
	TextFile(char* fileName)
	{
		this->fileName = new char[strlen(fileName) + 1];
		strcpy(this->fileName, fileName);
	}*/
	void createTextFile(char* nameOfTheFile, char* info);
	void dropTextFile(char* nameOfTheFile, int& rez);
	void displayTextFile(char* nameOfTheFile, char* info);
	char* getfileName();
	void setfileName(char* fileName);
	char* getInfo();
	void deserialize(char* nameOfTheFile, char* info);
};

class TextFileCommands : public TextFile
{
public:
	void readTextFile(int argc, char* argv[], int i);
};

#include <map>
#include <set>
#include <iostream>
using namespace std;
class BinaryFile
{
private:
	char* fileName;
	char* info;
public:
	void fileBinaryCreate(char* tableName, char* tableInfo);
	void fileBinaryDisplay(char* tableName, map<string, multiset<int>> mapInt, map<string, multiset<float>> mapFloat, map<string, multiset<string>> mapString);
	//void fileBinaryInsert(char* tableName, char* values, map<string, multiset<int>> mapInt, map<string, multiset<float>> mapFloat, map<string, multiset<string>> mapString);
	//void deserialization(char* tableName);
	void display(char* tableName);
	void importCSV(char* tableName, char* csvName, int& rez);
	void checkCSV(char* csvName, int& rez);
};

class BinaryFileOut : public BinaryFile
{
public:
	void fileBinaryInsert(char* tableName, char* values, map<string, multiset<int>> mapInt, map<string, multiset<float>> mapFloat, map<string, multiset<string>> mapString);
};
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

void CreateBinary(char* tableName, char* tableInfo)
{
	string binaryName = tableName;
	binaryName += ".bin";
	ofstream g(binaryName, ios::binary);
	int length = strlen(tableInfo);
	g.write((char*)&length, sizeof(length));
	g.write(tableInfo, length + 1);
	g.close();

}
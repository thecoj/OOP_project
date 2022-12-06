#include <iostream>
#include <sstream>
#include <iomanip>
#include "identificator.h"
#include <fstream>
#include "Column.h"
#include <vector>
#include <iterator>
#include <list>
#include <map>
#include <algorithm>
#include <vector>
#include <set>
#include <exception>
using namespace std;

int CreateTable(char* tableName, char* tabelInfo, list<string>& columns, int* size, char* command, list<string>& columnType);
int DropTable(char* tableName, char* command, int tokenType);
int DisplayTable(char* tableName, char* command);
char Delete(char check, char* tableName, char* columnNameWhere, char* valueWhere, int& typeWhere, char* command, int tokenType);
int Update(char* tableName, char* columnNameSet, char* valueSet, int& typeSet, char* columnNameWhere, char* valueWhere, int& typeWhere, char* command, char* tabelInfo);
int Select(char* tableName, char* command, char* columns);
int Insert(char* tableName, char* command, char* values, vector<int>& valueType);
int DropIndex(char* command, char* tableName, char* indexName, int tokenType);
int CreateIndex(char* tableName, char* indexName, char* columnName, char* command);

int main() 
{
	return 0;
}

//Work in Progress
#include <fstream>
#include <iostream>
#include <set>
using namespace std;

class Column
{
public:
	set<int> sint;
	set<float> sfloat;
	set<string> sstring;

	/*virtual void createColumn(char* columnName)
	{
		cout << "It should NOT be called";
	}*/
	virtual void insert(char* columnName, char* values)
	{
		cout << "It should NOT be called";
	}

};

class ColumnInt : public Column
{
public:
	set<int> createColumnInt(char* columnName)
	{
		set<int> s;
		return s;
	}
	void insert(char* columnName, char* values) override
	{
		set<int> s;
		int l = strlen(values);
		int number;
		char* p;
		p = strtok(values, " ");
		while (p != NULL)
		{
			int noDigits = strlen(p);
			for (int i = 0; i < noDigits; i++)
			{
				int digit = p[i] - '0';
				number += digit * pow(10, i);
			}
			s.insert(number);
			p = strtok(NULL, " ");
		}

	}
	void display(char* columnName, set<int> s)
	{
		for (set<int>::iterator it = s.begin(); it != s.end(); it++)
		{
			cout << *it << " ";
		}
	}
};

class ColumnFloat : public Column
{
	set<float> createColumnFloat(char* columnName)
	{
		set<float> s;
		return s;
	}

};

class ColumnString : public Column
{
	set<string> createColumnString(char* columnName)
	{
		set<string> s;
		return s;
	}
};
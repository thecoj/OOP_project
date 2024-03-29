#define _CRT_SECURE_NO_WARNINGS
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
		cout << "It sould not call this";
	}*/
	virtual void insert(char* columnName, char* values)
	{
		cout << "It sould not call this";
	}

};

class intColumn : public Column
{
public:
	set<int> intColumnCreate(char* columnName)
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
			int digitNumber = strlen(p);
			for (int i = 0; i < digitNumber; i++)
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

class FloatColumn : public Column
{
	set<float> createFloatColumn(char* columnName)
	{
		set<float> s;
		return s;
	}

};

class StringColumn : public Column
{
	set<string> createStringColumn(char* columnName)
	{
		set<string> s;
		return s;
	}
};
#include <iostream>
#include <map>
#include <set>
using namespace std;

class Index
{
public:
	string name;
	Index()
	{
		name = "";
	}
	Index(string name)
	{
		this->name = name;
	}
	virtual void display()
	{
		cout << "This is a base index" << endl;
	}
	virtual void create()
	{
		cout << "This index was created" << endl;
	}
	virtual void drop()
	{
		cout << "This index was deleted" << endl;
	}
};

class IndexInt : public Index
{
public:
	multiset<int> si;
	map<string, multiset<int>> mapIndexInt;
	IndexInt()
	{

	}
	IndexInt(string name) :Index(name)
	{
	}
	void display()
	{
		cout << "This is an index on an int column" << endl;
	}
	void create()
	{
		mapIndexInt.insert(pair<string, multiset<int>>(name, si));
		cout << "Index was created " << name << endl;

	}
	void drop()
	{
		mapIndexInt.erase(name);
		cout << "Index was deleted " << name << endl;
	}
};

class IndexFloat : public Index
{
public:
	multiset<float> sf;
	map<string, multiset<float>> mapIndexFloat;
	IndexFloat()
	{

	}
	IndexFloat(string name) :Index(name)
	{

	}
	void display()
	{
		cout << "This is an index on a float column" << endl;
	}
	void create()
	{
		mapIndexFloat.insert(pair<string, multiset<float>>(name, sf));
		cout << " Index was created " << name << endl;
	}
	void drop()
	{
		mapIndexFloat.erase(name);
		cout << "Index was deleted " << name << endl;
	}

};

class IndexString : public Index
{
public:
	multiset<string> ss;
	map<string, multiset<string>> mapIndexString;
	IndexString()
	{

	}
	IndexString(string name) :Index(name)
	{

	}
	void display()
	{
		cout << "This is an index on a string column" << endl;
	}
	void create()
	{
		mapIndexString.insert(pair<string, multiset<string>>(name, ss));
		cout << "Index was created " << name << endl;
	}
	void drop()
	{
		mapIndexString.erase(name);
		cout << "Index was deleted " << name << endl;
	}
};

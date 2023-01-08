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
	virtual void creare()
	{
		cout << "Index created" << endl;
	}
	virtual void drop()
	{
		cout << "Index dropped" << endl;
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
		cout << "This index is on an int column" << endl;
	}
	void creare()
	{
		mapIndexInt.insert(pair<string, multiset<int>>(name, si));
		cout << "Index created " << name << endl;

	}
	void drop()
	{
		mapIndexInt.erase(name);
		cout << "Index dropped " << name << endl;
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
		cout << "This index is on an float column" << endl;
	}
	void creare()
	{
		mapIndexFloat.insert(pair<string, multiset<float>>(name, sf));
		cout << " Index created " << name << endl;
	}
	void drop()
	{
		mapIndexFloat.erase(name);
		cout << "Index dropped " << name << endl;
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
		cout << "This index is on an string column" << endl;
	}
	void creare()
	{
		mapIndexString.insert(pair<string, multiset<string>>(name, ss));
		cout << "Index created " << name << endl;
	}
	void drop()
	{
		mapIndexString.erase(name);
		cout << "Index dropped " << name << endl;
	}
};

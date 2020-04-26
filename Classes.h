#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <sstream>
#include <Windows.h>

using namespace std;

class Admin
{
public:
	string login = "admin";
	string password = "password";

	friend istream& operator>> (istream&, Admin&);
	friend ostream& operator<< (ostream&, Admin&);
	friend ifstream& operator>> (ifstream&, Admin);
	friend ofstream& operator<< (ofstream&, Admin&);
};

class Brigade
{
public:
	string name = "no name";
	int people = 0;
	string order = "no active order";
	int completed = 0;

	friend istream& operator>> (istream&, Brigade&);
	friend ostream& operator<< (ostream&, Brigade&);
	friend ifstream& operator>> (ifstream&, Brigade&);
	friend ofstream& operator<< (ofstream&, Brigade&);
	void edit();
	void make_deleted();
};

class Order
{
public:
	int id = 1234;
	string customer = "no customer";
	string address = "no address";
	double area = 0;
	double cost = 0;
	string deadline = "no deadline";
	string maintainer = "no maintainer";
	bool isCompleted = false;

	friend istream& operator>> (istream&, Order&);
	friend ostream& operator<< (ostream&, Order&);
	friend ifstream& operator>> (ifstream&, Order&);
	friend ofstream& operator<< (ofstream&, Order&);
	void edit();
	void make_deleted();
};

template <typename T>
void scan(T&, string);

string enter_date();

void delete_deleted(vector<Brigade>&);

string encryptDecrypt(string);
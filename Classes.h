#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <sstream>
#include <Windows.h>
#include <algorithm>
#include <functional>

using namespace std;

class Admin
{
public:
	string login = "admin";
	string password = "password";

	friend istream& operator>> (istream&, Admin&);
	friend ostream& operator<< (ostream&, Admin&);
	friend ifstream& operator>> (ifstream&, Admin&);
	friend ofstream& operator<< (ofstream&, Admin&);
	void make_deleted();
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
void scan(T&,const string&);

string enter_date();

void delete_deleted(vector<Brigade>&);

void delete_deleted(vector<Order>&);

void delete_deleted(vector<Admin>&);

string encryptDecrypt(const string&);

bool clean_password(string&);

bool password_size(string&);

bool clean_login(string&);

bool login_size(string&);

void main_menu(vector<Brigade>&, vector<Order>&, vector<Admin>&);

void show_brigades(vector<Brigade>&, vector<Order>&, vector<Admin>&);

void show_top_brigades(vector<Brigade>&, vector<Order>&, vector<Admin>&);

void show_orders(vector<Brigade>&, vector<Order>&, vector<Admin>&);

void sign_in(vector<Brigade>&, vector<Order>&, vector<Admin>&);

void admin_menu(vector<Brigade>&, vector<Order>&, vector<Admin>&, string);

void manage_brigades(vector<Brigade>&, vector<Order>&, vector<Admin>&, int&);

void manage_orders(vector<Brigade>&, vector<Order>&, vector<Admin>&, int&);

void edit_account(vector<Brigade>&, vector<Order>&, vector<Admin>&, int&);

void sign_up(vector<Brigade>&, vector<Order>&, vector<Admin>&, int&);

void show_top_brigades(vector<Brigade>&, vector<Order>&, vector<Admin>&, int&);

template <typename T>
void sync(vector<T>&);
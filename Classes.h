#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <sstream>
#include <algorithm>
#include <functional>
#include <chrono>
#include <windows.h>

using namespace std;

struct Admin
{
	string login = "admin";
	string password = "password";

	friend istream& operator>> (istream&, Admin&);
	friend ostream& operator<< (ostream&, const Admin&);
	friend ifstream& operator>> (ifstream&, Admin&);
	friend ofstream& operator<< (ofstream&, const Admin&);
    void make_deleted() {login = "...";} //Inline functions increase performance
    //This function is IMPLICITLY inline (because it's inside a class code)
};

struct Brigade
{
	string name = "no name";
	int people = 0;
	string order = "no active order";
	int completed = 0;

	friend istream& operator>> (istream&, Brigade&);
	friend ostream& operator<< (ostream&, const Brigade&);
	friend ifstream& operator>> (ifstream&, Brigade&);
	friend ofstream& operator<< (ofstream&, const Brigade&);
	void edit();
    void make_deleted() {people = -10;} //Inline
};

struct Order
{
	int id = 1234;
	string customer = "no customer";
	string address = "no address";
	double area = 0;
	double cost = 0;
	string deadline = "no deadline";
	string maintainer = "no maintainer";
	bool isCompleted = false;

	friend istream& operator>> (istream&, Order&);
	friend ostream& operator<< (ostream&, const Order&);
	friend ifstream& operator>> (ifstream&, Order&);
	friend ofstream& operator<< (ofstream&, const Order&);
	void edit();
    void make_deleted() {cost = -10;} //Inline
};

void flush_cin();

template <typename T>
void scan(T& a, const string& str) //We don't change this string, it should be a reference
{
    while (true)
    {
        cout << str;
        cin >> a;
        if (cin.fail() || a < 0) //TODO: FIX: what if type T is NOT NUMERIC?
        {
			flush_cin();
            system("cls"); //TODO: We shouldn't do output in the input functions
        }
        else
            break;
    }
    cin.ignore(32767, '\n');
}

template <typename T>
void save(const vector<T>& vec, const string& filename)
{
    ofstream fout;
    fout.open(filename);
    for (const T& i : vec)                                //for every reference to element i in vec
        fout << i;
    fout.close();
}

string enter_date();

void delete_deleted(vector<Brigade>&);

void delete_deleted(vector<Order>&);

void delete_deleted(vector<Admin>&);

string encryptDecrypt(const string&);

bool clean_password(string&);

bool clean_login(string&);

bool check_size(const string&, size_t, size_t);

void main_menu(vector<Brigade>&, vector<Order>&, vector<Admin>&);

void show_brigades(vector<Brigade>&, vector<Order>&, vector<Admin>&);

void show_top_brigades(vector<Brigade>, vector<Order>&, vector<Admin>&);

void show_orders(vector<Brigade>&, vector<Order>&, vector<Admin>&);

void sign_in(vector<Brigade>&, vector<Order>&, vector<Admin>&);

void admin_menu(vector<Brigade>&, vector<Order>&, vector<Admin>&, int&);

void manage_brigades(vector<Brigade>&, vector<Order>&, vector<Admin>&, int&);

void manage_orders(vector<Brigade>&, vector<Order>&, vector<Admin>&, int&);

void edit_account(vector<Brigade>&, vector<Order>&, vector<Admin>&, int&);

void sign_up(vector<Brigade>&, vector<Order>&, vector<Admin>&, int&);

void show_top_brigades(vector<Brigade>&, vector<Order>&, vector<Admin>&, int&);

bool save_brigade(Brigade&, vector<Order>&);

bool save_order(Order&, vector<Brigade>&);

void fancy_dots(unsigned);

bool yes_or_no(const string& msg);
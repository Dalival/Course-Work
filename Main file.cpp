#include "Classes.h"

using namespace std;

int main()
{
	vector<Admin> veca;
	vector<Brigade> vecb;
	vector<Order> veco;

	Admin buffa;
	Brigade buffb;
	Order buffo;

	ofstream fout;
	fout.open("Administrators.txt");
	if (fout.is_open())
	{
		fout << buffa;
	}
	fout.close();

	cout << "My user in real: " << buffa << ' ' << buffa.password << endl;

	ifstream fin;
	fin.open("Administrators.txt");
	if (fin.is_open())
		fin >> buffa;
	cout << "My user from file: " << buffa << ' ' << buffa.password;

	/*ifstream fin;
	fin.open("Administrators.txt");
	if (fin.is_open())
	{
		for (int i = 0; !fin.eof(); i++)
			fin >> buffa;
	}/*









	///////////////////////////////////////////////////     N O T E S     ///////////////////////////////////////////////////

	/*vector<Brigade> bvec;
	Brigade bbuf;

	for (int i = 0; i < 3; i++)
	{
		cin >> bbuf;
		ofstream fout;
		fout.open("myFile.txt", ofstream::app);
		if (!fout.is_open())
			cout << "ERROR! Can't save data!";
		else
		{
			fout << bbuf << endl;
			cout << "Successfull!" << endl << endl;
			cin.ignore(32767, '\n');
		}
	}

	ifstream fin;
	fin.open("myFile.txt");
	if (!fin.is_open())
		cout << "No team has been registered.";
	else
	{
		for (int i = 0; !fin.eof(); i++)
		{
			cin >> bvec[0];
		}
	}*/
}
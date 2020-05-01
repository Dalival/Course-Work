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

	ifstream fin;
	fin.open("administrators.txt");
	if (fin.is_open())
	{
		for (int i = 0; !fin.eof(); i++)
		{
			fin >> buffa;
			veca.push_back(buffa);
		}
	}
	fin.close();

	fin.open("brigades.txt");
	if (fin.is_open())
	{
		for (int i = 0; !fin.eof(); i++)
		{
			fin >> buffb;
			vecb.push_back(buffb);
		}
	}
	fin.close();

	fin.open("orders.txt");
	if (fin.is_open())
	{
		for (int i = 0; !fin.eof(); i++)
		{
			fin >> buffo;
			veco.push_back(buffo);
		}
	}
	fin.close();

	main_menu(vecb, veco, veca);





	///////////////////////////////////////////////////     N O T E S     ///////////////////////////////////////////////////

	/*ofstream fout;
	fout.open("brigades.txt", ofstream::app);
	if (fout.is_open())
	{
		Brigade br;
		fout << br;
	}
	fout.close();
	fout.open("administrators.txt", ofstream::app);              //ÇÀÏÈÑÜ ÒÅÑÒÎÂÛÕ ÎÁÚÅÊÎÒÂ Â ÔÀÉË
	if (fout.is_open())
	{
		Admin adm;
		fout << adm;
	}
	fout.close();
	fout.open("orders.txt", ofstream::app);
	if (fout.is_open())
	{
		Order ord;
		fout << ord;
	}
	fout.close();*/

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
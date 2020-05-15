#include "Classes.h"
using namespace std;

int main() try
{
	vector<Admin> veca; //vector of administrators
	vector<Brigade> vecb; //vector of brigades
	vector<Order> veco; //vector of orders

	Admin buffa; //buffer variable for administrator
	Brigade buffb; //buffer variable for brigade
	Order buffo; //buffer variable for order

	ifstream fin;
	fin.open("administrators.txt"); //reading admins from file
	while (fin >> buffa)
		veca.push_back(buffa);
	if (empty(veca)) //create a standart admin when program run first time
	{
		Admin standart;
		veca.push_back(standart);
	}
    fin.close();

	fin.open("brigades.txt"); //reading brigades from file
	while(fin >> buffb)
        vecb.push_back(buffb);
	fin.close();

	fin.open("orders.txt"); //reading orders from file
	while(fin >> buffo)
        veco.push_back(buffo);
	fin.close();

	main_menu(vecb, veco, veca); //launching
	return 0;
}

catch (std::exception& e) //Catch any exception
{
    cerr << "\nWarning! Something really bad occurred. Message:  \n" << e.what() << "\n\nThe program can't continue!\n"; //output WHAT it is
    return (EXIT_FAILURE); //EXIT
}
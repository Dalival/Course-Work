#include "Classes.h"
using namespace std; //Bad practice

int main() try
{
	vector<Admin> veca;
	vector<Brigade> vecb;
	vector<Order> veco;

	Admin buffa;
	Brigade buffb;
	Order buffo;

	ifstream fin;
	fin.open("administrators.txt");
	while(fin >> buffa)
        veca.push_back(buffa);
    fin.close();

	fin.open("brigades.txt");
	while(fin >> buffb)
        vecb.push_back(buffb);
	fin.close();

	fin.open("orders.txt");
	while(fin >> buffo)
        veco.push_back(buffo);
	fin.close();

	main_menu(vecb, veco, veca);
}
catch (std::exception& e) //Catch any exception
{
    cerr << "\nWarning! Something really bad occurred. Message:  \n" << e.what() << "\nThe program can't continue!\n"; //output WHAT it is
    return (EXIT_FAILURE); //EXIT
}
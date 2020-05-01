#pragma once
#include "Classes.h"

//////////////////// ADMIN'S METHODS ////////////////////

istream& operator>> (istream& in, Admin& a)
{
    cout << "Enter login: ";
    getline(cin, a.login);
    cout << "Enter password: ";
    getline(cin, a.password);
    cout << "\nAdministrator " << a.login << " was successfully registrated!" << endl << endl;
    return in;
}

ostream& operator<< (ostream& out, Admin& a)
{
    cout << a.login << endl;
    return out;
}

ifstream& operator>> (ifstream& fin, Admin& a)
{
    fin >> a.login;
    fin >> a.password;
    a.login = encryptDecrypt(a.login);
    a.password = encryptDecrypt(a.password);
    return fin;
}

ofstream& operator<< (ofstream& fout, Admin& a)
{
    fout << encryptDecrypt(a.login) << endl;
    fout << encryptDecrypt(a.password) << endl;
    return fout;
}

//////////////////// BRIGADE'S METHODS ////////////////////

istream& operator>> (istream& in, Brigade& b)
{
	cout << "Enter brigade name: ";
	getline(cin, b.name);
    scan(b.people, "Enter how many people does brigade include: ");
	cout << "\nThe brigade " << b.name << " was successfully registrated!" << endl << endl;
	
    return in;
}

ostream& operator<< (ostream& out, Brigade& b)
{
    cout << "Brigade " << b.name << endl;
    cout << b.people << " people" << endl;
    cout << "Active order: " << b.order << endl;
    cout << b.completed << " completed orders";
	
    return out;
}

ifstream& operator>> (ifstream& fin, Brigade& b)
{
    getline(fin, b.name);
    fin >> b.people;
    fin >> b.order;
    fin >> b.completed;
  
    return fin;
}

ofstream& operator<< (ofstream& fout, Brigade& b)
{
    fout << b.name << endl;
    fout << b.people << endl;
    fout << b.order << endl;
    fout << b.completed << endl;
   
    return fout;
}

void Brigade::edit()
{
	int i = 1;
	char yn;

	while (i == 1)
	{
        system("cls");
		cout << "1 -> Edit name \n2 -> Edit number of people \n3 -> Change active order" << endl;
		i = _getch();
        system("cls");

		switch (i)
		{
		case '1':
			cout << "Enter new name: ";
			getline(cin, name);
			cout << "New name: " << name;
			break;

        case '2':
            scan(people, "Enter how many people are in brigade: ");
            cout << "Now " << name << " has " << people << " people.";
            break;

		case '3':
			cout << "Enter ID of order: ";
			getline(cin, order);
			cout << "Now brigade maintain the order " << order;
			break;
		default:
			i = 1;
			system("cls");
			continue;
		}

		do
		{
			cout << endl << "Do you want to edit something else? y/n";
			yn = _getch();
			switch (yn)
			{
			case 'y':
				i = 1;
				system("cls");
				break;
			case 'n':
				i = 2;
			default:
				i = 5;
			}
		} while (i == 5);
	}
}

void Brigade::make_deleted()
{
    people = -10;
}

//////////////////// ORDER'S METHODS ////////////////////

istream& operator>> (istream& in, Order& o)
{
	string s;
	scan(o.id, "Enter ID of the project: ");
    cin.ignore(32767, '\n');
    system("cls");

	cout << "Enter customer: ";
	getline(cin, o.customer);
    system("cls");

	cout << "Enter address: ";
	getline(cin, o.address);
    system("cls");

	scan(o.area, "Enter area of the office in square meters: ");
    system("cls");

	scan(o.cost, "Enter the cost of the project: ");
    cin.ignore(32767, '\n');
    system("cls");

	cout << "Let's set the deadline.\n";
    o.deadline = enter_date();
    system("cls");

	cout << "Choose a maintainer: ";
	getline(cin, o.maintainer);
    system("cls");

	return in;
}

ostream& operator<< (ostream& out, Order& o)
{
	cout << "ID: " << o.id << endl;
	cout << o.customer << endl;
	cout << o.address << endl;
	cout << o.area << " square meters" << endl;
	cout << '$' << o.cost << endl;
	cout << "The deadline is " << o.deadline << endl;
	cout << "Maintainer - " << o.maintainer << endl;

    return out;
}

ifstream& operator>> (ifstream& fin, Order& o)
{
    fin >> o.id;
    getline(fin, o.customer);
    getline(fin, o.address);
    fin >> o.area;
    fin >> o.cost;
    getline(fin, o.deadline);
    getline(fin, o.maintainer);
    fin >> o.isCompleted;
   
    return fin;
}

ofstream& operator<< (ofstream& fout, Order& o)
{
    fout << o.id << endl;
    fout << o.customer << endl;
    fout << o.address << endl;
    fout << o.area << endl;
    fout << o.cost << endl;
    fout << o.deadline << endl;
    fout << o.maintainer << endl;
    fout << o.isCompleted << endl;

    return fout;
}

void Order::edit()
{
	int i = 1;
	char yn;

	while (i == 1)
	{
        system("cls");
		cout << "1 -> Edit customer \n2 -> Edit address \n3 -> Edit area \n4 -> Edit cost \n5 -> Move deadline \n6 -> Change project maintainer" << endl << endl;
		i = _getch();
        system("cls");

		switch (i)
		{
		case '1':
			cout << "Enter new customer: ";
			getline(cin, customer);
			cout << "New customer: " << customer;
			break;

		case '2':
			cout << "Enter new address: ";
			getline(cin, address);
			cout << "New address: " << address;
			break;

		case '3':
			scan(area, "Enter new area: ");
			cout << "New area: " << area;
			break;

		case '4':
			scan(cost, "Enter new cost: ");
			cout << "New cost: " << cost;
			break;

		case '5':
			cout << "Let's set new deadline.\n";
            deadline = enter_date();
            cout << "\nNew deadline: " << deadline;
			break;

		case '6':
			cout << "Enter new maintaining brigade: ";
			getline(cin, maintainer);
			cout << "New maintainer: " << maintainer;
			break;
		default:
			i = 1;
			system("cls");
			continue;
		}

        do
        {
            cout << endl << "Do you want to edit something else? y/n";
            yn = _getch();
            switch (yn)
            {
            case 'y':
                i = 1;
                system("cls");
                break;
            case 'n':
                i = 2;
                break;
            default:
                i = 5;
            }
        }
        while (i == 5);
	}
}

void Order::make_deleted()
{
    cost = -10;
}

//////////////////// FUNCTIONS ////////////////////

string enter_date()
{
    istringstream  ssin(__DATE__);
    string str_current_m, str_current_d, str_current_y;
    ssin >> str_current_m >> str_current_d >> str_current_y;

    int current_d = stoi(str_current_d);
    int current_y = stoi(str_current_y);
    int current_m = -1;

    if (str_current_m == "Jan")
        current_m = 1;
    if (str_current_m == "Feb")
        current_m = 2;
    if (str_current_m == "Mar")
        current_m = 3;
    if (str_current_m == "Apr")
        current_m = 4;
    if (str_current_m == "May")
        current_m = 5;
    if (str_current_m == "Jun")
        current_m = 6;
    if (str_current_m == "Jul")
        current_m = 7;
    if (str_current_m == "Aug")
        current_m = 8;
    if (str_current_m == "Sep")
        current_m = 9;
    if (str_current_m == "Oct")
        current_m = 10;
    if (str_current_m == "Nov")
        current_m = 11;
    if (str_current_m == "Dec")
        current_m = 12;
    if (current_m == -1)
    {
        cout << "\n     Critical ERROR. I can't understand what month is now! Exetting...";
        Sleep(3500);
        exit(-1);
    }

    int year, month, day;

    while (true)
    {
        cout << "\nEnter the year: ";
        cin >> year;
        if (cin.fail())
        {
            system("cls");
            cin.clear();
            cin.ignore(32767, '\n');
            continue;
        }
        if (year < current_y)
        {
            system("cls");
            cout << "Dedline can't be in the past. Try again." << endl;
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "Enter the month: ";
        cin >> month;
        if (cin.fail())
        {
            system("cls");
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "The entered year: " << year << endl;
            continue;
        }
        if (month < 1 || month > 12)
        {
            system("cls");
            cout << "The entered year: " << year << "\n\nThere are only 12 months in the year." << endl;
            continue;
        }
        if (year == current_y && month < current_m)
        {
            system("cls");
            cout << "The entered year: " << year << "\n\nDedline can't be in the past. Try again." << endl;
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "Enter the day: ";
        cin >> day;
        if (cin.fail())
        {
            system("cls");
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "The entered year: " << year << "\nThe entered month: " << month << endl;
            continue;
        }
        if (day < 1 || day > 31)
        {
            system("cls");
            cout << "The entered year: " << year << "\nThe entered month: " << month << "\n\nThe month can include maximum 31 days." << endl;
            continue;
        }
        if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            if (day > 30)
            {
                system("cls");
                cout << "The entered year: " << year << "\nThe entered month: " << month << "\n\nApr, Jun, Sep, Nov include only 30 days." << endl;
                continue;
            }
        }
        if (month == 2 && year % 4 == 0)
        {
            if (day > 29)
            {
                system("cls");
                cout << "The entered year: " << year << "\nThe entered month: " << month << "\n\nFeb include maximum 29 days." << endl;
                continue;
            }
        }
        if (month == 2 && year % 4 != 0)
        {
            if (day > 28)
            {
                system("cls");
                cout << "The entered year: " << year << "\nThe entered month: " << month << "\n\nFeb of non-leap year include only 28 days." << endl;
                continue;
            }
        }
        if (year == current_y && month == current_m && day < current_d)
        {
            system("cls");
            cout << "The entered year: " << year << "\nThe entered month: " << month << "\n\nDedline can't be in the past. Try again." << endl;
            continue;
        }
        break;
    }

    stringstream ssout;

    if (day < 10)
        ssout << '0' << day << '.';
    else
        ssout << day << '.';
    if (month < 10)
        ssout << '0' << month << '.' << year;
    else
        ssout << month << '.' << year;

    string date = ssout.str();
    cin.ignore(32767, '\n');
    return date;
}

template <typename T>
void scan(T& a, string str)
{
    while (true)
    {
        cout << str;
        cin >> a;
        if (cin.fail() || a < 0)
        {
            cin.clear();
            cin.ignore(32767, '\n');
            system("cls");
        }
        else
            break;
    }
}

void delete_deleted(vector<Brigade>& vec)
{
    vec.erase(remove_if(vec.begin(), vec.end(), [](Brigade br) { return br.people < 0; }), vec.end());
    vec.shrink_to_fit();
    for (unsigned int i = 0; i < vec.size(); i++)
        cout << vec[i] << endl;
}

void delete_deleted(vector<Order>& vec)
{
    vec.erase(remove_if(vec.begin(), vec.end(), [](Order ord) { return ord.cost < 0; }), vec.end());
    vec.shrink_to_fit();
    for (unsigned int i = 0; i < vec.size(); i++)
        cout << vec[i] << endl;
}

string encryptDecrypt(string toEncrypt) {
    char key[3] = { 'F', 'E', 'A' }; // my initials
    string output = toEncrypt;
    for (unsigned int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];
    return output;
}

bool clean_password(string& s)
{
    for (char ch : s) {
        if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
            continue;
        else
            return false;
    }
    return true;
}

bool password_size(string& s)
{
    return (s.size() >= 8 && s.size() <= 24);
}

/*int main()
{
    string rpassword;
    getline(cin, rpassword);
    while (!clean_password(rpassword))
    {
        cout << "\nPassword might include only numbers and latin letters. Try again:\n\n";
        getline(cin, rpassword);
    }
    while (!password_size(rpassword))
    {
        cout << "\nPassword must be 8-24 symbols. Try again:\n\n";
        getline(cin, rpassword);
    }
    cout << "Successfull!" << endl;
}*/

//////////////////// MENUS ////////////////////

void main_menu(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca)
{
	system("cls");
	cout << "MAIN MENU" << endl << endl;
	cout << "1 -> Show the list of brigades\n" << "2 -> Show the list of orders\n" << "3 -> Sign in as an administrator\n" << "4 -> Exit\n\n";
	while (true)
	{
		switch (char ch = _getch())
		{
		case '1':
			show_brigades(vecb, veco, veca);
			break;
		case '2':
			show_orders(vecb, veco, veca);
			break;
		/*case '3':
			sign_in();
			break;*/
		case '4':
			cout << "Exitting ";
			Sleep(600);
			cout << ". ";
			Sleep(600);
			cout << ". ";
			Sleep(600);
			cout << ". ";
			Sleep(600);
			exit(0);
		default:
			continue;
		}
        break;
	}
}

void show_brigades(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca)
{
    system("cls");
    if (size(vecb) >= 0)
    {
        for (unsigned int i = 0; i < vecb.size(); i++)
        {
            cout << vecb[i] << endl;
        }
        cout << endl << "1 -> Show TOP-3 brigades" << endl << "2 -> Quit";
        while (true)
        {
            switch (char ch = _getch())
            {
            case '1':
                system("cls");
                show_top_brigades(vecb, veco, veca);
                break;
            case '2':
                main_menu(vecb, veco, veca);
            default:
                continue;
            }
            break;
        }
    }
    else
    {
        cout << "There are no registered brigades!\n" << "Press anu key to quit.";
        char ch = _getch();
        main_menu(vecb, veco, veca);
    }
}

void show_top_brigades(vector<Brigade> vecb, vector<Order>& veco, vector<Admin>& veca)  //vecb isn't a reference, because I don't want to sort the original vector
{
    sort(vecb.begin(), vecb.end(), [](Brigade a, Brigade b) { return a.completed > b.completed; });
    for (unsigned int i = size(vecb) - 1; i > size(vecb) - 3; i--)
        cout << vecb[i] << endl;
    cout << "\nPress any key to quit.";
    char ch = _getch();
    main_menu(vecb, veco, veca);
}

void show_orders(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca)
{
    system("cls");
    for (unsigned int i = 0; i < veco.size(); i++)
    {
        cout << veco[i] << endl;
    }
    cout << endl << "Press any key to quit.";
    char ch = _getch();
    main_menu(vecb, veco, veca);
}
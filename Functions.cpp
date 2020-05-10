#include "Classes.h"

//////////////////// ADMIN'S METHODS ////////////////////

istream& operator>> (istream& in, Admin& a)
{
    string input;
    while (true)
    {
        cout << "Enter the login of new administrator: ";
        getline(cin, input);
        if (login_size(input))
        {
            if (clean_login(input))
            {
                a.login = input;
                break;
            }
            else
            {
                system("cls");
                cout << "Login can include latin letters, numbers and symbols \"-\" and \"_\". Try again.\n";
            }
        }
        else
        {
            system("cls");
            cout << "Login should include 3-30 symblos. Try again.\n";
        }
	}

	while (true)
	{
		cout << "Enter the password of new administrator: ";
		getline(cin, input);
		if (password_size(input))
		{
			if (clean_password(input))
			{
				a.password = input;
				break;
			}
            else
            {
                system("cls");
                cout << "Password can include latin letters and numbers. Try again.\n";
            }
		}
        else
        {
            system("cls");
            cout << "Password should include 8-24 symblos. Try again.\n";
        }
	}
    system("cls");
    cout << "\nAdministrator " << a.login << " was registrated!";
    successfull();
    return in;
}

ostream& operator<< (ostream& out, Admin& a)
{
    cout << a.login << endl;
    return out;
}

ifstream& operator>> (ifstream& fin, Admin& a)
{
    getline(fin, a.login);
    getline(fin, a.password);
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

void Admin::make_deleted()
{
    login = "...";
}

//////////////////// BRIGADE'S METHODS ////////////////////

istream& operator>> (istream& in, Brigade& b)
{
    do
    {
        system("cls");
        cout << "Enter brigade name: ";
        getline(cin, b.name);
    } while (!clean_login(b.name));
    scan(b.people, "Enter how many people does brigade include: ");
	cout << "\nBrigade " << b.name << " was registrated!";
    successfull();	
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
    if (fin.peek() == EOF)
    {
        fin.ignore(32767, '\n');
        return fin;
    }
    string temp;
    getline(fin, b.name);
    getline(fin, temp);
    b.people = stoi(temp);
    getline(fin, b.order);
    getline(fin, temp);
    b.completed = stoi(temp);
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

			switch (_getch())
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
				break;
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

	cout << "Enter office address: ";
	getline(cin, o.address);
    system("cls");

	scan(o.area, "Enter area of the office in square meters: ");
    system("cls");

	scan(o.cost, "Enter cost of the project in dollars: ");
    cin.ignore(32767, '\n');
    system("cls");

	cout << "Let's set a deadline.\n";
    o.deadline = enter_date();
    successfull();

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
    if (fin.peek() == EOF)
    {
        fin.ignore(32767, '\n');
        return fin;
    }
    string temp;
    getline(fin, temp);
    o.id = stoi(temp);
    getline(fin, o.customer);
    getline(fin, o.address);
    getline(fin, temp);
    o.area = stoi(temp);
    getline(fin, temp);
    o.cost = stoi(temp);
    getline(fin, o.deadline);
    getline(fin, o.maintainer);
    getline(fin, temp);
    o.isCompleted = stoi(temp);
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

        cout << endl << "Do you want to edit something else? y/n";
        do
        {
            switch (_getch())
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

//////////////////// OTHER ////////////////////

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
        cout << "\n     Critical ERROR. I can't understand what month is now! Exiting...";
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
void scan(T& a, const string& str) //We don't change this string, it should be a reference
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
}

void delete_deleted(vector<Order>& vec)
{
    vec.erase(remove_if(vec.begin(), vec.end(), [](const Order& ord) { return ord.cost < 0; }), vec.end());
    vec.shrink_to_fit();
}

void delete_deleted(vector<Admin>& vec)
{
    vec.erase(remove_if(vec.begin(), vec.end(), [](Admin adm) { return adm.login == "..."; }), vec.end());
    vec.shrink_to_fit();
}

string encryptDecrypt(const string& toEncrypt) {
    char key[3] = { 'F', 'E', 'A' }; // my initials
    string output = toEncrypt;
    for (unsigned int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];
    return output;
}

void successfull()
{
    cout << endl << "Successfull! ";
    Sleep(400);
    cout << ". ";
    Sleep(400);
    cout << ". ";
    Sleep(400);
    cout << ". ";
    Sleep(400);
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

bool clean_login(string& s)
{
    for (char ch : s) {
        if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == '-' || ch == '_')
            continue;
        else
            return false;
    }
    return true;
}

bool login_size(string& s)
{
    return (s.size() >= 3 && s.size() <= 30);
}

void sync(vector<Admin>& vec)
{
    ofstream fout;
    fout.open("administrators.txt");
    for (Admin& i : vec)                                //for every reference to element i in vec
    {
        fout << i;
    }
    fout.close();
}

void sync(vector<Order>& vec)
{
    ofstream fout;
    fout.open("orders.txt");
    for (Order& i : vec)                                //for every reference to element i in vec
    {
        fout << i;
    }
    fout.close();
}

void sync(vector<Brigade>& vec)
{
    ofstream fout;
    fout.open("brigades.txt");
    for (Brigade& i : vec)                                //for every reference to element i in vec
    {
        fout << i;
    }
    fout.close();
}

bool save_brigade(Brigade& b, vector<Order>& veco)
{
	if (b.people < 0)
	{
		for (auto& o : veco)
		{
			if (o.id == stoi(b.order))
			{
				o.maintainer == "no maintainer";
				return true;
			}
		}
		return false;
	}

	else
	{
		for (auto& o : veco)
		{
			if (o.id == stoi(b.order))
			{
				o.maintainer == b.name;
				return true;
			}
		}
		return false;
	}
}

bool save_order(Order& o, vector<Brigade>& vecb)
{
	if (o.cost < 0)
	{
        for (auto& b : vecb)
        {
            if (b.name == o.maintainer)
            {
                b.order = "no active order";
                return true;
            }
        }
        return false;
	}
	else
	{
		for (auto& b : vecb)
		{
			if (b.name == o.maintainer)
			{
				b.order = to_string(o.id);
				return true;
			}
		}
		return false;
	}
}

//////////////////// MENUS ////////////////////

void main_menu(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca)
{
	system("cls");
	cout << "MAIN MENU" << endl << endl;
	cout << "1 -> Show the list of brigades\n" << "2 -> Show the list of orders\n" << "3 -> Sign in as an administrator\n" << "4 -> Exit\n\n";
	while (true)
	{
		switch (_getch())
		{
		case '1':
			show_brigades(vecb, veco, veca);
			break;
		case '2':
			show_orders(vecb, veco, veca);
			break;
		case '3':
			sign_in(vecb, veco, veca);
			break;
		case '4':
			cout << "Exitting ";
			Sleep(400);
			cout << ". ";
			Sleep(400);
			cout << ". ";
			Sleep(400);
			cout << ". ";
			Sleep(400);
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
    if (size(vecb) > 0)
    {
        for (auto & i : vecb) //for every reference to element i in vecb -> cout i
            cout << i << endl;
        cout << "\n1 -> Show TOP-3 brigades" << endl << "2 -> Quit";
        while (true)
        {
            switch (_getch())
            {
            case '1':
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
        cout << "There are no registered brigades!\n" << "Press any key to quit.";
        _getch();
        main_menu(vecb, veco, veca);
    }
}

void show_top_brigades(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca)
{
    system("cls");
    vector<Brigade> top = vecb;
    sort(top.begin(), top.end(), [](const Brigade& a,const Brigade& b) { return a.completed > b.completed; });
    for (unsigned int i = size(top) - 1; i > size(top) - 3; i--)
        cout << top[i] << endl;
    cout << "\nPress any key to quit.";
    _getch();
    main_menu(vecb, veco, veca);
}

void show_orders(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca)
{
    system("cls");
    for (auto & i : veco)//for every reference to element i in veco -> cout i
        cout << i << endl;
    if(size(veco) < 1)
        cout << "There are no registrated orders!\n" << "Press any key to quit.";
    _getch();
    main_menu(vecb, veco, veca);
}

void sign_in(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca)
{
    string logpass;
    system("cls");
    while (true)
    {
        cout << "Write \"quit\" to quit.\n\nLogin: ";
        getline(cin, logpass);
        if (logpass == "quit" || logpass == "Quit")
            main_menu(vecb, veco, veca);
        int i;
        for (i = 0; i < size(veca); i++)
        {
            if (logpass == veca[i].login)
            {
                while (true)
                {
                    cout << "Password: ";
                    getline(cin, logpass);
                    if (logpass == "quit" || logpass == "Quit")
                        main_menu(vecb, veco, veca);
                    if (logpass == veca[i].password)
                    {
                        successfull();
                        admin_menu(vecb, veco, veca, i);
                    }
                    else
                    {
                        system("cls");
                        cout << "Wrong password! Try again." << endl << endl;
                    }
                }
            }
        }
        system("cls");
        cout << "Wrong login! Such administrator doesn't exist. Try again.\n";
    }
}

//////////////////// ADMIN'S MENUS ////////////////////

void admin_menu(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca, int& i)
{
	while (true)
	{
		system("cls");
		cout << "Welcome, " << veca[i].login << endl << endl;
		cout << "1 -> Manage brigades\n" << "2 -> Manage orders\n" << "3 -> Edit my account\n" << "4 -> Register a new administrator\n" << "5 -> Exit\n\n";
		switch (_getch())
		{
		case '1':
			manage_brigades(vecb, veco, veca, i);
			break;
		case '2':
			manage_orders(vecb, veco, veca, i);
			break;
		case '3':
			edit_account(vecb, veco, veca, i);
			break;
		case '4':
			sign_up(vecb, veco, veca, i);
			break;
		case '5':
			cout << "Exitting ";
			Sleep(400);
			cout << ". ";
			Sleep(400);
			cout << ". ";
			Sleep(400);
			cout << ". ";
			Sleep(400);
			exit(0);
		}
	}
}

void manage_brigades(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca, int& i)
{
	if (size(vecb) > 0)
	{
		system("cls");
		for (auto& i : vecb) //for every reference to element i in vecb -> cout i
			cout << i << endl;
		cout << endl << "1 -> Show TOP-3 brigades\n" << "2 -> Add new brigade\n" << "3 -> Edit brigade\n" << "4 -> Delete brigade\n" << "5 -> Quit" << endl << endl;
		string name;
        Brigade buffb;
        while (true)
        {
            switch (_getch())
            {
            case '1':
                show_top_brigades(vecb, veco, veca, i);
                break;
            case '2':
                system("cls");
                cin >> buffb;
                vecb.push_back(buffb);
                save_brigade(buffb, veco);
                sync(vecb);
                sync(veco);
                break;
            case '3':
                while (true)
                {
                    cout << "Enter the name of the brigade you want to edit: ";
                    getline(cin, name);
                    if (name == "quit" || name == "Quit")
                        manage_brigades(vecb, veco, veca, i);
                    for (auto& b : vecb)
                    {
                        if (name == b.name)
                        {
                            b.edit();
                            save_brigade(b, veco);
                            sync(vecb);
                            sync(veco);
                            manage_brigades(vecb, veco, veca, i);
                        }
                    }
                    cout << "Brigade with such name doesn't exist! Try again or write \"quit\" to quit.\n";
                }
                break;
            case '4':
                while (true)
                {
                    cout << "Enter the name of the brigade you want to delete: ";
                    getline(cin, name);
                    if (name == "quit" || name == "Quit")
                        manage_brigades(vecb, veco, veca, i);
                    for (auto& b : vecb)
                    {
                        if (name == b.name)
                        {
                            b.make_deleted();
                            save_brigade(b, veco);
                            sync(veco);
                            delete_deleted(vecb);
                            sync(vecb);
                            manage_brigades(vecb, veco, veca, i);
                        }
                    }
                    cout << "Brigade with such name doesn't exist! Try again or write \"quit\" to quit.\n";
                }
                break;
            case '5':
                admin_menu(vecb, veco, veca, i);
            }
        }
    }
    else
    {
        system("cls");
        cout << "There are no registered brigades!\n";
        cout << "\n1 -> Add new brigade\n" << "2 -> Quit" << endl << endl;
        string name;
        Brigade buffb;
        while (true)
        {
            switch (_getch())
            {
            case '1':
                system("cls");
                cin >> buffb;
                vecb.push_back(buffb);
                save_brigade(buffb, veco);
                sync(vecb);
                sync(veco);
                break;
            case '2':
                admin_menu(vecb, veco, veca, i);
            }
        }
    }
}

void show_top_brigades(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca, int& i)
{
    system("cls");
    if (size(vecb) > 0)
    {
        vector<Brigade> top = vecb;
        sort(top.begin(), top.end(), [](const Brigade& a, const Brigade& b) { return a.completed > b.completed; });
        for (unsigned int i = size(top) - 1; i > size(top) - 3; i--)
            cout << top[i] << endl;
    }
    else
    {
        cout << "There are no registered brigades!";
    }
    cout << "\nPress any key to quit.";
    _getch();
    admin_menu(vecb, veco, veca, i);
}

void manage_orders(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca, int& i)
{
	if (size(veco) > 0)
	{
		system("cls");
		for (auto& i : veco) //for every reference to element i in vecb -> cout i
			cout << i << endl;
		cout << endl << "1 -> Mark order as completed\n" << "2 -> Add new order\n" << "3 -> Edit order\n" << "4 -> Delete order\n" << "5 -> Quit" << endl << endl;
		string ID;
		Order buffo;
		while (true)
		{
			switch (_getch())
			{
			case '1':
				while (true)
				{
					cout << "Enter ID of order you want to mark as completed: ";
					getline(cin, ID);
					if (ID == "quit" || ID == "Quit")
						manage_orders(vecb, veco, veca, i);
					for (auto& o : veco)
					{
						if (stoi(ID) == o.id)
						{
							o.isCompleted = true;
							sync(veco);
                            for (auto& b : vecb)
                            {
                                if (o.id == stoi(b.order))
                                {
                                    ++b.completed;
                                }
                            }
                            successfull();
							manage_orders(vecb, veco, veca, i);
						}
					}
					cout << "Order with such ID doesn't exist! Try again or write \"quit\" to quit." << endl << endl;
				}
			case '2':
				system("cls");
				cin >> buffo;
                save_order(buffo, vecb);
				veco.push_back(buffo);
				sync(veco);
                sync(vecb);
			case '3':
				while (true)
				{
					cout << "Enter ID of order you want to edit: ";
					getline(cin, ID);
					if (ID == "quit" || ID == "Quit")
						manage_orders(vecb, veco, veca, i);
					for (auto& o : veco)
					{
						if (stoi(ID) == o.id)
						{
							o.edit();
                            save_order(o, vecb);
							sync(veco);
                            sync(vecb);
							manage_orders(vecb, veco, veca, i);
						}
					}
					cout << "Order with such ID doesn't exist! Try again or write \"quit\" to quit.\n";
				}
			case '4':
				while (true)
				{
					cout << "Enter ID of order you want to delete or write \"quit\" to quit: ";
					getline(cin, ID);
					if (ID == "quit" || ID == "Quit")
						manage_orders(vecb, veco, veca, i);
					for (auto& o : veco)
					{
						if (stoi(ID) == o.id)
						{
							o.make_deleted();
                            save_order(o, vecb);
                            sync(vecb);
							delete_deleted(veco);
							sync(veco);
							manage_orders(vecb, veco, veca, i);
						}
					}
					cout << "Order with such ID doesn't exist! Try again or write \"quit\" to quit.\n";
				}
			case '5':
				admin_menu(vecb, veco, veca, i);
			}
		}
	}
	else
	{
        system("cls");
		cout << "There are no registered orders!" << endl;
        cout << "\n1 -> Add new order\n" << "2 -> Quit" << endl << endl;
        string ID;
        Order buffo;
        while (true)
        {
            switch (_getch())
            {
            case '1':
                system("cls");
                cin >> buffo;
                save_order(buffo, vecb);
                sync(vecb);
                veco.push_back(buffo);
                sync(veco);
            case '2':
                admin_menu(vecb, veco, veca, i);
            }
        }
	}
}

void edit_account(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca, int& i)
{
    string input;
    while (true)
    {
        system("cls");
        cout << "1 -> Change login\n" << "2 -> Change password\n" << "3 -> Delete this account (careful!)\n" << "4 -> Quit" << endl << endl;
        switch (_getch())
        {
        case '1':
            while (true)
            {
                cout << "\nEnter new login: ";
                getline(cin, input);
                if (input == "quit" || input == "Quit")
                    break;
                if (login_size(input))
                {
                    if (clean_login(input))
                    {
                        veca[i].login = input;
                        successfull();
                        sync(veca);
                        break;
                    }
                    else
                        cout << "Login can include latin letters, numbers and symbols \"-\" and \"_\". Try again or write \"quit\" to quit.\n";
                }
                else
                    cout << "Login should include 3-30 symblos. Try again or write \"quit\" to quit.\n";
            }
            break;

        case '2':
            while (true)
			{
				cout << "\nEnter new password: ";
				getline(cin, input);
				if (input == "quit" || input == "Quit")
					break;
				if (password_size(input))
				{
					if (clean_password(input))
					{
						veca[i].password = input;
                        successfull();
                        sync(veca);
						break;
					}
					else
						cout << "Password can include latin letters and numbers. Try again or write \"quit\" to quit.\n";
				}
				else
					cout << "Password should include 8-24 symblos. Try again or write \"quit\" to quit.\n";
			}
            break;

        case '3':
            if (size(veca) == 1)
            {
                cout << "\nYou are the only administrator! Your account can't be deleted. Press any key to cancel.";
                _getch();
            }
            else
            {
                cout << "\nAre you sure to delete your account? It won't be possible to cancel! Enter \"DELETE\" to confirm or anything else to cancel.";
                getline(cin, input);
                if (input == "DELETE")
                {
                    veca[i].make_deleted();
                    cout << "\n\nDeleting ";
                    Sleep(600);
                    cout << ". ";
                    Sleep(600);
                    cout << ". ";
                    Sleep(600);
                    cout << ". ";
                    Sleep(600);
                    delete_deleted(veca);
                    cout << "Successfully deleted.";
                    Sleep(600);
                    sync(veca);
                    main_menu(vecb, veco, veca);
                }
                else
                {
                    cout << "\n\nCanceled.";
                    Sleep(600);
                }
            }
            break;

        case '4':
            admin_menu(vecb, veco, veca, i);
        }
    }
}

void sign_up(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca, int& i)
{
    Admin buffa;
    system("cls");
    cin >> buffa;
    veca.push_back(buffa);
    sync(veca);
}
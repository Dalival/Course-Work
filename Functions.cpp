#include "Classes.h"

//////////////////// UTILITY ////////////////////

bool yes_or_no(const string& msg)
{
    do
    {
        cout << endl << msg << " y/n";
        switch (_getch())
        {
            case 'y':
                system("cls");
                return true;
            case 'n':
                return false;
            default:
                break;
        }
    } while (true);
}

void flush_cin()
{
    cin.clear();
    cin.ignore(32767, '\n');
}

void fancy_dots(unsigned delay = 400)
{
    Sleep(delay);
    cout << ". ";
    Sleep(delay);
    cout << ". ";
    Sleep(delay);
    cout << ". ";
    Sleep(delay);
}

//////////////////// ADMIN'S METHODS ////////////////////

istream& operator>> (istream& in, Admin& a)
{
    string input;
    while (true)
    {
        cout << "Enter the login of new administrator: ";
        getline(cin, input);
        if (check_size(input,3,30))
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
		if (check_size(input,8,24))
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
    cout << "Success!" << endl;
    fancy_dots();
    return in;
}

ostream& operator<< (ostream& out, const Admin& a)
{
    cout << a.login << endl;
    return out;
}

ifstream& operator>> (ifstream& fin, Admin& a)
{
    if (fin.peek() == EOF)
        return fin;
    getline(fin, a.login);
    getline(fin, a.password);
    a.login = encryptDecrypt(a.login);
    a.password = encryptDecrypt(a.password);
    return fin;
}

ofstream& operator<< (ofstream& fout, const Admin& a)
{
    fout << encryptDecrypt(a.login) << endl;
    fout << encryptDecrypt(a.password) << endl;
    return fout;
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
    cout << "Success!" << endl;
    fancy_dots();
    return in;
}

ostream& operator<< (ostream& out, const Brigade& b)
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
        return fin;
    string temp;
    getline(fin, b.name);
    getline(fin, temp);
    b.people = stoi(temp);
    getline(fin, b.order);
    getline(fin, temp);
    b.completed = stoi(temp);
    return fin;
}

ofstream& operator<< (ofstream& fout, const Brigade& b)
{
    fout << b.name << endl;
    fout << b.people << endl;
    fout << b.order << endl;
    fout << b.completed << endl;
    return fout;
}

void Brigade::edit()
{
	while (true)
	{
        system("cls");
		cout << "1 -> Edit name \n2 -> Edit number of people \n3 -> Change active order" << endl;
		switch (_getch())
		{
            case '1':
                system("cls");
                cout << "Enter new name: ";
                getline(cin, name);
                cout << "New name: " << name;
                break;
            case '2':
                system("cls");
                scan(people, "Enter how many people are in brigade: ");
                cout << "Now " << name << " has " << people << " people.";
                break;
            case '3':
                system("cls");
                cout << "Enter ID of order: ";
                getline(cin, order);
                cout << "Now brigade maintain the order " << order;
                break;
            default:
                continue;
		}
        //TODO: Test
		if (!yes_or_no("Do you want to edit something else?")) return;
		//If the user said NO it will be inverted to true and we'll exit
	}
}

//////////////////// ORDER'S METHODS ////////////////////

istream& operator>> (istream& in, Order& o)
{
	string s;
	scan(o.id, "Enter ID of the project: ");
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
    cout << "Success!" << endl;
    fancy_dots();
	return in;
}

ostream& operator<< (ostream& out, const Order& o)
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
        return fin;
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

ofstream& operator<< (ofstream& fout, const Order& o)
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
	while (true)
	{
        system("cls");
		cout << "1 -> Edit customer \n2 -> Edit address \n3 -> Edit area \n4 -> Edit cost \n5 -> Move deadline \n6 -> Change project maintainer" << endl << endl;
		switch (_getch())
		{
		case '1':
            system("cls");
			cout << "Enter new customer: ";
			getline(cin, customer);
			cout << "New customer: " << customer;
			break;
		case '2':
            system("cls");
			cout << "Enter new address: ";
			getline(cin, address);
			cout << "New address: " << address;
			break;
		case '3':
            system("cls");
			scan(area, "Enter new area: ");
			cout << "New area: " << area;
			break;
		case '4':
            system("cls");
			scan(cost, "Enter new cost: ");
			cout << "New cost: " << cost;
			break;
		case '5':
            system("cls");
			cout << "Let's set new deadline.\n";
            deadline = enter_date();
            cout << "\nNew deadline: " << deadline;
			break;
		case '6':
            system("cls");
			cout << "Enter new maintaining brigade: ";
			getline(cin, maintainer);
			cout << "New maintainer: " << maintainer;
			break;
		default:
			continue;
		}
		if (!yes_or_no("Do you want to edit something else?")) return;
	}
}

//////////////////// OTHER ////////////////////

string enter_date() //TODO: Functions must not be long (>50 lines)
{
    time_t t = time(nullptr); //get the amount of seconds since year 1970
    tm* cur_date = localtime(&t); //conver it to a proper format using library <chrono>
    unsigned current_y = cur_date->tm_year, current_m = cur_date->tm_mon, current_d = cur_date->tm_mday; //assign it to values
    unsigned year = 0, month = 0, day = 0;
    while (true)
    {
        cout << "\nEnter the year: ";
        cin >> year;
        if (cin.fail())
        {
            system("cls");
            flush_cin();
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
            flush_cin();
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

    while (true) //TODO: bad style, use switch
    {
        cout << "Enter the day: ";
        cin >> day;
        if (cin.fail())
        {
            system("cls");
            flush_cin();
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
    flush_cin();
    return date;
}

void delete_deleted(vector<Brigade>& vec) //TODO: Horrible performance, refactor.
{
    vec.erase(remove_if(vec.begin(), vec.end(), [](const Brigade& br) { return br.people < 0; }), vec.end()); //Takes too long to do
    vec.shrink_to_fit(); //Completely redundant
}

void delete_deleted(vector<Order>& vec)
{
    vec.erase(remove_if(vec.begin(), vec.end(), [](const Order& ord) { return ord.cost < 0; }), vec.end());
    vec.shrink_to_fit();
}

void delete_deleted(vector<Admin>& vec)
{
    vec.erase(remove_if(vec.begin(), vec.end(), [](const Admin& adm) { return adm.login == "..."; }), vec.end());
    vec.shrink_to_fit();
}

string encryptDecrypt(const string& toEncrypt) {
    char key[3] = { 'F', 'E', 'A' }; // my initials
    string output = toEncrypt;
    for (unsigned int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))]; //TODO: Meaningless code
    return output;
}

bool clean_password(string& s)
{
    for (const char& ch : s)
        if (!isalnum(ch)) // if NOT alphanumeric or - or _ then return false
            return false;
    return true;
}

bool check_size(const string& s, size_t min, size_t max)
{
    return (s.size() >= min && s.size() <= max); //TODO: Merge functions?
}

bool clean_login(string& s)
{
    for (const char& ch : s) //reference
        if (!(isalnum(ch) || ch == '-' || ch == '_')) // if NOT alphanumeric or - or _ then return false
            return false;
    return true;
}

bool save_brigade(Brigade& b, vector<Order>& veco)
{
	if (b.people < 0)
	{
		for (auto& o : veco)
		{
			if (o.id == stoi(b.order))
			{
				o.maintainer = "no maintainer";
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
	cout << "MAIN MENU\n\n"
	     << "1 -> Show the list of brigades\n"
	     << "2 -> Show the list of orders\n"
	     << "3 -> Sign in as an administrator\n"
	     << "4 -> Exit\n" << endl;
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
                fancy_dots();
			exit(0); //TODO: NEVER USE EXIT()!
		default:
			continue;
		}
        break;
	}
}

void show_brigades(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca)
{
    system("cls");
    if (!vecb.empty())
    {
        for (const auto & i : vecb) //for every reference to element i in vecb -> cout i
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

void show_top_brigades(vector<Brigade> vecb, vector<Order>& veco, vector<Admin>& veca)
{
    system("cls");
    sort(vecb.begin(), vecb.end(), [](const Brigade& a,const Brigade& b) { return a.completed > b.completed; });
    for (unsigned int i = vecb.size() - 1; i > vecb.size() - 3; i--)
        cout << vecb[i] << endl;
    cout << "\nPress any key to quit.";
    _getch();
    main_menu(vecb, veco, veca);
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

void show_orders(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca)
{
    system("cls");
    for (const auto & i : veco) //for every reference to element i in veco -> cout i
        cout << i << endl;
    if(veco.empty())
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
        for (int i = 0; i < veca.size(); i++)
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
                        cout << "Success!" << endl;
                        fancy_dots();
                        admin_menu(vecb, veco, veca, i);
                    }
                    else
                    {
                        system("cls");
                        cout << "Wrong password! Try again." << endl << endl;
                    }
                    break;
                }
            }
        }
        system("cls");
        cout << "Wrong login! Such administrator doesn't exist. Try again.\n";
        break; //TODO: There was an endless loop. Is that intended?
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
                fancy_dots();
			exit(0); //TODO: Never use exit()
		}
	}
}

void manage_brigades(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca, int& i)
{
	if (size(vecb) > 0)
	{
		system("cls");
		for (const auto& b : vecb) //for every reference to element i in vecb -> cout i
			cout << b << endl;
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
                save(vecb,"brigades.txt");
                save(veco,"orders.txt");
                break;
            case '3':
                while (true)
                {
                    cout << "Enter the name of the brigade you want to edit: ";
                    getline(cin, name);
                    if (name == "quit" || name == "Quit") //TODO: Make a lowercase function
                        manage_brigades(vecb, veco, veca, i);
                    for (auto& b : vecb)
                    {
                        if (name == b.name)
                        {
                            b.edit();
                            save_brigade(b, veco);
                            save(vecb,"brigades.txt");
                            save(veco,"orders.txt");
                            manage_brigades(vecb, veco, veca, i);
                        }
                    }
                    cout << "Brigade with such name doesn't exist! Try again or write \"quit\" to quit.\n";
                    break; //TODO: There was an endless loop. Was that intended?
                }
                break;
            case '4':
                while (true)
                {
                    cout << "Enter the name of the brigade you want to delete: ";
                    getline(cin, name);
                    if (name == "quit" || name == "Quit")
                        manage_brigades(vecb, veco, veca, i);
                    for (auto& b : vecb) //TODO: Bad code
                    {
                        if (name == b.name)
                        {
                            b.make_deleted();
                            save_brigade(b, veco);
                            save(veco, "orders.txt");
                            delete_deleted(vecb);
                            save(vecb,"brigades.txt");
                            manage_brigades(vecb, veco, veca, i);
                        }
                    }
                    cout << "Brigade with such name doesn't exist! Try again or write \"quit\" to quit.\n";
                    break; //TODO: There was an endless loop. Was that intended?
                }
                break;
            case '5':
                admin_menu(vecb, veco, veca, i);
            }
            break; //TODO: There was an endless loop. Was that intended?
        }
    }
    else
    {
        system("cls");
        cout << "There are no registered brigades!\n" << "\n1 -> Add new brigade\n" << "2 -> Quit\n\n";
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
                save(vecb,"brigades.txt");
                save(veco,"orders.txt");
                break;
            case '2':
                admin_menu(vecb, veco, veca, i);
            }
        break; //TODO: Endless loop. Was that intended?
        }
    }
}

void manage_orders(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca, int& i)
{
	if (size(veco) > 0)
	{
		system("cls");
		for (const auto& o : veco) //for every reference to element i in vecb -> cout i
			cout << o << endl;
		cout << "\n1 -> Mark order as completed\n"
             << "2 -> Add new order\n"
             << "3 -> Edit order\n"
             << "4 -> Delete order\n"
             << "5 -> Quit\n" << endl;
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
                            save(veco, "orders.txt");
                            for (auto& b : vecb)
                            {
                                if (o.id == stoi(b.order))
                                {
                                    ++b.completed;
                                }
                            }
                            cout << "Success!" << endl;
                            fancy_dots();
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
                save(veco, "orders.txt");
                save(veco, "brigades.txt");
                break;
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
                            save(veco, "orders.txt");
                            save(veco, "brigades.txt");
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
                            save(vecb, "brigades.txt");
							delete_deleted(veco);
                            save(veco, "orders.txt");
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
                save(veco, "brigades.txt");
                veco.push_back(buffo);
                save(veco, "orders.txt");
                break;
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
                if (check_size(input,3,30))
                {
                    if (clean_login(input))
                    {
                        veca[i].login = input;
                        cout << "Success!" << endl;
                        fancy_dots();
                        save(veca, "administrators.txt");
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
				if (check_size(input,8,24))
				{
					if (clean_password(input))
					{
						veca[i].password = input;
                        cout << "Success!" << endl;
                        fancy_dots();
                        save(veca, "administrators.txt");
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
                    fancy_dots(600);
                    delete_deleted(veca);
                    cout << "Successfully deleted.";
                    Sleep(600);
                    save(veca, "administrators.txt");
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

void sign_up(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca, int& i) //TODO: Unused parameters!
{
    Admin buffa;
    system("cls");
    cin >> buffa;
    veca.push_back(buffa);
    save(veca, "administrators.txt");
}
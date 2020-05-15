#include "Classes.h"


//////////////////// UTILITY ////////////////////


bool yes_or_no(const string& msg) //do you want to... y/n
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

void fancy_dots(unsigned delay = 400) //to give time to read for user
{
    Sleep(delay);
    cout << ". ";
    Sleep(delay);
    cout << ". ";
    Sleep(delay);
    cout << ". ";
    Sleep(delay);
}

string encryptDecrypt(const string& toEncrypt) //for admin's data
{
    char key[3] = { 'F', 'E', 'A' }; // my initialsFedorenko Egor Alekseevich
    string output = toEncrypt;
    for (unsigned int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];
    return output;
}


//////////////////// ADMIN'S METHODS ////////////////////


istream& operator>> (istream& in, Admin& a)
{
    string input;
    while (true)
    {
        cout << "Enter the login of new administrator: ";
        getline(cin, input);
        if (input == "quit" || input == "Quit")
        {
            cout << "You can't use word \"quit\". It's reserved.\n";
        }
        else
        {
            if (check_size(input, 3, 30))
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
	}

    while (true)
    {
        cout << "Enter the password of new administrator: ";
        getline(cin, input);
        if (input == "quit" || input == "Quit")
        {
            cout << "You can't use word \"quit\". It's reserved.\n";
        }
        else
        {
            if (check_size(input, 8, 24))
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
    }
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
	{
		fin.ignore(32767, '\n'); //needed to avoid last element duplicating
		return fin;
	}
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
    return in;
}

ostream& operator<< (ostream& out, const Brigade& b)
{
    cout << "Brigade " << b.name << endl;
    cout << b.people << " people" << endl;
    cout << "Active order: ";
    if (b.order == 0)
        cout << "no active order" << endl;
    else
        cout << b.order << endl;
    cout << b.completed << " completed orders" << endl;
    return out;
}

ifstream& operator>> (ifstream& fin, Brigade& b)
{
    if (fin.peek() == EOF)
    {
        fin.ignore(32767, '\n'); //needed to avoid last element duplicating
        return fin;
    }
    string temp;
    getline(fin, b.name);
    getline(fin, temp);
    b.people = stoi(temp);
    getline(fin, temp);
    b.order = stoi(temp);
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

void Brigade::edit(vector<Brigade>& vecb)
{
	while (true)
	{
		cout << "1 -> Edit name \n2 -> Edit number of people \n3 -> Quit" << endl;
		switch (_getch())
		{
            case '1':
                system("cls");
                while (true)
                {
                    int it = 0;
                    cout << "Enter new name: ";
                    getline(cin, name);
                    if (!clean_login(name))
                    {
                        cout << "Brigade name can include latin letters, numbers and symbols \"-\" and \"_\"." << endl;
                        continue;
                    }
                    for (auto& br : vecb) //to avoid the same names of brigades
                    {
                        if (name == br.name)
                        {
                            it++;
                            if (it > 1)
                            {
                                cout << "Brigade with name " << name << " already exist." << endl;
                                break;
                            }
                        }
                    }
                    if (it > 1)
                        continue;
                    if (name == "quit" || name == "Quit") //possibility to go back
                    {
                        cout << "You can't use word \"quit\". It's reserved. Press any key to try again." << endl;
                        continue;
                    }
                    cout << "New name: " << name;
                    break;
                }
                break;
            case '2':
                system("cls");
                scan(people, "Enter how many people are in brigade: ");
                cout << "Now " << name << " has " << people << " people.";
                break;
            case '3':
                return;
		}
		if (!yes_or_no("Do you want to edit something else?")) return;
	}
}


//////////////////// ORDER'S METHODS ////////////////////


istream& operator>> (istream& in, Order& o)
{
	string s;

	cout << "Enter customer: ";
	getline(cin, o.customer);
    system("cls");

	cout << "Enter office address: ";
	getline(cin, o.address);
    system("cls");

	scan(o.area, "Enter area of the office in square meters: ");
    system("cls");

	scan(o.cost, "Enter cost of the project in dollars: ");
    system("cls");

    o.deadline = enter_date();
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
    {
        fin.ignore(32767, '\n'); //needed to avoid last element duplicating
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
    return fout;
}

void Order::edit(vector<Brigade>& vecb, vector<Order>& veco)
{
    string old_maintainer = maintainer;
	while (true)
	{
        bool isExist = false;
        string temp;
        system("cls");
        cout << *this << endl;
		cout << "1 -> Edit customer \n2 -> Edit address \n3 -> Edit area \n4 -> Edit cost \n5 -> Move deadline \n6 -> Change project maintainer \n7 -> Quit" << endl << endl;
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
            break;
        case '6':
            system("cls");
            for (const auto& i : vecb) //for every reference to element i in veco -> cout i
                cout << i << endl;
            cout << "Enter new maintaining brigade: ";
            getline(cin, temp);
            if (temp == "quit" || temp == "Quit")
                continue;
            for (auto& b : vecb)
            {
                if (b.name == temp)
                {
                    isExist = true;
                    for (auto& o : veco) // clean the maintainer-fill of order that was maintained by new brigade.
                    {
                        if (o.maintainer == temp)
                        {
                            o.maintainer = "no maintainer";
                            break;
                        }
                    }
                    b.order = id;
                    sync(b, veco);
                    break;
                }
			}
			if (!isExist)
			{
				cout << "There is no brigades with such name!.";
				continue;
			}
            for (auto& b : vecb) // clean the order fill of old brigade-maintainer
            {
                if (b.name == old_maintainer)
                    b.order = 0;
            }
			cout << "New maintainer: " << maintainer;
			break;
		case '7':
            return;
		}
		if (!yes_or_no("Do you want to edit something else?")) return;
	}
}


//////////////////// OTHER ////////////////////


string enter_date()
{
    time_t t = time(nullptr); //get the amount of seconds since year 1970
    tm* cur_date = localtime(&t); //convert it to a proper format
    unsigned current_y = cur_date->tm_year+1900, current_m = cur_date->tm_mon+1, current_d = cur_date->tm_mday; //assign it to values
    unsigned year = 0, month = 0, day = 0;
    bool go; //we go until finished
    string date;
	do //until the date is right, repeat
	{
		try //try to check date
		{
			go = false; //Don't go for now
			system("cls");
			cout << "Enter the deadline in the format DD.MM.YYYY : ";
			getline(cin, date);
			if (date.size() != 10) throw std::invalid_argument("Default case when parsing month");
			string temp{ date[0], date[1] }; //first two are day
			day = stoi(temp); //ATTEMPT to convert the input into numbers
			temp = { date[3], date[4] }; // month
			month = stoi(temp);
			temp = { date[6], date[7], date[8], date[9] }; //year
			year = stoi(temp); //If stoi throws, we catch it later.
			if (day == 0 //non-zero
				|| month == 0
				|| year == 0
				|| month > 12
				|| year > current_y + 50 //No more than 20 years to finish (change it for your needs)
				|| year < current_y //shouldn't be in the past
				|| (year == current_y && month < current_m) //if year is ok, check that month is not in the past
				|| (year == current_y && month == current_m && day < current_d))  //if month and year are ok, check the day
			{
				cout << "The date you entered is invalid\n";
				fancy_dots();
				go = true;
				continue; //continue to as the user for the date
			}
			switch (month)
			{
			case 1: //these statements fall through to next, and then again and so on
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				if (day > 31)
				{
					cout << "More than 31 days\n";
					fancy_dots();
					go = true;
				}
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				if (day > 30)
				{
					cout << "More than 30 days\n";
					fancy_dots();
					go = true;
				}
				break;
			case 2: //FEBRUARY
				if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
				{ //check for leap year
					if (day > 29)
					{
						cout << "More than 29 days\n";
						fancy_dots();
						go = true;
					}
				}
				else if (day > 28)
				{ //Not a leap year
					cout << "More than 28 days\n";
					fancy_dots();
					go = true;
				}
				break;
			default:
				throw invalid_argument("Default case when parsing month"); //Should never happen if we checked right
			}
		}
		catch (...) //Catch everything (including stoi() errors)
		{
			cout << "You didn't enter a date in the right format. Try again.\n";
			fancy_dots(600);
			go = true;
			continue; //Try again
		}
	} while (go);
	cout << "Success: ";
	cout << day << "." << month << "." << year << '\n';
	fancy_dots();
	return date;
}

void delete_deleted(vector<Brigade>& vec) //remove from vector brigades that was marked as deleted
{
    vec.erase(remove_if(vec.begin(), vec.end(), [](const Brigade& br) { return br.people < 0; }), vec.end()); //the best sort I've found
    vec.shrink_to_fit(); //why not
}

void delete_deleted(vector<Order>& vec) //remove from vector orders that was marked as deleted
{
    vec.erase(remove_if(vec.begin(), vec.end(), [](const Order& ord) { return ord.cost < 0; }), vec.end());
    vec.shrink_to_fit();
}

void delete_deleted(vector<Admin>& vec) //remove from vector admins that was marked as deleted
{
    vec.erase(remove_if(vec.begin(), vec.end(), [](const Admin& adm) { return adm.login == "..."; }), vec.end());
    vec.shrink_to_fit();
}

bool clean_password(string& s)
{
    for (const char& ch : s)
        if (!isalnum(ch)) //symbol is not a letter and is not a number
            return false;
    return true;
}

bool check_size(const string& s, size_t min, size_t max)
{
    return (s.size() >= min && s.size() <= max); //to avoid too long/short names/passwords
}

bool clean_login(string& s)
{
    for (const char& ch : s)
        if (!(isalnum(ch) || ch == '-' || ch == '_')) // if NOT alphanumeric or - or _ then return false
            return false;
    return true;
}

bool sync(Brigade& b, vector<Order>& veco) //if you change brigade the order that linked with it will be changed too
{
	if (b.people < 0)
	{
		for (auto& o : veco)
		{
			if (o.id == b.order)
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
			if (o.id == b.order)
			{
				o.maintainer = b.name;
				return true;
			}
		}
		return false;
	}
}

bool sync(Order& o, vector<Brigade>& vecb) //if you change order the brigade that linked with it will be changed too
{
	if (o.cost < 0)
	{
        for (auto& b : vecb)
        {
            if (b.name == o.maintainer)
            {
                b.order = 0;
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
				b.order = o.id;
				return true;
			}
		}
		return false;
	}
}


//////////////////// MENUS ////////////////////


void main_menu(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca)
{
    while(true)
    {
	system("cls");
    cout << "MAIN MENU\n\n"
         << "1 -> Show the list of brigades\n"
         << "2 -> Show the list of orders\n"
         << "3 -> Sign in as an administrator\n"
         << "4 -> Exit\n" << endl;
		switch (_getch())
		{
		case '1':
			show_brigades(vecb, veco, veca);
            break;
		case '2':
			show_orders(veco);
			break;
		case '3':
			sign_in(vecb, veco, veca);
			break;
		case '4':
			cout << "Exitting ";
                fancy_dots();
			exit(0); //end the program. I know I shouldn't use it but it's too hard to remake the core of the project
		}
	}
}

void show_brigades(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca)
{
	system("cls");
	for (const auto& i : vecb) //for every reference to element i in veco -> cout i
		cout << i << endl;
	if (vecb.empty())
	{
		cout << "There are no registered brigades! \nPress any key to quit.\n";
		_getch();
		return;
	}
	else
	{
		cout << "\n1 -> Show TOP-3 brigades \n2 -> Quit";
		switch (_getch())
		{
		case '1':
			show_top_brigades(vecb, veco, veca);
			break;
		case '2':
			return;
		}
	}
}

void show_top_brigades(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca) //my task from curator
{
    system("cls");
    if (size(vecb) > 3)
    {
        vector<Brigade> top = vecb;
        sort(top.begin(), top.end(), [](Brigade& a, Brigade& b) { return a.completed > b.completed; });
        for (size_t i = 0; i < 3; i++)
            cout << top[i] << endl;
    }
    else if (size(vecb) <= 3)
    {
        vector<Brigade> top = vecb;
        sort(top.begin(), top.end(), [](Brigade& a, Brigade& b) { return a.completed > b.completed; });
        for (size_t i = 0; i < size(top); i++)
            cout << top[i] << endl;
    }
    else // nothing to sort
	{
		cout << "There are no registered brigades!";
	}
	cout << "\nPress any key to quit.";
	_getch();
	main_menu(vecb, veco, veca);
}

void show_top_brigades(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca, int& i) //yes, the same function but with possibility to call admin_menu function
{
    system("cls");
    if (size(vecb) > 3)
    {
        vector<Brigade> top = vecb;
        sort(top.begin(), top.end(), [](Brigade& a, Brigade& b) { return a.completed > b.completed; });
        for (size_t i = 0; i < 3; i++)
            cout << top[i] << endl;
    }
    else if (size(vecb) <= 3)
    {
        vector<Brigade> top = vecb;
        sort(top.begin(), top.end(), [](Brigade& a, Brigade& b) { return a.completed > b.completed; });
        for (size_t i = 0; i < size(top); i++)
            cout << top[i] << endl;
    }
    else
    {
        cout << "There are no registered brigades!";
    }
    cout << "\nPress any key to quit.";
    _getch();
}

void show_orders(vector<Order>& veco)
{
    system("cls");
    for (const auto& i : veco) //for every reference to element i in veco -> cout i
        cout << i << endl;
    if (veco.empty())
        cout << "There are no registrated orders!\n";
    cout << "Press any key to quit.";
    _getch();
    return;
}

void sign_in(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca) //sign in as an admin
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
                        cout << "\nSuccess!";
                        fancy_dots();
                        admin_menu(vecb, veco, veca, i);
                    }
                    else
                    {
                        system("cls");
                        cout << "Wrong password! Try again.\n\n";
                        cout << "Login: " << veca[i].login << '\n';
                    }
                }
            }
        }
        system("cls");
        cout << "Wrong login! Such administrator doesn't exist. Try again.\n";
    }
}


//////////////////// ADMIN'S MENUS ////////////////////


void admin_menu(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca, int& i) //maim menu but with more features included
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
			sign_up(veca);
			break;
		case '5':
			cout << "Exitting ";
                fancy_dots();
			exit(0);
		}
	}
}

void manage_brigades(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca, int& i) //menu of brigades
{
    while (true)
    {
        if (size(vecb) > 0)
        {
            system("cls");
            string name;
            Brigade buffb;
            while (true)
            {
                for (const auto& b : vecb) //for every reference to element i in vecb -> cout i
                    cout << b << endl;
                cout << "\n1 -> Show TOP-3 brigades\n"
                    << "2 -> Add new brigade\n"
                    << "3 -> Edit brigade\n"
                    << "4 -> Delete brigade\n"
                    << "5 -> Quit\n" << endl;
                switch (_getch())
                {
                case '1':
                    show_top_brigades(vecb, veco, veca, i); //the version of function for admins (check passed  values)
                    break;
                case '2':
                    system("cls");
                    while (true)
                    {
                        bool duplicate = false;
                        cin >> buffb;
                        for (auto& b : vecb)
                        {
                            if (b.name == buffb.name)
                            {
                                cout << "\nBrigade with name " << buffb.name << " already exist. Press any key to try again." << endl;
                                _getch();
                                duplicate = true;
                                break;
                            }
                        }
                        if (buffb.name == "quit" || buffb.name == "Quit")
                        {
                            cout << "You can't use word \"quit\". It's reserved. Press any key to try again." << endl;
                            _getch();
                            continue;
                        }
                        if (duplicate)
                            continue;
                        vecb.push_back(buffb);
                        sync(buffb, veco); //changed linked order
                        save(vecb, "brigades.txt"); //save brigades in file
                        save(veco, "orders.txt"); //save orders in file
                        cout << "\nBrigade " << buffb.name << " was registrated!" << endl;
                        cout << "Success!";
                        fancy_dots();
                        break;
                    }
                    break;
                case '3':
                    while (true)
                    {
                        cout << "Enter the name of the brigade you want to edit: ";
                        getline(cin, name);
                        if (name == "quit" || name == "Quit")
                            manage_brigades(vecb, veco, veca, i); //back to main menu
                        for (auto& b : vecb)
                        {
                            if (name == b.name)
                            {
                                b.edit(vecb);
                                sync(b, veco);
                                save(vecb, "brigades.txt");
                                save(veco, "orders.txt");
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
                        for (auto& b : vecb) //TODO: Bad code
                        {
                            if (name == b.name)
                            {
                                b.make_deleted();
                                sync(b, veco);
                                save(veco, "orders.txt");
                                delete_deleted(vecb);
                                save(vecb, "brigades.txt");
                                manage_brigades(vecb, veco, veca, i);
                            }
                        }
                        cout << "Brigade with such name doesn't exist! ";
                        fancy_dots(600);
                        break; //TODO: There was an endless loop. Was that intended?
                    }
                    break;
                case '5':
                    admin_menu(vecb, veco, veca, i);
                }
                system("cls");
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
                    sync(buffb, veco);
                    save(vecb, "brigades.txt");
                    save(veco, "orders.txt");
                    break;
                case '2':
                    admin_menu(vecb, veco, veca, i);
                default:
                    continue;
                }
                break;
            }
        }
    }
}

void manage_orders(vector<Brigade>& vecb, vector<Order>& veco, vector<Admin>& veca, int& i) //menu of orders
{
    while (true)
    {
        if (size(veco) > 0)
        {
            while (true)
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
                bool duplicate = true;
                switch (_getch())
                {
                case '1':
                    while (true)
                    {
                        cout << "Completed orders are removed from the list. Enter the ID of order you want to mark as completed: "; //yeah maybe I was shoud to create archive or smth
                        getline(cin, ID);
                        if (ID == "quit" || ID == "Quit")
                            manage_orders(vecb, veco, veca, i);
                        for (auto& o : veco)
                        {
                            if (stoi(ID) == o.id)
                            {
                                for (auto& b : vecb)
                                {
                                    if (o.id == b.order)
                                    {
                                        ++b.completed;
                                        b.order = 0;
                                    }
                                }
                                save(vecb, "brigades.txt");
                                cout << "Success!";
                                fancy_dots();
                                o.make_deleted();
                                delete_deleted(veco);
                                save(veco, "orders.txt");
                                manage_orders(vecb, veco, veca, i);
                            }
                        }
                        cout << "Order with such ID doesn't exist! Try again or write \"quit\" to quit." << endl << endl;
                    }
                case '2':
                    system("cls");
                    cin >> buffo;
                    while (duplicate)
                    {
                        duplicate = false;
                        if (!empty(veco))
                            buffo.id = veco[size(veco) - 1].id + 1;
                        for (auto& o : veco)
                        {
                            if (buffo.id == o.id)
                            {
                                duplicate = true;
                                break;
                            }
                        }
                    }
                    sync(buffo, vecb);
                    veco.push_back(buffo);
                    save(veco, "orders.txt");
                    save(vecb, "brigades.txt");
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
                                o.edit(vecb, veco);
                                sync(o, vecb);
                                save(veco, "orders.txt");
                                save(vecb, "brigades.txt");
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
                                sync(o, vecb);
                                save(vecb, "brigades.txt");
                                delete_deleted(veco);
                                save(veco, "orders.txt");
                                manage_orders(vecb, veco, veca, i);
                            }
                        }
                        cout << "Order with such ID doesn't exist! Try again or write \"quit\" to quit.\n";
                    }
                case '5':
                    admin_menu(vecb, veco, veca, i); //back to main menu
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
                    sync(buffo, vecb);
                    save(vecb, "brigades.txt");
                    veco.push_back(buffo);
                    save(veco, "orders.txt");
                    break;
                case '2':
                    admin_menu(vecb, veco, veca, i);
                }
                break;
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
        cout << "1 -> Change login\n"
             << "2 -> Change password\n"
             << "3 -> Delete this account (careful!)\n"
             << "4 -> Quit\n" << endl;
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
                        cout << "Success!";
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
                        cout << "Success!";
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
                cout << "\nAre you sure to delete your account? It won't be possible to cancel! \nEnter \"DELETE\" to confirm or anything else to cancel." << endl;
                getline(cin, input);
                if (input == "DELETE" || input == "delete" || input == "Delete") //to make administrator sure that this is an important decision
                {
                    veca[i].make_deleted();
                    cout << "\n\nDeleting ";
                    fancy_dots();
                    delete_deleted(veca);
                    cout << "\nSuccessfully deleted ";
                    fancy_dots();
                    save(veca, "administrators.txt");
                    main_menu(vecb, veco, veca);
                }
                else
                {
                    cout << "\n\nCanceled ";
                    fancy_dots();
                }
            }
            break;

        case '4':
            admin_menu(vecb, veco, veca, i);
        }
    }
}

void sign_up(vector<Admin>& veca) //only admin can register a new admin
{
    Admin buffa;
    bool duplicate = true;
    system("cls");
    while (duplicate) //to avoid the same logins of different admins
    {
        duplicate = false;
        cin >> buffa;
        for (auto& a : veca)
        {
            if (buffa.login == a.login)
            {
                cout << "\nAdmin with name \"" << buffa.login << "\" is already exist. Choose another name." << endl;
                duplicate = true;
                break;
            }
        }
    }
    veca.push_back(buffa);
    save(veca, "administrators.txt");
    system("cls");
    cout << "Administrator " << buffa.login << " was successfully registered ";
    fancy_dots();
    return;
}
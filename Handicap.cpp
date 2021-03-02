#include<iostream>
#include <string>
#include<windows.h>
#include<iomanip>

using namespace std;

class MyScreen
{
private:
	HANDLE screen;
public:
	MyScreen()
	{
		screen = GetStdHandle(STD_OUTPUT_HANDLE);

	}
	MyScreen(HANDLE s)
	{
		screen = s;
	}
	void placeCursor(int row, int col);
};

void MyScreen::placeCursor(int row, int col)
{
	COORD position;
	position.Y = row;
	position.X = col;

	SetConsoleCursorPosition(screen, position);
}
class WinMenu
{
private:
	int row;
	int col;
	int choice;
	MyScreen scr;
public:
	WinMenu(int r, int c)
	{
		row = r;
		col = c;
		scr.placeCursor(row, col);

	}
};
void display()
{
	cout << "				Simple Golf Handicapper\n";
	
	cout << "\n---------------------------------------------------------------------------------------";
	MyScreen scr;
	scr.placeCursor(25, 1);
	cout << "******************************************************************************************" << endl;
	cout << "| name | add | update | clear | list | help | save | quit |";
	
}

string command();
string username(string &name, int entry[], int &count, string &save, string &tempname);
void display_username(string &name, int &count, double &handicap);
void input_add(int row, int col, string &name, int entry[], double &handicap, int &count, string &strupdate);
void display_add(int row, int col, string &name, int entry[], int &count, double &handicap, int &num, double &low, double &high, int sort[], string &strupdate);
void help(int row, int col);
void clear(int entry[], int &count, string &name, double &handicap, double &low, double &high, string &strUpdate);
void update(int row, int col, string &name, int entry[], int &count, int sorted[], string &strUpdate);
void bubbleSortInt(int entry[], int &count, int sorted[]);
void handicap(int entry[], int &count, int sorted[], double &idx, int &num);
void save(string &name, int entry[], int &count, string &tempname, string &save);
void display_round(string &name, int &count, double &handicap);

int main()
{
	MyScreen scr;
	display();
    help(4, 1);
	string choice;
	
	WinMenu menu(27, 1);
	cout << "Command: ";
	choice = command();
	
	int array1[1000] = { 0 };
    int entry[1000] = { 0 };
	int sorted[1000] = { 0 };
	int number = 0;
	double idx = 0;
	int num = 0;
	double high = 0, low = 0;

	string name = " ";
	string string_save = " ";
	string tempName;
	string strUpdate = " ";
	while (choice != "q" && choice != "quit")
	{
		if (choice == "n" || choice == "name")
		{
			system("cls");
			name = username(name, entry, number, string_save, tempName);
			tempName = name;;
			system("cls");
			display();
			display_username(name, number, idx);
		}

		else if (choice == "a" || choice == "add")
		{
			system("cls");
			display();
			input_add(27, 1, name, array1, idx, number, strUpdate);

			for (int x = 0; x < number; x++)
			{
				entry[x] = array1[x];
			}
			
		}
		else if (choice == "l" || choice == "list")
		{
			system("cls");
			display();
			display_add(3, 1, name, entry, number, idx, num, low, high, sorted, strUpdate);
			
		}
		else if (choice == "u" || choice == "update")
		{
			system("cls");
			display();
			update(3, 0, name, entry, number, sorted, strUpdate);
			handicap(entry, number, sorted, idx, num);
		}
		else if (choice == "h" || choice == "help")
		{
			system("cls");
			display();
			help(3, 1);
			
		}
		else if (choice == "s" || choice == "save")
		{
			system("cls");
			display();
			save(name, entry, number, tempName, string_save);

		}
		else if (choice == "c" || choice == "clear")
		{
			system("cls");
			display();
			clear(entry, number, name, idx, low, high, strUpdate);
			
		}
		cin.ignore();
		scr.placeCursor(27, 1);
		cout << "Command: ";
		choice = command();
	}

	return 0;
}
   

string command()
{
	MyScreen scr;
	string c;
	cin >> c;
	
	
		while (c != "n" && c != "name" && c != "a" && c != "add" && c != "update" && c != "u" && c != "clear" && c != "c" && c != "list" && c != "l" && c != "help" && c != "h" && c != "save" && c != "s" && c != "q" && c != "quit")
		{
			system("cls");
			display();
			WinMenu menu(5, 1);
			cout << "Invalid Selection " << c;
			scr.placeCursor(27, 1);
			cout << "Command: ";
			cin >> c;
		}
	
	return c;
}
string username(string &name, int entry[], int &count, string &save, string &tempname)
{
	
	system("cls");
	MyScreen scr;
	display();
	string temp = tempname;

	WinMenu menu(27, 0);
	cout << "Enter an existing or new UserName.                                                                 \n";
	cout << "Username:";
	cin >> name;


	if (save == " ")
	{
		for (int x = 0; x < count; x++)
		{
			entry[x] = 0;
		}
		count = 0;

		if (temp != name)
		{
			for (int x = 0; x < count; x++)
			{
				entry[x] = 0;
			}
			count = 0;
		}
	}
	if (save == "save")
	{

		if (temp != name)
		{
			for (int x = 0; x < count; x++)
			{
				entry[x] = 0;
			}
			count = 0;
		}
	}
	return name;
}

void display_username(string &name, int &count, double &handicap)
{
	MyScreen scr;
	display_round(name, count, handicap);
	scr.placeCursor(3, 1);
	cout << count << " rounds loaded for user " << name;
}

void input_add(int row, int col, string &name, int entry[], double &handicap, int &counter, string &strupdate)
{

	MyScreen scr;
	
	scr.placeCursor(row, col);
	
	cout << "Add one or more scores separated by space, input is terminated by new line\n";
	cout << "enter scores: ";

	char peek_char;
	int count = counter;
	int show = 0;
	while (count < 10000)
	{
		cin >> entry[count];
		count++;
		counter++;
		show++;
		peek_char = cin.peek();

		while (peek_char == ' ')  
		{
			peek_char = cin.get();  
			peek_char = cin.peek();
		}

		if (peek_char == '\n')   
			break;
	}
	if (count > 20)
	{
		int rem;
		int x;
		rem = count - 20;
		for (x = 0; x < rem; x++)
		{
			entry[x] = 0;
		}
		for (int y = 0; y < 20, rem <= count; y++, rem++)
		{
			entry[y] = entry[rem];
		}
		for (int x = 20; x < count; x++)
		{
			entry[x]=0;
		}
		counter = 20;
	}
	
	system("cls");
	display();

    display_round(name, count, handicap);
	
	scr.placeCursor(3, 1);
	cout << show << " scores added\n";
	strupdate = " ";
	
}

void display_add(int row, int col, string &name, int entry[], int &count, double &handicap, int &num, double &low, double &high, int sorted[], string &strupdate)
{
	MyScreen scr;
	
	int x;
	int y ;
	int z = 0;
	int temp[10000] = { 0 };

	for (int a = 0; a < count; a++)
	{
		temp[a] = entry[a];
	}

	
		for (y = 0; y < num; y++)
		{
			for (x = 0; x < count; x++)
			{

				if (entry[x] == sorted[y])
				{
					scr.placeCursor(x + 4, col + 12);
					cout << " *";
					sorted[y] = 0;
					entry[x] = 0;
				}

			}
		}

		for (int a = 0; a < count; a++)
		{
			entry[a] = temp[a];
		}

		scr.placeCursor(row, col);
		cout << "Round   Score - * indicates score was used in handicap calculation      \n";
		if (count > 10)
		{
			for (x = 0; x < 9; x++)
			{
				cout << "  " << x + 1 << "        " << entry[x] << endl;
			}
			for (x = 9; x < count; x++)
			{
				cout << "  " << x + 1 << "       " << entry[x] << endl;
			}
		}
		else
			for (x = 0; x < count; x++)
			{
				cout << "  " << x + 1 << "        " << entry[x] << endl;
			}
	
	
	
	if (low == 0)
	{
		low = handicap;

	}
	if (high < handicap)
		high = handicap;
	if (low >= handicap && high >= handicap)
		low = handicap;
	else
		low = low;
	
	if (low == 0 && high == 0)
	{
		cout << "Lowest Handicap: " << "none";
		cout << "     Highest Handicap: " << "none";
		
	}
	
	else
	{
		cout << "Lowest Handicap: " << low;
		cout << "     Highest Handicap: " << high;
	}

	display_round(name, count, handicap);
	
	
}

void bubbleSortInt(int entry[], int &count, int sorted[])
{
	int temp;
	bool madeAswap;

	for (int s = 0; s < count; s++)
	{
		sorted[s] = entry[s];
	}
	do
	{
		madeAswap = false;
		for (int idx = 0; idx < (count - 1); idx++)
		{
			if (sorted[idx] > sorted[idx + 1])
			{
				temp = sorted[idx];
				sorted[idx] = sorted[idx + 1];
				sorted[idx + 1] = temp;
				madeAswap = true;
			}
		}
	} while (madeAswap);

}

void update(int row, int col, string &name, int entry[], int &count,int sorted[], string &strUpdate)
{
	MyScreen scr;

	bubbleSortInt(entry, count, sorted);
	scr.placeCursor(4, 1);
	cout <<"Scores updated\n";
	int x = 0;
	strUpdate = "update";


}


void handicap(int entry[], int &count, int sorted[], double &idx, int &num)
{
	int diff = 0;
	double sum = 0;
	num = 0;
	int  times = 0;

	if (count < 5)
	{
		num = 0;
	}
	else if (count > 4 && count < 7)
	{
		num = 1;
	}
	else if (count > 6 && count < 9)
	{
		num = 2;
	}
	else if (count > 8 && count < 11)
	{
		num = 3;
	}
	else if (count > 10  && count < 13)
	{
		num = 4;
	}
	else if (count > 12 && count < 15)
	{
		num = 5;
	}
	else if (count > 14 && count < 17)
	{
		num = 6;
	}
	else if (count == 17)
	{
		num = 7;
	}
	else if (count == 18)
	{
		num = 8;
	}
	else if (count == 19)
	{
		num = 9;
	}
	else if (count == 20)
	{
		num = 10;
	}
	for (int c = 0; c < num; c++)
	{
			diff = sorted[c] - 72;
		

		sum += diff;
	}
	
	
	if (num != 0)
	{
		idx = (sum / num) * 0.96;
		float myval = idx;
		idx = ((int)(myval * 10)) / 10.0;
	}
	
	if (num == 0)
	{
		idx = 0;
	}
	if (idx > 36.4)
	{
		idx = 36.4;
	}
	if (idx < 0)
	{
		idx = 0;
	}

	
}

void help(int row,int col)
{
	MyScreen scr;
	scr.placeCursor(row, col);

	cout << "Commands:\n"
		<< "User <user>    The name of the user data (if any) to be loaded\n"
		<< "Add <#>        Followed by one or more scores to be added to the data\n"
		<< "Recalc         Recalculate the handicap and update history\n"
		<< "Clear          clears all recorded scores and handicap information\n"
		<< "List           Lists all recorded scores and handicap history\n"
		<< "Help           This help\n"
		<< "Save           Saves the current user data and exits the application\n"
		<< "Quit           Exits that application without saving any data\n\n"
		<< "Only the first character of the command is required at the prompt\n\n"
		<< "Arguments in <> may be entered immediately after command or when prompted.";
}

void clear(int entry[], int &count, string &name, double &handicap, double &low , double &high, string &strUpdate)
{
	MyScreen scr;
	scr.placeCursor(5, 1);
	handicap = 0;
	cout << "All data cleared";
	for (int x = 0; x < count; x++)
	{
		entry[x] = 0;
	}
	count = 0;
	strUpdate = " ";

}

void display_round(string &name, int &count, double &handicap)
{
	MyScreen scr;
	scr.placeCursor(1, 1);
	cout << "User: " << name << "\t\t";
	if (count == 0)
		cout << "Rounds: " << "none";
	else
		cout << "Rounds: " << count;
	if (handicap == 0)
		cout << "\t\t" << "Handicap: " << "none ";
	else
		cout << "\t\t" << "Handicap: " << handicap;

	
}
void save(string &name, int entry[], int &count, string &tempname, string &save)
{
	MyScreen scr;
	save = "save";

	
	
	if (name == " ")
	{
		name= username(name, entry, count, save, tempname);
	}
	
	system("cls");
	display();
	scr.placeCursor(28, 1);
		cout << "Data saved successfully\n";
	
}




// Name: Lewis Taylor  
// Student number: 18027909
// Project name: Cashier system c++ 
// Date: 19/12/19

// The software written below has been written to simulate a Cashier system.

 /*  The Cashier system does as follows:
   - Outputs welcome message.
   - Asks the customer to enter a barcode ranging from "0120001" ... "0120010".
   - I'f the customer types in an incorrect value, they will be presented with an 
     error message and asked to re-enter a barcode. 
   - I'f the customer enters "f" or "F", the total cost of the products selected are calculated. 
   - The system will then ask the user to input a value for the amount needed to complete the transaction.
   - I'f the amount recieved is not enough to complete the transaction, the system will ask for more cash. Otherwise
     if the amount received is over the required payment, the system will total the amount of change needed to give
	 back to the customer. 
   - The system will then ask the customer if they would like a reciept. If yes, then the customer can type, 
     "y", "Y", "yes" or "Yes  otherwise if no ("n", "N", "no", "No") then it will skip to ask for a new customer. 
   - The same applies for when the system asks whether there is a new customer or not. If there is, the system prints out
     a christmas greeting, if there isn't, it'll print out the Christmas greeting for the last time. 
   - The system will then begin at the start of the program if  "y", "Y", "yes" or "Yes" is specified. 
   */


#include <iostream> // Used for input output functionalities
#include <string> // Used to access the string data type. 
#include <iomanip> // Used in program to access keywords to format values. 
#include <fstream> // Used to input/output information to and from text files. 
#include <sstream>// Used in this program to convert string values to double. 
#include <windows.h> // Used to change the colour of text in command prompt. 

using namespace std; // std: :cout etc, std: :endl ;  
                       
 
int n; // Used as an index placeholder. 
int i = 0; 
string bcode; // Used to store barcode values.
string barcode[] = {"0120001", "0120002", "0120003", "0120004", "0120005", "0120006", "0120007", "0120008", "0120009", "0120010"}; 
//array of barcode strings
string product[] = {"Milk", "Bread", "Chocolate", "Towel", "Toothpaste", "Soap", "Pen", "Biscuits", "Lamp", "Battery"};
//array of product strings
double price[] = { 10.50, 5.50, 8.80, 12.10, 6.75, 5.20, 2.00, 4.45, 20.50, 10.00 };
//array of price strings

bool f1 = false; // Bool variables used to control the direction of when code is executed. 
bool f2 = false; // ^
bool f3 = false; // |
bool f4 = false; // |
bool f5 = false; // |  
double total_value; // Total of prices related to each index of the selected barcodes. 
double amount_recieved; // Total value of prices minus the amount of cash received. 
double real_cash = 0.00; /* Used as a capsel to store the converted 
                            string value of getline(cin, cash) into a double data type.*/
int index_conc = 0;      // Used to change the state of the index 'n'.
string next_customer;    // Used to store values inputed to it i.e. "y", "n" etc...
string pound = "\x9C";   /* Hexidecimal value for the pound symbol. Conversion of char(156) representation of the pound sign 
                            doesn't exist in visual studio. */
string cash; // Used to store inputted value.
ofstream outFile; // Outputs information from the program to .txt file.
ifstream inFile, christmasFile; // Inputs information from the .txt file to the program. 
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); /* HANDLE is a handle to an object. 
												   GETStdHandle() retrieves a handle to the 
												   specified standard device here: 
												   STD_OUTPUT_HANDLE. The standard output device.
												   Initially, this is the active console screen buffer.*/


// void functions can store multiple data types, but do not return a value back to the function. 
void welcome_Header()
{
	string s, s2, s3; // intialising strings. 
	s2 = "WELCOME TO HERTS SUPERMARKET CHECKOUT SYSTEM"; // Assigning qoutes to intialised variable. 
	s3 = "Scan the barcode or manually type the barcode ID"; // Assigning qoutes to intialised variable. 

	for (int i = 0; i < 54; i++) // This prints out "string 's'" continously until the condition is met. 
    {
		s = "*";
		cout << s;
    }
    
	cout << endl;

	cout << "*    " << s2 << "    *" << endl;
	cout << "*  " << s3 << "  *" << endl;

	for (int i = 0; i < 54; i++)
	{
		s = "*";
		cout << s;
	}
	cout << endl;
} 

void calc_Price()
{
	outFile.open("read_barcode.txt", ios::out); /* opens .txt file. Ios keyword acts as a precursor refirming that
	                                               the .txt file is an output file. */

	outFile << "_________________________________" << endl; // Outputs qoutes into .txt file. 
	
	outFile << "              RECEIPT            " << endl;

	outFile << setw(10) << "Item" << setw(11) << "Barcode" << setw(9) << "Price" << endl;
	outFile << endl; // setw is used to space qoutes outputted to the text file. 
	
	while (i != 1)
	{
		cout << "Barcode (Type 'f' to finsih): ";
		getline(cin, bcode); // Ignores spaces and anything after. 


		for (n = 0; n < 10; n++)
		{
			if (bcode == barcode[n]) 
			{
				outFile << setw(10) << product[n] << setw(11) << barcode[n]
					<< setw(5) << fixed << setprecision(2) << pound << price[n] << endl;
				outFile << endl; // Outputs qoutes into .txt file.

				total_value += price[n]; // adds up the value of each product in accordance to the prices index. 

				cout << "The product you have selected is: ";
				
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				// Sets the foreground(text) attributes of characters written to the console screen buffer.
				
				cout << product[n] << endl;
				
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				// Sets the foreground(text) attributes of characters written to the console screen buffer.

				index_conc = n; // while 4loop is running, index_conc will remain as an index value in relation to barcode[n].  

				break;
			}
			else
			{
				index_conc = -1; // does not correspond with any index related to barcode[n].
			}
		}
            if (bcode == "f" || bcode == "F")
			{
				cout << "Total value: " << pound << fixed << setprecision(2) << total_value << endl;
				
				index_conc = 0; // returns index_conc back into the arrays index range. 
				
				break; 
			}
			else if(index_conc == -1)
		    {
		    // Sets the foreground(text) attributes of characters written to the console screen buffer.
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // sets colour and intensity.
			
			cout << "Error occured (re-enter barcode)" << endl;
	
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			// Sets the foreground(text) attributes of characters written to the console screen buffer.
		    }
			
	}
		
	outFile << setw(21) << "Total: " << setw(5) << pound << fixed << setprecision(2) << total_value << endl;

	outFile << "_________________________________" << endl;

	outFile.close(); // closes output file. 
}

void cash_needed()
{
	if (total_value > 0)
	{
		cout << endl;
		cout << "Cashed recieved: " << pound;
		getline(cin, cash);

		while (1)
		{
			if (!cin.fail()) // returns true when an input failure occurs (input is not an integer). 
			{
				istringstream is(cash);

				is >> real_cash;

				/*stringstream cash(cash); // converts string value into double data type.

				cash >> real_cash; // passes value over to new variable. */

				break;
			}
		}
	}
	if (total_value <= real_cash)
	{
		amount_recieved = real_cash - total_value; // when value less than or equal to. 
		f1 = true;
	}
	else
	{
		total_value -= real_cash; // otherwise the value of cash is taken away until total_value is 0. 
	}
	while (f1 != true)
	{
		real_cash = 0; 

		SetConsoleTextAttribute(hConsole, 5 | FOREGROUND_INTENSITY); // '5' represents purple. 
		cout << "[i]"; 
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		
		cout << "More cash needed : " << pound << fixed << setprecision(2) << total_value << endl;
		cout << endl; 
		
		cout << "Cashed recieved: " << pound;
		getline(cin, cash);

		while (1)
		{
			if (!cin.fail())
			{
				istringstream is(cash);

				is >> real_cash;
				
				/*stringstream cash(cash);

				cash >> real_cash;*/

				break;
			}
		}

		if (total_value <= real_cash)
		{
			amount_recieved = real_cash - total_value;
			f1 = true;
		}
		else 
		{
			total_value -= real_cash; 
		}
	}
	cout << endl; 
	cout << "Change: " << pound << fixed << setprecision(2) << amount_recieved << endl;
	// fixed and setprecision used to format value inputted. 
}

void print_receipt()
{

	while (f2 != true)
	{
		if (f3 != true)
		{
			cout << "Print receipt? (Y/N): ";
			getline(cin, next_customer); 
		}

		if (next_customer == "y" || next_customer == "Y" || next_customer == "Yes")
		{
			
			string receipt_info; 
			
			int count = 0; 
			
			inFile.open("read_barcode.txt"); // Opens file.
			
			for (count ;!inFile.eof(); count ++) // Reads to the end of the file. 
			{
				getline(inFile, receipt_info); // Assigns .txt file data to receipt_info
				cout << receipt_info << endl; 
			}
		  
			inFile.close(); // Closes file.
			
			break;
		}
		else if (next_customer == "n" || next_customer == "N" || next_customer == "No")
		{
			f2 = true;
		}
		else 
		{
			f3 = true; 
			cout << endl;
			SetConsoleTextAttribute(hConsole, 5 | FOREGROUND_INTENSITY);
			cout << "[!]";
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			
			cout << "Please press y for Yes, and n for No: ";
			getline(cin, next_customer); 
		}
		
	}
}

void calc_Nextcustomer()
{
	cout << endl;
	cout << "Next customer (Y/N) : ";
	while (f5 != true)
	{
		getline(cin, next_customer);

		if (next_customer == "Y" || next_customer == "yes" || next_customer == "y" || next_customer == "Yes" || next_customer == "YES") {

			f4 = false;
			f5 = true;

		}
		else if (next_customer == "N" || next_customer == "no" || next_customer == "n" || next_customer == "No" || next_customer == "NO") {

			f4 = true;
			f5 = true;

		}
		else
		{
			cout << endl; 
			SetConsoleTextAttribute(hConsole, 5 | FOREGROUND_INTENSITY);
			cout << "[!]"; 
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			
			cout << "Please press y for Yes, and n for No: ";
        }
    }
	cout << endl;
}

void christmas_Greet()
{
	string christmas;

	int count = 0;

	christmasFile.open("Christmas_greet.txt");

	for (count; !christmasFile.eof(); count++)
	{
		getline(christmasFile, christmas);
		cout << christmas << endl;
	}
	christmasFile.close();
}

int main()
{
	f4 = false;
	while (f4 != true)
	{
		// variables restored back to original values.
		f1 = false;
		f2 = false; 
		f3 = false; 
		f5 = false;
		index_conc = 0;  
		total_value = 0;
		real_cash = 0;
		amount_recieved = 0;

		welcome_Header();
		calc_Price();
		cash_needed();
		print_receipt();
		calc_Nextcustomer();
		christmas_Greet();

		if (next_customer == "N")
		{

			f4 = true;
		}
	}
	return 0; 
}
		
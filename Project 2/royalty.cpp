#include <iostream>;
#include <string>;
using namespace std;

int main()
{
	int units;
	double bPrice;
	string title, yn;

	// takes in the number of units
	cout << "Units sent: ";
	cin >> units;
	cin.ignore(10000, '\n');
	// checks to see if units is negative, which is an invalid input
	if (units < 0)
	{
		cout << "---" << endl;
		cout << "The number of units sent must be nonnegative.\n";
		return 1;
	}

	// records and stores the title of the movie
	cout << "Title: ";
	getline (cin, title);
	// checks to see if title is empty, which is an invalid input
	if (title == "")
	{
		cout << "---" << endl;
		cout << "You must enter a title.\n";
		return 1;
	}

	// takes in the base price
	cout << "Base price: ";
	cin >> bPrice;
	cin.ignore(10000, '\n');
	// checks to see if base price is negative, which is an invalid input
	if (bPrice < 0)
	{
		cout << "---" << endl;
		cout << "The base price must be nonnegative.\n";
		return 1;
	}

	// takes in a y or n
	cout << "Premium item? (y/n): ";
	getline (cin, yn);
	// input must be either y or n, so this checks to see if the input is invalid
	if ((yn != "y") && (yn != "n"))
	{
		cout << "---" << endl;
		cout << "You must enter y or n.\n";
		return 1;
	}

	// everything below calculates the total royalties
	double royal1;
	double royal2;
	double royal3;
	double totalRoyalties;

	// rounds each dollar amount to the nearest cent
	cout.setf(ios::fixed);
	cout.precision(2);

	// this calculates the first 400, the next 800, and anything after 1200 separately,
	// then adds them together for the total royalties earned. 

	// calculates royalty if it is not a premium item
	if (yn == "n")
	{
		if (units <= 400)
		{
			totalRoyalties = 0.09 * bPrice * units;
		}
		else if (units <= 1200)
		{
			royal1 = 0.09 * bPrice * 400;
			royal2 = 0.13 * bPrice * (units - 400);
			totalRoyalties = royal1 + royal2;
		}
		else
		{
			royal1 = 0.09 * bPrice * 400;
			royal2 = 0.13 * bPrice * 800;
			royal3 = 0.14 * bPrice * (units - 1200);
			totalRoyalties = royal1 + royal2 + royal3;
		}
	}

	// calculates royalty if it is a premium item
	if (yn == "y")
	{
		if (units <= 400)
		{
			totalRoyalties = 0.09 * bPrice * units;
		}
		else if (units <= 1200)
		{
			royal1 = 0.09 * bPrice * 400;
			royal2 = 0.16 * bPrice * (units - 400);
			totalRoyalties = royal1 + royal2;
		}
		else
		{
			royal1 = 0.09 * bPrice * 400;
			royal2 = 0.16 * bPrice * 800;
			royal3 = 0.14 * bPrice * (units - 1200);
			totalRoyalties = royal1 + royal2 + royal3;
		}
	}

	// this prints out the calculated dollar amount of the total royalties earned
	cout << "---" << endl;
	cout << title << " earned $" << totalRoyalties << " in royalties.\n";
}
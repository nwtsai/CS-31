#include <iostream>
#include <string>
#include "grid.h"
#include <cctype>
#include <cassert>

using namespace std;

bool isRouteWellFormed(string route)
{
	int count = 0;

	//returns true if string is empty
	if (route == "")
		return true;

	//returns false if first character is a number
	if (isdigit(route[0]))
		return false;
 
	for (int i = 0; i != route.size(); i++)
	{
		//checks if all characters are alphanumeric
		if (!isalnum(route[i]))
		{
			return false;
		}

		//if char is a letter, and is n,e,s,w, keeps check equal to true
		if (isalpha(route[i]))
		{
			char lowerDir = tolower(route[i]);
			if (!(lowerDir == 'n' || lowerDir == 'e' || lowerDir == 's' || lowerDir == 'w'))
			{
				return false;
			}
		}

		//counts the digits that follow a direction, if it's more than 2, returns false
		if (isdigit(route[i]))
		{
			count++;
		}
		else
		{
			count = 0;
		}
		if (count > 2)
		{
			return false;
		}
	}
	return true;
}

int navigateSegment(int r, int c, char dir, int maxSteps)
{
	int steps = 0;
	char tempDir = tolower(dir); //sets all letters to lowercase

    //checks for valid parameter inputs, and checks if [r,c] is a wall
	if (r > getRows() || r < 0 || c > getCols() || c < 0 || maxSteps < 0 || isWall(r, c))
	{
		return -1;
	}

	//individual loops for all four directions that describe which way for robot to step
	else if (tempDir == 'n')
	{
		for (int i = r - 1; (i >= r - maxSteps) && (i >= 1); i--)
		{
			if (isWall(i, c))
			{
				return steps;
			}
			steps++;
		}
		return steps;
	}
	else if (tempDir == 's')
	{
		for (int i = r + 1; (i <= r + maxSteps) && (i <= getRows()); i++)
		{
			if (isWall(i, c))
			{
				return steps;
			}
			steps++;
		}
		return steps;
	}
	else if (tempDir == 'e')
	{
		for (int i = c + 1; (i <= c + maxSteps) && (i <= getCols()); i++)
		{
			if (isWall(r, i))
			{
				return steps;
			}
			steps++;
		}
		return steps;
	}
	else if (tempDir == 'w')
	{
		for (int i = c - 1; (i >= c - maxSteps) && (i >= 1); i--)
		{
			if (isWall(r, i))
			{
				return steps;
			}
			steps++;
		}
		return steps;
	}

	//returns -1 if the direction is something other than n,s,e,w
	else
	{
		return -1;
	}
}

int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps)
{
	//returns 2 for bad input
	if (isRouteWellFormed(route) == false || sr < 0 || sc < 0 || er < 0 || ec < 0 || sr > getRows() ||
		sc > getCols() || er > getRows() || ec > getCols() || isWall(sr, sc) || isWall(er, ec))
	{
		return 2;
	}

	nsteps = 0;

	int tempRow = sr;
	int tempCol = sc;
	int tempLength = 0;

	//for loop that loops thru each character in the string
	for (int i = 0; i < route.size(); i++)
	{
		tempLength = 0;	// the integer value of the number that follows each letter

		char dir = ' ';	// holds the direction of the route segment

		//finds each route segment, sets letter to dir, sets number to routeLength
		if (isalpha(route[i]))
		{
			dir = tolower(route[i]);

			if ((i + 1) < route.size() && isdigit(route[i + 1]))
			{
				tempLength = route[i + 1] - '0';

				if ((i + 2) < route.size() && isdigit(route[i + 2]))
				{
					tempLength = (route[i + 1] - '0') * 10 + (route[i + 2] - '0');
					i++;
				}
				i++;
			}
			else if (isalpha(route[i + 1]) && (i + 1) < route.size())
			{
				tempLength = 1;
			}
			else
			{
				tempLength = 1;
			}

			// if navigateSegment returns something smaller than the tempLength, it means it hit a wall or hit a boundary, so return 3.
			if (navigateSegment(tempRow, tempCol, dir, tempLength) < tempLength)
			{
				nsteps += navigateSegment(tempRow, tempCol, dir, tempLength);
				return 3;
			}

			// changes to Row and Col depend on the direction
			// locates robot's position after every route segment
			if (dir == 'n')
				tempRow = tempRow - tempLength;
			if (dir == 's')
				tempRow = tempRow + tempLength;
			if (dir == 'w')
				tempCol = tempCol - tempLength;
			if (dir == 'e')
				tempCol = tempCol + tempLength;
		}
		nsteps += tempLength;
	}

	//check if lands correctly
	if (tempRow == er && tempCol == ec)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int main()
{
	setSize(3, 4);
	setWall(1, 4);
	setWall(2, 2);
	setWall(3, 2);
	assert(isRouteWellFormed("n2e1"));
	assert(!isRouteWellFormed("n12xe5"));
	assert(!isRouteWellFormed("1n2e1"));
	assert(!isRouteWellFormed("n1e444"));
	assert(!isRouteWellFormed("n123es2"));

	assert(navigateSegment(1, 1, 'E', 10) == 2);
	assert(navigateSegment(2, 2, 'W', 2) == -1);
	assert(navigateSegment(3, 1, 'N', 2) == 2);
	assert(navigateSegment(1, 1, 'X', 5) == -1);

	int len;
	len = -999;  // so we can detect whether navigateRoute sets len
	assert(navigateRoute(3, 1, 3, 4, "N2eE01n0s2e1", len) == 0 && len == 7);
	len = -999;  // so we can detect whether navigateRoute sets len
	assert(navigateRoute(2, 4, 1, 1, "w3n1", len) == 3 && len == 1);

	//my navigateRoute test cases
	len = -999;
	assert(navigateRoute(2, 1, 2, 4, "Ne1E01n0se1", len) == 0 && len == 5);
	len = -999;
	assert(navigateRoute(2, 1, 2, 4, "Ne1E01n0se0", len) == 1 && len == 4);
	len = -999;
	assert(navigateRoute(2, 1, 3, 4, "NX1E01n0se0", len) == 2 && len == -999);
	len = -999;
	assert(navigateRoute(3, 1, 1, 1, "n03", len) == 3 && len == 2);
	len = -999;
	assert(navigateRoute(1, 1, 3, 4, "S2e3", len) == 3 && len == 2);
	len = -999;
	assert(navigateRoute(3, 4, 1, 1, "Nw1nw02", len) == 0 && len == 5);

	cout << "All tests succeeded" << endl;
}


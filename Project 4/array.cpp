#include <iostream>
#include <cassert>
#include <string>

using namespace std;

int appendToAll(string a[], int n, string value)
{
	//loops thru each element of array, adds value onto end of each value
	for (int i = 0; i < n; i++)
	{
		a[i] += value;
	}
	return n;
}

int lookup(const string a[], int n, string target)
{
	//loops thru each element, checks to see if element is equal to target
	//returns position of element if it equals target, returns -1 if no match is found
	for (int j = 0; j < n; j++)
	{
		if (a[j] == target)
		{
			return j;
		}
	}
	return -1;
}

int positionOfMax(const string a[], int n)
{
	//if array has 0 elements, returns -1
	if (n == 0)
	{
		return -1;
	}

	//notes which string has higher value from left to right
	//if it has higher value, the maxPos gets set with the position of the highest string value so far
	//returns the position of the "biggest" string in the array
	int maxPos = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] >= a[maxPos])
		{
			maxPos = i;
		}
	}
	return maxPos;
}

int rotateLeft(string a[], int n, int pos)
{
	//stores the value of the element at pos into a new variable
	string s = a[pos];

	//sets each element with the value of the next element
	//upper limit is n - 1 so that a[i + 1] doesn't go out of bounds
	for (int i = pos; i < n - 1; i++)
	{
		a[i] = a[i + 1];
	}

	//sets the last element of the array with the value of the element that was at "pos"
	a[n - 1] = s;
	//returns the last parameter of the rotateLeft function
	return pos;
}

int countRuns(const string a[], int n)
{
	//sets count equal to 1, so that even if there only exists one element in a sequence it still counts as "one run"
	int count = 1;

	//loops through each element, checks if it doesn't equal the next one. If doesn't equal, the number of unique elements increases
	for (int i = 0; i < n - 1; i++)
	{
		if (a[i] != a[i + 1])
		{
			count++;
		}
	}
	//returns number of unique elements, because for loop above counts how many times the elements change
	//ie if it counts that the elements change 4 times, we know that there are 5 unique strings. So count is initialized as 1, not 0. 
	return count;
}

int flip(string a[], int n)
{
	//sets j as the position of the last element
	int j = n - 1;

	//loops through each element from opposite sides, with i increasing and j decreasing
	//switches each element of array by swapping values
	//if loops stops once i and j meets, which means all elements have already flipped
	for (int i = 0; i < n; i++)
	{
		if (i <= j)
		{
			//temp1 serves as a temporary variable to swap values if a[i] and a[j]
			string temp1 = a[i];
			a[i] = a[j];
			a[j] = temp1;
			j--;
		}
	}
	//returns last parameter of function
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
	//finds the smaller array list
	int smaller = 0;

	if (n1 <= n2)
	{
		smaller = n1;
	}
	else
	{
		smaller = n2;
	}

	//stops loop at the end of the smaller array
	//checks for the first unequal element. If unequal element is found, returns position of the place of inequality
	for (int i = 0; i < smaller; i++)
	{
		if (a1[i] != a2[i])
		{
			return i;
		}
	}
	//returns the full size of the smaller array if every element up to that point is equal
	return smaller;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	//returns position 0 if size of 2nd array is 0
	if (n2 == 0)
	{
		return 0;
	}

	//tracks position of the beginning of subsequence
	int n2pos = 0;
	int count = 0;
	int n1pos = 0;

	//loops through each element, compares first list until it sees the first element of the second list
	//count == 1 means it is the position of the first time it sees first element of second list in the first list
	//if count successfully reaches the value of n2, then we know a subsequence is found in a1. 
	//if it doesn't find any matches, resets each variable to 0
	for (int i = 0; i < n1; i++)
	{
		if (a1[i] == a2[n2pos])
		{
			n2pos++;
			count++;
			if (count == 1)
			{
				n1pos = i;
			}
			if (count == n2)
			{
				return n1pos;
			}
		}
		else
		{
			count = 0;
			n1pos = 0;
			n2pos = 0;
		}
	}
	//returns -1 if no subsequence is found
	return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
	//checks the first element of a1 with every element of a2, etc.
	//nested for loop is best way to thoroughly check to see if an element in a2 exists in element of a1
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			if (a1[i] == a2[j])
			{
				//returns position of first equal element
				return i;
			}
		}
	}
	//returns -1 if no element is equal between a1 and a2
	return -1;
}

int split(string a[], int n, string splitter)
{
	int start = 0;
	int end = n - 1;
	string temp;

	//exchanges value of elements that don't belong in their half
	//swaps value of elements that are in wrong order
	while (start < end)
	{
		for (; start <= end && a[start] < splitter; start++)
		{
			;
		}
		for (; end >= start && a[end] > splitter; end--)
		{
			;
		}

		//swaps value if start < end still holds after start++ and end-- is processed
		if (start < end)
		{
			temp = a[start];
			a[start] = a[end];
			a[end] = temp;
		}
	}

	//returns the position of the element that is not less than the splitter value
	for (int yy = 0; yy < n; yy++)
	{
		if (a[yy] >= splitter)
		{
			return yy;
		}
	}
	//returns n if no elements are greater than or equal to splitter value
	return n;
}

int main()
{
	//============================================My Test Cases==================================================
	string a[7] = { "Alana", "Jerry", "Ben", "Jonathan", "Zack", "Hillary", "Maggie" };

	assert(appendToAll(a, 7, "!!") == 7 && a[5] == "Hillary!!");
	assert(lookup(a, 7, "Zack!!") == 4);
	assert(lookup(a, 7, "Shirley") == -1);
	assert(positionOfMax(a, 7) == 4);
	assert(rotateLeft(a, 7, 2) == 2 && a[3] == "Zack!!");

	string b[5] = { "Alpha", "Beta", "Beta", "Gamma", "Delta" };
	string c[6] = { "Alpha", "Beta", "Beta", "Delta", "Epsilon", "Zeta" };
	string m[3] = { "Delta", "Epsilon", "Zeta" };
	string n[2] = { "Zeta", "Eta" };

	assert(countRuns(b, 5) == 4);
	assert(differ(b, 5, c, 6) == 3);
	assert(differ(b, 2, c, 3) == 2);
	assert(subsequence(c, 6, m, 3) == 3);
	assert(subsequence(c, 6, n, 2) == -1);
	assert(lookupAny(c, 6, n, 2) == 5);
	assert(lookupAny(b, 5, n, 2) == -1);
	assert(flip(b, 5) == 5 && b[0] == "Delta" && b[3] == "Beta");
	assert(split(a, 7, "Jack") == 3);
	assert(split(a, 7, "Zeck") == 7);

	//============================================Smallberg Tests================================================

	string h[7] = { "bernie", "hillary", "donald", "jeb", "", "carly", "ben" };
	assert(lookup(h, 7, "carly") == 5);
	assert(lookup(h, 7, "donald") == 2);
	assert(lookup(h, 2, "donald") == -1);
	assert(positionOfMax(h, 7) == 3);

	string g[4] = { "bernie", "hillary", "jeb", "carly" };
	assert(differ(h, 4, g, 4) == 2);
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "bernie?" && g[3] == "carly?");
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "jeb?" && g[3] == "hillary?");

	string e[4] = { "donald", "jeb", "", "carly" };
	assert(subsequence(h, 7, e, 4) == 2);

	string d[5] = { "hillary", "hillary", "hillary", "ben", "ben" };
	assert(countRuns(d, 5) == 2);

	string f[3] = { "jeb", "donald", "marco" };
	assert(lookupAny(h, 7, f, 3) == 2);
	assert(flip(f, 3) == 3 && f[0] == "marco" && f[2] == "jeb");
	assert(split(h, 7, "carly") == 3);

	cout << "All tests succeeded" << endl;
}
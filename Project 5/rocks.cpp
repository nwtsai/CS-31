#include "utilities.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <random>
#include <utility>

using namespace std;

const int MAXWORDS = 10000;

// counts the number of letters in a given c string
int countLetters(char c[MAXWORDLEN + 1])
{
	int count = 0;

	for (int i = 0; c[i] != '\0'; i++)
	{
		count++;
	}
	return count;
}

// counts the number of rocks given two c strings
int countRocks(char probe[MAXWORDLEN + 1], char words[MAXWORDLEN + 1])
{
	int count = 0;

	for (int i = 0; words[i] != '\0'; i++)
	{
		if (probe[i] == words[i])
		{
			count++;
		}
	}
	return count;
}

// counts the number of pebbles given two c strings
int countPebbles(char probe[MAXWORDLEN + 1], char words[MAXWORDLEN + 1])
{
	int pebbles = 0;

	// loops through each letter of the secret word 
	for (int i = 0; words[i] != '\0'; i++)
	{
		// variables that count how many times a letters shows up
		int probeCount = 0;
		int secretCount = 0;
		bool hasSameLetters = false;

		// checks if same letter appears twice in the secret word
		for (int j = i - 1; j >= 0; j--)
		{
			if (words[i] == words[j])
			{
				hasSameLetters = true;
			}
		}

		// if no repeated letters, start counting pebbles
		if (hasSameLetters == false)
		{
			// counts number of times the specific letter at i shows up in secret word
			for (int k = 0; words[k] != '\0'; k++)
			{
				if (words[i] == words[k])
				{
					secretCount++;
				}
			}

			// counts number of times the specific letter in the secret word shows up in the probe word
			for (int l = 0; probe[l] != '\0'; l++)
			{
				if (words[i] == probe[l])
				{
					probeCount++;
				}
			}

			// compare counts, adds smaller number to the total pebble count
			if (secretCount < probeCount)
			{
				pebbles += secretCount;
			}
			else
			{
				pebbles += probeCount;
			}
		}
	}

	// number of pebbles equals the smaller count minus number of rocks
	return pebbles - countRocks(probe, words);
}

// checks if the probe word is between 4 and 6 letters and checks if word is in the wordList
// returns true if probe word is syntactically correct, false if otherwise
bool validate(char probe[MAXWORDLEN + 1], const char words[][MAXWORDLEN + 1], int nWords)
{
	// boolean that represents if word is between 4 and 6 lower case letters
	bool isSyntax;
	// booleean that represents if word is found in word list
	bool isValid;

	// if length is between 4 and 6
	if (strlen(probe) >= 4 && strlen(probe) <= 6)
	{
		// if casing is correct
		for (int i = 0; probe[i] != '\0'; i++)
		{
			if (islower(probe[i]))
			{
				isSyntax = true;
			}
			else
			{
				cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
				return false;
			}
		}
	}
	else
	{
		cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
		return false;
	}

	// if the above holds true, then checks if word exists in wordList
	if (isSyntax)
	{
		for (int i = 0; i < nWords; i++)
		{
			// if probe word is found in the wordlist and if it is syntactically correct, return true
			if (strcmp(probe, words[i]) == 0)
			{
				return true;
			}

			// otherwise, since it passed first test, but doesn't pass the word list test, then print out I don't know that word
			else
			{
				isValid = false;
			}
		}
	}

	// checks if the word does not exist in the word list
	if (isValid == false)
	{
		cout << "I don't know that word." << endl;
		return false;
	}

	return true;
}

int manageOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum)
{
	// if number of words in the array is not positive, or if wordnum is less than zero or greater than or equal to nWords, return -1
	if (nWords <= 0 || (wordnum < 0 || wordnum >= nWords))
	{
		return -1;
	}

	int numTries = 1;
	bool isValid;
	char probe[MAXWORDLEN + 1];
	char secret[MAXWORDLEN + 1];
	strcpy_s(secret, words[wordnum]);
	//cout << "Secret word is: " << secret << endl;

	// loops until right word is found
	do {
		//cout << "inside do while loop" << endl;
		cout << "Probe word: ";
		cin.getline(probe, 101);
		isValid = validate(probe, words, nWords);

		// if probe word equals secret word, leave the loop, returns 0 + 1 = 1
		if (strcmp(probe, secret) == 0)
		{
			break;
		}

		// if the probe word is between 4 and 6 lower case letters, and is in the word list, count rocks and pebbles
		// number of tries gets increased by 1 
		if (isValid)
		{
			cout << "Rocks: " << countRocks(probe, secret) << ", Pebbles: " << countPebbles(probe, secret) << endl;
			numTries++;
		}

	// strcmp returns 0 if both c strings are equal, returns anything else if not equal
	} while (strcmp(probe, secret) != 0 || isValid == false);

	return numTries;
}

int main()
{
	char wordList[MAXWORDS][MAXWORDLEN + 1];
	int nWords = loadWords(wordList, MAXWORDS);
	int numRounds = 0;
	int numTries;
	int min;
	int max = 0;
	int roundNumber = 1;
	double totalScore = 0;
	double avg = 0;

	// checks if the word list is empty
	if (nWords < 1)
	{
		cout << "No words were loaded, so I can't play the game." << endl;
		return 0;
	}

	// prompts the user to enter number of rounds, stores input into numRounds
	cout << "How many rounds do you want to play? ";
	cin >> numRounds;
	cin.ignore(10000, '\n');

	// checks for a negative number of rounds, stops program if input is negative 
	if (numRounds <= 0)
	{
		cout << "The number of rounds must be positive." << endl;
		return 0;
	}

	// do while loop that calls manageRound function
	do {
		// everytime it loops, a new random number is chosen
		int randomIndex = randInt(0, nWords - 1);
		cout << endl << "Round " << roundNumber << endl;
		cout << "The secret word is " << countLetters(wordList[randomIndex]) << " letters long." << endl;
		numTries = manageOneRound(wordList, nWords, randomIndex);

		// number of tries gets summed and then divided by round number to find the average
		totalScore += numTries;
		avg = totalScore / (roundNumber);

		// if user gets word in one try, the message prints out the singular version of the completion message
		if (numTries == 1)
		{
			cout << "You got it in " << numTries << " try." << endl;
		}

		// if user takes more than one try, the message prints out the plural version of the completion message
		else
		{
			cout << "You got it in " << numTries << " tries." << endl;
		}

		// if it is the first round, minimum is set to the current score
		if (roundNumber == 1)
		{
			min = numTries;
		}

		// if the current score is less than minimum, the minimum takes the value of the current score
		if (numTries < min)
		{
			min = numTries;
		}

		// if the current score is more than the maximum, the maximum takes the value of the current score
		if (numTries > max)
		{
			max = numTries;
		}

		// makes it so that the average is displayed to two decimal places
		cout.setf(ios::fixed);
		cout.precision(2);
		cout << "Average: " << avg << ", minimum: " << min << ", maximum: " << max << endl;

		// increases the round number after every round
		roundNumber++;

	// stops the loop after round number equals the set number of rounds that the user inputs
	} while (roundNumber <= numRounds);
}
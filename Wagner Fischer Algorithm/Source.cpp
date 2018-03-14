//Christopher Tuncap
//Wagner Fischer Algorithm

#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


struct distanceVector {
	int distance;
	string word;
};

void importFile(vector<string> &rawDictionary);
int editDistance(string s, string t);
bool compareByDistance(const distanceVector &a, const distanceVector &b);

void calculateEditDistance(std::vector<std::string> &rawDictionary, std::string &word, std::vector<distanceVector> &dictionary);

void displayTopTenWords(std::vector<distanceVector> &dictionary);

void promptForWord(std::string &word);

int main()
{

	string word;
	int wDistance = 0;
	vector<distanceVector> dictionary;
	vector<string> rawDictionary;

	importFile(rawDictionary);
	promptForWord(word);
	calculateEditDistance(rawDictionary, word, dictionary);
	displayTopTenWords(dictionary);


	system("pause");
	return 0;

}

void promptForWord(std::string &word)
{
	cout << "Enter a word: ";
	cin >> word;
}

void displayTopTenWords(std::vector<distanceVector> &dictionary)
{
	cout << "Top 10 Best Matches." << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << dictionary[i].distance << " - " << dictionary[i].word << endl;
	}
}

void calculateEditDistance(std::vector<std::string> &rawDictionary, std::string &word, std::vector<distanceVector> &dictionary)
{
	for (size_t i = 0; i < rawDictionary.size(); i++)
	{
		if (i > 12)
		{
			int wDistance = editDistance(word, rawDictionary[i]);
			if (dictionary[11].distance > wDistance)
			{
				dictionary[11].distance = editDistance(word, rawDictionary[i]);
				dictionary[11].word = rawDictionary[i];
				sort(dictionary.begin(), dictionary.end(), compareByDistance);
			}
		}
		else
		{
			dictionary.push_back(distanceVector());
			dictionary[i].distance = editDistance(word, rawDictionary[i]);
			dictionary[i].word = rawDictionary[i];
		}
	}
}

int editDistance(string s, string t)
{

	int m = s.length();
	int n = t.length();

	int** d = new int*[m + 1];
	for (int i = 0; i < m + 1; i++)
	{
		d[i] = new int[n + 1];
	}

	for (int i = 0; i <= m; i++)
	{
		d[i][0] = i;
	}
	for (int j = 0; j <= n; j++)
	{
		d[0][j] = j;
	}

	for (int j = 1; j <= n; j++)
	{
		for (int i = 1; i <= m; i++)
		{
			if (s[i - 1] == t[j - 1])
			{
				d[i][j] = d[i - 1][j - 1];
			}
			else
			{
				int smallestOfTwo = min((d[i - 1][j] + 1), (d[i][j - 1] + 1));
				d[i][j] = min(smallestOfTwo, (d[i - 1][j - 1] + 2));
			}
		}
	}

	return d[m][n];
}


void importFile(vector<string> &rawDictionary)
{
	string word;
	int count = 0;
	ifstream inFile;
	inFile.open("words.txt");

	cout << "Loading wordlist...";
	while (getline(inFile, word))
	{
		rawDictionary.push_back(word);
	}
	cout << " done." << endl;
	inFile.close();
}

bool compareByDistance(const distanceVector &a, const distanceVector &b)
{
	return a.distance < b.distance;
}
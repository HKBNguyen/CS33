#include "provided.h"
#include "MyHash.h"
#include <string>
#include <vector>
#include <fstream>
#include <ctype.h>
using namespace std;


unsigned int hash(const std::string& s)
{
	return std::hash<std::string>()(s);
}
unsigned int hash(const int& i)
{
	return std::hash<int>()(i);
}
unsigned int hash(const char& c)
{
	return std::hash<char>()(c);
}
class WordListImpl
{
public:
	bool loadWordList(string filename);
	bool contains(string word) const;
	vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
	MyHash<string, string> dictionary; // all the words stored in a hash table for fast access
	MyHash<string, vector<string>> wordsPattern;
	string pattern(string s) const;
};

bool WordListImpl::loadWordList(string filename)
{
	wordsPattern.reset();
	dictionary.reset();
	ifstream infile;
	infile.open(filename);
	if (!infile)
	{
		return false;
	}
	std::string s;
	vector<string> vec;
	int count = 0;
	while (getline(infile, s))
	{
		for (int i = 0; i < s.size(); i++)
		{
			s[i] = tolower(s[i]);
		}
		dictionary.associate(s, s);
		string t = pattern(s);
		vector<string>* st = wordsPattern.find(t);
		if (st != nullptr)
			st->push_back(s);
		else
		{
			vec.push_back(s);
			wordsPattern.associate(t, vec);
			vec.clear();
		}
	}
	return true;  
}

bool WordListImpl::contains(string word) const
{
	string w = pattern(word);
	const vector<string>* s = wordsPattern.find(w); // find pointer to vector of possible strings with same pattern
	if (s == nullptr)
		return false;
	const vector<string> t = *s;
	for (int i = 0; i < word.size(); i++) // change word to all lowercase
	{
		word[i] = tolower(word[i]);
	}
	const string * found = dictionary.find(word);
	if (found != nullptr && *found == word)
		return true;
	else
		return false;
	
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
	if (cipherWord.size() != currTranslation.size())
		return vector<string>();
	for (int i = 0; i < cipherWord.size(); i++)
	{
		if (!isalpha(cipherWord[i]) && cipherWord[i] != '\'')
			return vector<string>();
		if (!isalpha(currTranslation[i]) && currTranslation[i] != '\'' && currTranslation[i] != '?')
			return vector<string>();
	}
	string w = pattern(cipherWord);
	const vector<string>* s = wordsPattern.find(w); // find pointer to vector of possible strings with same pattern
	if (s == nullptr)
		return vector<string>();
	const vector<string> t = *s;
	vector<string> candidates;
	vector<string>::const_iterator it;
	it = t.begin(); 
	while (it != t.end()) //search through the same pattern vector	
	{
		bool found = true; // check to remove wordsPattern that differentiate from currTranslation
		string temp = *it;
		for (int j = 0; j < temp.size(); j++) // change each possible word to lowercase since spec says contains must be case insensitive 
		{
			temp[j] = tolower(temp[j]);
		}
		for (int i = 0; i < cipherWord.size(); i++) // change word to all lowercase for case insensitive requirement
		{
			if (isalpha(currTranslation[i]))
			{
				currTranslation[i] = tolower(currTranslation[i]);
				if (currTranslation[i] != temp[i])
				{
					found = false;
					break;
				}
			}
			if (currTranslation[i] == '?' && (!isalpha(temp[i]) || !isalpha(cipherWord[i])))
			{
				found = false;
				break;
			}
			if (currTranslation[i] == '\'' && (temp[i] != '\'' || cipherWord[i] != '\''))
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			candidates.push_back(*it);
			it++;
		}
		else
		it++;
	}
	return candidates; 
}

string WordListImpl::pattern(string s) const
{
	int count = 0; // element/index number
	for (int i = 0; i < s.size(); i++)
	{
		for (int t = i + 1; t < s.size(); t++)
		{
			s[i] = tolower(s[i]);
			s[t] = tolower(s[t]);
			if (s[i] == s[t]) 
				s[t] = '0' + count; // if any two letters are the same change the furtherest letter to a number
		}
		if (isalpha(s[i])) // check to prevent duplicate runs 
		{
			s[i] = '0' + count;
			count++; // increase count for next combination/letter
		}
	}
	return s;
}


//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
	m_impl = new WordListImpl;
}

WordList::~WordList()
{
	delete m_impl;
}

bool WordList::loadWordList(string filename)
{
	return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
	return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
	return m_impl->findCandidates(cipherWord, currTranslation);
}

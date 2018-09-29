#include "provided.h"
#include <string>
#include "MyHash.h"
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

class TranslatorImpl
{
public:
	TranslatorImpl();
	bool pushMapping(string ciphertext, string plaintext);
	bool popMapping();
	string getTranslation(const string& ciphertext) const;
private:
	vector<vector<char>> translations; // vector that holds tables of each letter's mappings in the context of another vector
int push = 0;
int pop = 0;
};

TranslatorImpl::TranslatorImpl()
{
	vector<char> currMap; // initially an empty mapping
	for (int i = 0; i < 26; i++)
	{
		currMap.push_back('?'); // 26 elements of this vector map must initially be all ?
	}
	translations.push_back(currMap); // after the loop is done, push the empty map into the translations vector
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
	if (ciphertext.size() != plaintext.size()) 
		return false;
	vector<char> copy; //good translations, so hold a separate map
	unordered_set<char> valuesToKey; //flip key to value map in order to check for inconsistences of multiple values
	for (int i = 0; i < 26; i++) //valuesToKey
	{
		copy.push_back(translations.back()[i]);
		if (translations.back()[i] != '?')
		{
			valuesToKey.insert(tolower(translations.back()[i]));
			valuesToKey.insert(toupper(translations.back()[i]));
		}
	}
	for (int i = 0; i < ciphertext.size(); i++)
	{
		int index;
		if (islower(ciphertext[i]))
		{
			char temp = toupper(ciphertext[i]);
			index = temp - 'A';	
			tolower(ciphertext[i]);
		}
		else 
		index = ciphertext[i] - 'A';
		if (translations.back()[index] == plaintext[i])
			continue;
		if (translations.back()[index] != '?')
			return false;
		if (valuesToKey.find(plaintext[i]) != valuesToKey.end())
			return false;
		copy[index] = plaintext[i];
	}
	translations.push_back(copy); // push the newly updated map to the beginning of vector
	push++; //keep a counter to make sure not to pop more than pushed (probably leads to runtime errors)
	return true;
}

bool TranslatorImpl::popMapping()
{
	if (pop == push) // can't pop more than pushed
	return false;  
	translations.pop_back();
	pop++;
	return true;
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
	string s;
	for (int i = 0; i < ciphertext.size(); i++)
	{
		int index;
		if (islower(ciphertext[i]))
		{
			char temp = toupper(ciphertext[i]);
			index = temp - 'A';
			tolower(ciphertext[i]);
		}
		else
			index = ciphertext[i] - 'A';
		if (!isalpha(ciphertext[i]))
			s += ciphertext[i];
		else if (translations.back()[index] == '?')
			s += '?';
		else
		{
			if (isupper(ciphertext[i]))
				s += (toupper(translations.back()[index]));
			else 
				s += (tolower(translations.back()[index]));
		}
	}
	return s;
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
	m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
	delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
	return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
	return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
	return m_impl->getTranslation(ciphertext);
}

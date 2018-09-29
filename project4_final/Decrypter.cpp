#include "provided.h"
#include <string>
#include <vector>
#include <ctype.h>
#include <algorithm>
using namespace std;

class DecrypterImpl
{
public:
	bool load(string filename);
	vector<string> crack(const string& ciphertext);
private:
	Translator m_translator; //step 1 since nothing has been added, initially empty mapping
	WordList m_wl;
	Tokenizer* m_tokenizer;
	string translateAgain(vector<string>& possibleTranslations, const string& ciphertext);
};

bool DecrypterImpl::load(string filename)
{
	if (!m_wl.loadWordList(filename))
		return false;
	else
		return true;
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
	vector<string> possibleTranslations;
	string separators;
	for (int i = 0; i < ciphertext.size(); i++) // search for specific separators
	{
		if (isdigit(ciphertext[i]) ||
			isspace(ciphertext[i]) ||
			ciphertext[i] == ',' ||
			ciphertext[i] == ';' ||
			ciphertext[i] == ':' ||
			ciphertext[i] == '.' ||
			ciphertext[i] == '!' ||
			ciphertext[i] == '(' ||
			ciphertext[i] == ')' ||
			ciphertext[i] == '[' ||
			ciphertext[i] == ']' ||
			ciphertext[i] == '{' ||
			ciphertext[i] == '}' ||
			ciphertext[i] == '-' ||
			ciphertext[i] == '"' ||
			ciphertext[i] == '#' ||
			ciphertext[i] == '$' ||
			ciphertext[i] == '%' ||
			ciphertext[i] == '^' ||
			ciphertext[i] == '&'
			)
		{
			separators += ciphertext[i]; //string of separators
		}
			
	}
		m_tokenizer = new Tokenizer(separators);
	translateAgain(possibleTranslations, ciphertext);
	return possibleTranslations;
}

string DecrypterImpl::translateAgain(vector<string>& possibleTranslations, const string & ciphertext)
{
	string s = m_translator.getTranslation(ciphertext);
	vector<string> afterTokenizedCipher = m_tokenizer->tokenize(ciphertext); // send back a vector of the ciphertext without separators
	vector<string> afterTokenized = m_tokenizer->tokenize(s); // send back a vector of the ciphertext without separators
	string toDecrypt; //string that can change repeatedly according to # of ?s
	int maxUntranslated = 0; //counter to see which word to decrypt next
	for (int i = 0; i < afterTokenized.size(); i++)
	{
		int count = 0;
		for (int j = 0; j<afterTokenized[i].size(); j++)
		{
			if (afterTokenized[i][j] == '?')
				count++;
			if (count > maxUntranslated)
			{
				maxUntranslated = count;
				toDecrypt = afterTokenizedCipher[i];
			}
		}
	}
	string intialDecrypted = m_translator.getTranslation(toDecrypt); //step 3, this is equivalent to currTranslation
																	 //step 4
	vector<string> possibleCandidates = m_wl.findCandidates(toDecrypt, intialDecrypted); //finding vector of words that match pattern and adhere to currTranslation
																						 //step 5
	if (possibleCandidates.empty()) //if there are no candidates just move to the next possible string
	{
		return "";
	}
	sort(possibleCandidates.begin(), possibleCandidates.end());
	vector<string>::iterator itP; //otherwise loop through all candidates, also named plaintext
								  //step 6a
	itP = possibleCandidates.begin();
	while (itP != possibleCandidates.end()) //for each candidate try and push a new mapping onto the current mapping
	{
		if (!m_translator.pushMapping(toDecrypt, *itP))
			itP++;
		else
		{
			string afterDecrypted = m_translator.getTranslation(ciphertext);
			vector<string> againTokenized = m_tokenizer->tokenize(afterDecrypted);
			vector<string>::iterator itTA;
			itTA = againTokenized.begin();
			bool incorrectMap = false;
			int total = 0;
			//still step 6c, top level; this makes sure fully translated words are in wordlist and no completely untranslated words
			while (itTA != againTokenized.end())
			{
				
				int count = 0;
				for (int i = 0; i < (*itTA).size(); i++)
				{
					if ((*itTA)[i] == '?')
					{
						count++;
					}
				}
				/*if (count == (*itTA).size())
				{
					m_translator.popMapping();
					itP++;
					incorrectMap = true;
					break;
				}*/
				if (count == 0)
				{
					if (!m_wl.contains((*itTA)))
					{
						m_translator.popMapping();
						itP++;
						incorrectMap = true;
						break;
					}
					total++;
				}
				itTA++;
			}
			if (incorrectMap)
				continue;
			if (total < 1)
			{
				m_translator.popMapping();
				itP++;
				continue;
			}
			if (total == againTokenized.size())
			{
				possibleTranslations.push_back(afterDecrypted);
				m_translator.popMapping();
				itP++;
				continue;
			}
			//crack ciphertext again. if returns empty vector then pop current mapping
			if (translateAgain(possibleTranslations, ciphertext) != "")
			{
				//m_translator.popMapping();
				itP++;
				continue;
			}
		}
	}
	m_translator.popMapping();
	return "a";
}




//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
	m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
	delete m_impl;
}

bool Decrypter::load(string filename)
{
	return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
	return m_impl->crack(ciphertext);
}

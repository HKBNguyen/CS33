#include "provided.h"
#include <string>
#include <vector>
#include <ctype.h>
using namespace std;

class TokenizerImpl
{
public:
	TokenizerImpl(string separators);
	~TokenizerImpl();
	vector<string> tokenize(const std::string& s) const;
private:
	char* op;
	int op_size;
};

TokenizerImpl::TokenizerImpl(string separators)
{
	op = new char[separators.size()];
	op_size = separators.size();
	for (int i = 0; i < op_size; ++i)
	{
		op[i] = separators[i];
	}
}

TokenizerImpl::~TokenizerImpl()
{
	delete[] op;
}

vector<string> TokenizerImpl::tokenize(const std::string& s) const
{
	vector<string> v;
	string temp;
	// boolean to see if something can be added to the string to be pushed
	for (int i = 0; i < s.size(); ++i)
	{
		bool correct = true;
		for (int j = 0; j < op_size; ++j)
		{
			if (s[i] == op[j])
			{
				if (!temp.empty())
					v.push_back(temp);
				temp = "";
				correct = false;
				break;
			}
		}
		if (correct) //error checking
		{
			temp += s[i];
			if (i == s.size() - 1)
				v.push_back(temp);
		}
	}
	return v;  
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
	m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
	delete m_impl;
}

vector<string> Tokenizer::tokenize(const std::string& s) const
{
	return m_impl->tokenize(s);
}

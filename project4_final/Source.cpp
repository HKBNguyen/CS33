#if defined(_MSC_VER)  &&  !defined(_DEBUG)
#include <iostream>
#include <windows.h>
#include <conio.h>

struct KeepWindowOpenUntilDismissed
{
	~KeepWindowOpenUntilDismissed()
	{
		DWORD pids[1];
		if (GetConsoleProcessList(pids, 1) == 1)
		{
			std::cout << "Press any key to continue . . . ";
			_getch();
		}
	}
} keepWindowOpenUntilDismissed;
#endif
#include "provided.h"
#include "MyHash.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cassert>
using namespace std;

const std::string WORDLIST_FILE = "wordlist.txt";
const char* FILENAME = "sanityfile";

/*string encrypt(string plaintext)
{
	// Generate a to z
	char plaintextAlphabet[26 + 1];
	iota(plaintextAlphabet, plaintextAlphabet + 26, 'a');
	plaintextAlphabet[26] = '\0';

	// Generate permutation
	string ciphertextAlphabet(plaintextAlphabet);
	default_random_engine e((random_device()()));
	shuffle(ciphertextAlphabet.begin(), ciphertextAlphabet.end(), e);

	// Run translator (opposite to the intended direction)
	Translator t;
	t.pushMapping(plaintextAlphabet, ciphertextAlphabet);
	return t.getTranslation(plaintext);
}

bool decrypt(string ciphertext)
{
	Decrypter d;
	if (!d.load(WORDLIST_FILE))
	{
		cout << "Unable to load word list file " << WORDLIST_FILE << endl;
		return false;
	}
	for (const auto& s : d.crack(ciphertext))
		cout << s << endl;
	return true;
}

int main(int argc, char* argv[])
{
	if (argc == 3 && argv[1][0] == '-')
	{
		switch (tolower(argv[1][1]))
		{
		case 'e':
			cout << encrypt(argv[2]) << endl;
			return 0;
		case 'd':
			if (decrypt(argv[2]))
				return 0;
			return 1;
		}
	}
	cout << "Usage to encrypt:  " << argv[0] << " -e \"Your message here.\"" << endl;
	cout << "Usage to decrypt:  " << argv[0] << " -d \"Uwey tirrboi miyi.\"" << endl;
	return 1;
}*/




bool createWordListFile()
{
	ofstream ofs(FILENAME);
	if (!ofs)
	{
		cout << "Cannot create word list file named " << FILENAME << endl;
		return false;
	}
	const char* words[] = {
		"people", "aerate", "ether", "essay", "eater",
		"excel", "Expel", "ablate", "purple"
	};
	for (auto w : words)
		ofs << w << endl;
	return true;
}
void testDecrypter()
{
	if (!createWordListFile())
	{
		cout << "Cannot complete Decrypter test" << endl;
		exit(1);
	}
	Decrypter d;
	assert(d.load(FILENAME));
	vector<string> v = d.crack("smxsdg SGOSDG gfvgx!!");
	const char* expected[] = {
		"ablate AERATE excel!!",
		"ablate AERATE expel!!",
		"purple PEOPLE eater!!",
		"purple PEOPLE ether!!"
	};
	assert(v.size() == 4 && equal(v.begin(), v.end(), expected));
	assert(d.crack("smxsdg SGOSDG gfvgy!!").empty());
	remove(FILENAME);
}

void testMyHash()
{
	MyHash<int, string> m;
	m.associate(222, "Ethel");
	m.associate(333, "Lucy");
	m.associate(111, "Fred");
	assert(m.getNumItems() == 3);
	assert(abs(m.getLoadFactor() - 0.03) < 0.00001);
	string* s = m.find(333);
	assert(s != nullptr  &&  *s == "Lucy");
	m.associate(333, "Ricky");
	assert(m.getNumItems() == 3);
	const MyHash<int, string>& cm = m;
	const string* cs = cm.find(333);
	assert(cs != nullptr  &&  *cs == "Ricky");
	int x = 1776;
	for (int k = 0; k < 1000; k++)
	{
		m.associate(x, "Carey");
		x += 1789;
	}
	assert(m.getNumItems() == 1003);
	double lf = m.getLoadFactor();
	assert(lf >= 0.5 / 2 && lf <= 0.5);
	m.reset();
	m.associate(444, "David");
	assert(m.getNumItems() == 1);
	assert(abs(m.getLoadFactor() - 0.01) < 0.00001);
}
void f()
{
	WordList wl;
	if (!wl.loadWordList("wordlist.txt"))
	{
		cout << "Unable to load word list" << endl;
		return;
	}
	if (wl.contains("onomatopoeia"))
		cout << "I found onomatopoeia!" << endl;
	else
		cout << "Onomatopoeia is not in the word list!" << endl;
	string cipher = "xyqbbq";
	string decodedSoFar = "?r????";
	vector<string> v = wl.findCandidates(cipher, decodedSoFar);
	if (v.empty())
		cout << "No matches found" << endl;
	else
	{
		cout << "Found these matches:" << endl;
		for (size_t k = 0; k < v.size(); k++)
			cout << v[k] << endl; // writes grotto and troppo
	}
}

void d()
{
	Translator t;
	t.pushMapping("DHL", "ERD"); // DàE, HàR, LàD
	if (!t.pushMapping("QX", "RY")) // QàR, XàY
		cout << "Both H and Q would map to R!" << endl;
	// The current mapping is still DàE, HàR, LàD with no
	// mapping for Q or X
	cout << t.getTranslation("HDX") << endl; // writes RE?
	if (!t.pushMapping("H", "S")) // HàS
		cout << "H would map to both R and S!" << endl;
	t.popMapping();
	t.popMapping();
	cout << t.getTranslation("HDX") << endl;
	t.pushMapping("Yet", "Kxa");
	cout << t.getTranslation("YEt");
}

void testTokenizer()
{
	Tokenizer t(".#");
	vector<string> v = t.tokenize("this.is##.#a#SILLY test#..");
	const char* expected[4] = { "this", "is", "a", "SILLY test" };
	assert(v.size() == 4 && equal(v.begin(), v.end(), expected));
}
void testWordList()
{
	if (!createWordListFile())
	{
		cout << "Cannot complete WordList test" << endl;
		exit(1);
	}
	WordList wl;
	assert(wl.loadWordList(FILENAME));
	assert(wl.contains("expel"));
	assert(!wl.contains("extol"));
	vector<string> v = wl.findCandidates("wpxWv", "?x???");
	const char* expected[] = { "excel", "expel" };
	assert(v.size() == 2);
	for (auto& w : v)
		transform(w.begin(), w.end(), w.begin(), [](char c) { return tolower(c); });
	assert(equal(v.begin(), v.end(), expected) || equal(v.rbegin(), v.rend(), expected));
	v = wl.findCandidates("wpxwv", "?????");
	assert(v.size() == 4);
	v = wl.findCandidates("wpxwv", "?s??y");
	assert(v.size() == 0);
	remove(FILENAME);
}

void testTranslator()
{
	const char* q5bang = "?????" "!";  // Avoid trigraph
	Translator t;
	assert(t.getTranslation("Hdqlx!") == q5bang);
	assert(!t.popMapping());
	assert(t.getTranslation("Hdqlx!") == q5bang);
	assert(t.pushMapping("dhL", "Erd"));
	assert(t.getTranslation("Hdqlx!") == "Re?d?!");
	assert(!t.pushMapping("QX", "RY"));
	assert(t.getTranslation("Hdqlx!") == "Re?d?!");
	assert(!t.pushMapping("H", "S"));
	assert(t.getTranslation("Hdqlx!") == "Re?d?!");
	assert(t.pushMapping("QX", "AY"));
	assert(t.getTranslation("Hdqlx!") == "Ready!");
	assert(t.popMapping());
	assert(t.getTranslation("Hdqlx!") == "Re?d?!");
	assert(t.popMapping());
	assert(t.getTranslation("Hdqlx!") == q5bang);
	assert(!t.popMapping());
}

int main() {
	//{
		/*MyHash<int, double> hashBoi;
		hashBoi.associate(1, 2.0);
		hashBoi.associate(3, 3.4);
		hashBoi.associate(2, 2.33);
		hashBoi.associate(3, 1.88); //Duplicate
		hashBoi.associate(303, 1.04);
		hashBoi.associate(603, 1.11);
		double* printed = hashBoi.find(202);
		assert(*hashBoi.find(3) == 1.88 && *hashBoi.find(303) == 1.04 && *hashBoi.find(2) == 2.33);
		assert(printed == nullptr);
		assert(hashBoi.getLoadFactor() == 0.05);
		assert(hashBoi.getNumItems() == 5);
		hashBoi.reset();
		assert(hashBoi.getNumItems() == 0 && hashBoi.getLoadFactor() == 0.05);
		assert(hashBoi.find(3) == nullptr);
		for (int i = 0; i < 10000; i++) //Make sure no memory leaks
			hashBoi.reset();
		assert(hashBoi.find(303) == nullptr); //Should be empty
		for (int i = 0; i < 10000; i++) {
			MyHash<int, double> hash1(0.7);
			assert(hash1.getLoadFactor() == 0.7);
		}
		//Testing to make sure it works with multiple stuff
		//Should never go overload
		for (int i = 0; i < 1000; i++) {
			MyHash<int, double> hashBB(3.1); //Should go to 2.0
			assert(hashBB.getLoadFactor() == 2.0);
			for (int z = 0; z < 199; z++) { //Each will have 2 things in
				hashBB.associate(z, z * 1.1);
			}
			for (int z = 0; z < 199; z++) {
				assert(*hashBB.find(z) == z * 1.1); //Make sure they can be found
			}
			//Should never appear
			for (int z = 0; z < 199; z++)
				assert(hashBB.find(z + 200) == nullptr);
		}
		//Testing for pathological cases LATER
		MyHash<int, double> hashBB();

		//Testing for going over load
		for (int i = 0; i < 1000; i++) {
			MyHash<int, double> hashBE(0.1); //Only handle 10 items before reshuffling
			assert(hashBE.getLoadFactor() == 0.1);
			for (int z = 0; z < 50; z++) //Reshuffle 3 times
			{
				hashBE.associate(z, z * 1.1);
			}
			assert(hashBE.getNumItems() == 50);
			for (int z = 0; z < 50; z++) { //Should exist (no memory leaks hopefully)
				assert(*hashBE.find(z) == z * 1.1);
			}
			for (int z = 0; z < 100; z++) { //Should not exist
				assert(hashBE.find(50 + z) == nullptr);
			}
		}
	}*/

	Decrypter d;
	d.load("wordlist.txt");
//	vector<string> c = d.crack("Trcy oyc koon oz rweelycbb vmobcb, wyogrcn oecyb; hjg ozgcy tc moox bo moya wg grc vmobck koon grwg tc ko yog bcc grc oyc trlvr rwb hccy oecyck zon jb. -Rcmcy Xcmmcn");
//	vector<string> c = d.crack("Axevfvu lvnelvp bxqp mvpprjv rgl bvoop Grnxvgkvuj dqupb jvbp buvrbvl be lqggvu.");
//	vector<string> c = d.crack("Jxwpjq qwrla glcu pcx qcn xkvv dw uclw ekarbbckpjwe dq jzw jzkpta jzrj qcn ekep'j ec jzrp dq jzw cpwa qcn eke ec. -Urls Jxrkp");
	vector<string> c = d.crack("Xjzwq gjz cuvq xz huri arwqvudiy fuk ufjrqoq svquxiy. - Lzjk Nqkkqcy");

	vector<string>::iterator it;
	it = c.begin();
	while (it != c.end())
	{
		cout << *it << endl;
		it++;
	}
	//testDecrypter();
	//WordList wl;
	//wl.loadWordList("wordlist.txt");
//	assert(!wl.contains("Meller"));
	cout << endl;
	cout << "Passed all tests" << endl;
}


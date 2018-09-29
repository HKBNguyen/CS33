#ifndef MYHASH_INCLUDED
#define MYHASH_INCLUDED
#include <string>
#include <functional>
#include <algorithm>
template <typename KeyType, typename ValueType>
class MyHash
{
public:
	MyHash(double maxLoadFactor = 0.5);
	~MyHash();
	void reset();
	void associate(const KeyType& key, const ValueType& value);
	// for a map that can't be modified, return a pointer to const ValueType
	 ValueType* find(const KeyType& key) const;

	// for a modifiable map, return a pointer to modifiable ValueType
	ValueType* find(const KeyType& key)
	{
		return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key)); // C++ magic
	}
	int getNumItems() const;
	double getLoadFactor() const;
	MyHash(const MyHash&) = delete;
	MyHash& operator=(const MyHash&) = delete;
private:
	struct Node
	{
		Node(const KeyType& k, const ValueType& v) :m_key(k), m_value(v), next(nullptr){} 
		KeyType m_key;
		ValueType m_value;
		Node * next;
	};
	Node** table;
	double curr_associations = 0;
	double curr_Nodes;
	double m_maxLoadFactor;
	int max_Nodes = 100;
	unsigned int getNodeNum(const KeyType& key, int maxBuckets) const;
};

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor)
{
	if (maxLoadFactor <= 0)
		maxLoadFactor = .5;
	if (maxLoadFactor > 2)
		maxLoadFactor = 2.0;
	m_maxLoadFactor = maxLoadFactor;
	curr_Nodes = maxLoadFactor * max_Nodes;
	table = new Node*[max_Nodes]; //default is 100 nodes or slots in the hash table
	for (int i = 0; i < max_Nodes; ++i)
	{
		table[i] = nullptr; //must set each to nullptr for defensive programming
	}
}

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::~MyHash()
{
	for (int i = 0; i < max_Nodes; i++)
	{
		if (table[i] == nullptr)
			continue;
		Node* head = table[i];
		while (head->next != nullptr)
		{
			Node* temp = head->next;
			delete head;
			head = temp;
		}
		delete head;
	}
	delete[] table;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::reset()
{
	for (int i = 0; i < max_Nodes; i++)
	{
		
		if (table[i] == nullptr)
			continue;
			Node* head = table[i];
			while (head->next != nullptr)
			{
				Node* temp = head->next;
				delete head;
				head = temp;
			}
			delete head;
	}
	delete[] table;
	curr_associations = 0;
	max_Nodes = 100;
	table = new Node*[100];
	for (int i = 0; i < 100; i++)
	{
		table[i] = nullptr;
	}
}

/*void MyHash<KeyType, ValueType>::associate(const KeyType & key, const ValueType & value)
{
	ValueType * v = find(key);
	if (v == nullptr) // if that key/value pair is not currently in the hash table
	{
		if ((getLoadFactor() + (curr_associations + 1))/(max_Nodes) >= m_maxLoadFactor) // checks whether or not adding this association would cause the need to recreate and double the size of the hash table
		{
			//reset();
			//for (int i = max_Nodes; i < max_Nodes * 2; i++)
				//table[i] = new Node;
			max_Nodes *= 2; // intialize table twice the size
			Node ** tempTable = new Node*[max_Nodes]; //now double the size
			for (int i = 0; i < max_Nodes; i++)
			{
				tempTable[i] = nullptr;
			}
			for (int i = 0; i < max_Nodes/2; i++) // must loop through the intial table that is 1/2 the size of new table
			{
				KeyType k = table[i]->m_key;  // copy the key, value pair
				ValueType v = table[i]->m_value;
				int index = getNodeNum(table[i]->m_key, max_Nodes); // get the new index
				tempTable[index]->m_key = k;
				tempTable[index]->m_value = v;
			}
			max_Nodes /= 2; // turn back to original number of nodes to delete them
			reset(); // delete them and then reintialize the orignal amount
			for (int i = max_Nodes; i < max_Nodes * 2; i++) // intialize the other newly created half
				tempTable[i] = nullptr;
			max_Nodes *= 2; // set to the correct amount of Nodes
			table = tempTable; // table now points to the tempTable
		}
		unsigned int index = getNodeNum(key, max_Nodes);
		Node * p = table[index];
		if(p == nullptr)
		table[index] = new Node(key, value, nullptr);
		else
		{
			while (p->next != nullptr)
				p = p->next;
			p->next = new Node(key, value);
		}
		curr_associations++;
	}
	else
	{
		*v = value;// if it doesn't overfill simply and that key already exists then replace that value
	}
}*/
template<typename KeyType, typename ValueType>
void MyHash<KeyType,ValueType>::associate(const KeyType& key, const ValueType& value)
{
	ValueType * v = find(key);

	if (v == nullptr) // the key is not present in the hash map
	{
		if ((curr_associations + 1) / (max_Nodes) >= m_maxLoadFactor) // checks whether or not adding this association would cause the need to recreate and double the size of the hash table
		{
			Node** tempTable = new Node*[2*max_Nodes];
			for (int i = 0; i < 2 * max_Nodes; i++)
			{
				tempTable[i] = nullptr;
			}
			for (int i = 0; i < max_Nodes; i++)
			{
				if (table[i] == nullptr)
					continue;
				unsigned int index = getNodeNum(table[i]->m_key, 2 * max_Nodes);
				tempTable[index] = new Node(table[i]->m_key, table[i]->m_value);
				if (table[i]->next != nullptr)
				{
					Node *p = table[i];
					Node *j = tempTable[index];
					while (p->next != nullptr)
					{
						j->next = new Node(table[i]->next->m_key, table[i]->next->m_value);
						j = j->next;
						p = p->next;
					}
				}
			}
			double temp_associations = curr_associations; //temporary associations and maxNodes need to be made because reset resets them
			int temp_maxNodes = max_Nodes;
			reset();
			curr_associations = temp_associations;
			max_Nodes = temp_maxNodes;
			for (int i = 0; i < 100; i++)
			{
				if (table[i] == nullptr)
					continue;
				Node*head = table[i];
				while (head->next != nullptr)
				{
					Node* temp = head->next;
					delete head;
					head = temp;
				}
				delete head;
			}
			delete[] table;
			table = tempTable;
			max_Nodes = max_Nodes * 2;
		}
			unsigned int index = getNodeNum(key, max_Nodes);
			Node * p = table[index];
			if (p == nullptr)
				table[index] = new Node(key, value);
			else
			{
				while (p->next != nullptr)
					p = p->next;
				p->next = new Node(key, value);
			}
			curr_associations++;
	}
	else
	{
		*v = value;
	}

	}


template<typename KeyType, typename ValueType>
ValueType * MyHash<KeyType, ValueType>::find(const KeyType & key) const
{
	unsigned int index = getNodeNum(key, max_Nodes);
	if (table[index] == nullptr) // if that index has no linked list then it must have no value
		return nullptr;
	Node * p = table[index];
	while (p != nullptr) // check if that index has a linked list and search through for the key
	{
		if (p->m_key == key) // if the key is found then return a pointer to the value
			return &p->m_value;
		p = p->next;
	}
	return nullptr; // no key exists
}

template<typename KeyType, typename ValueType>
int MyHash<KeyType, ValueType>::getNumItems() const
{
	return curr_associations;
}

template<typename KeyType, typename ValueType>
double MyHash<KeyType, ValueType>::getLoadFactor() const
{
	return (curr_associations / max_Nodes);
}
template<typename KeyType, typename ValueType>
 unsigned int MyHash<KeyType, ValueType>::getNodeNum(const KeyType & key, int maxBuckets) const
{
	unsigned int hash(const KeyType& k); //prototype for all the various hash functions
	unsigned int index = hash(key); //hash produces a random number between 0 and 4 billion
	return index % maxBuckets;
}

#endif // MYHASH_INCLUDED

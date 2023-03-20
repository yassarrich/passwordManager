//Name:Yassar Rich
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

using namespace std;
//Public Functions
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size)
{	hashVector.resize(prime_below(size));
	currentSize = 0;
}

template <typename K, typename V>
HashTable<K, V>::~HashTable()
{clear();}

template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k) const
{
	for (auto i = hashVector[myhash(k)].begin(); i != hashVector[myhash(k)].end(); ++i)
	{
		if (i->first == k)
		{
			return true;
		}
	}
	return false;
}

template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K,V> & kv) const
{
	auto & matchList = hashVector[myhash(kv.first)];
	return (std::find(matchList.begin(), matchList.end(), kv) != matchList.end());
}

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K,V> & kv)
{
	if (contains(kv.first))
	{
		auto & insertList = hashVector[myhash(kv.first)];
		for (auto i = insertList.begin(); i != insertList.end(); ++i)
		{
			if (i->first == kv.first)
			{
				auto remove = insertList.erase(i);
				insertList.insert(remove, kv);
				return true;
			}
		}
	}
	//Making sure the user isn't already in the list
	else if (match(kv))
	{
		return false;
	}

	else
	{
		hashVector[myhash(kv.first)].push_back(kv);
		if (++currentSize > hashVector.size())
		{
			rehash();
		}
		return true;
	}
	return false;
}

template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K,V> && kv)
{
	const std::pair<K,V> newPair = std::move(kv);
	return insert(newPair);
}

template <typename K, typename V>
bool HashTable<K, V>::remove(const K & k)
{
	auto & removeList = hashVector[myhash(k)];
	bool remove = false;
	for (auto i = removeList.begin(); i != removeList.end(); ++i)
	{
		if (i->first == k)
		{
			i = removeList.erase(i);
			--currentSize;
			remove = true;
		}
	}
	return remove;
}

template <typename K, typename V>
void HashTable<K, V>::clear()
{makeEmpty();}

template <typename K, typename V>
bool HashTable<K, V>::load(const char * filename)
{	
	char space;
	pair<K,V> enteredPair;
	ifstream input;

	input.open(filename, std::ifstream::in);

	if (!input)
		return false;

	while (input)
	{
		std::getline(input, enteredPair.first, ' ');

		while (isspace(input.peek()))
			input.get(space);

		std::getline(input, enteredPair.second, '\n');

		while (isspace(input.peek()))
			input.get(space);

		insert(enteredPair);
	}
}

template <typename K, typename V>
void HashTable<K, V>::dump() const
{
	cout << "\n";
	for (int i = 1; i < hashVector.size(); i++)
	{
		cout << "v[" << i << "]:";
		if (!hashVector[i].empty())
		{
			for (auto j = hashVector[i].begin(); j != hashVector[i].end(); ++j)
			{
				if (j != hashVector[i].begin())
					cout << ':';
				cout << j->first << " " << j->second;
			}
		}
		cout << "\n";
	}
}

template <typename K, typename V>
size_t HashTable<K, V>::size() const
{return currentSize;}

template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char * filename) const
{
	ofstream output;
	output.open(filename);

	if(!output)
		return false;

	for (int i = 0; i < hashVector.size(); i++)
	{
		for (auto iterator = hashVector[i].begin(); iterator != hashVector[i].end(); ++iterator)
			output << iterator->first << ' ' << iterator->second << '\n';
	}

	output.close();
	return true;
}

//Private Functions

template <typename K, typename V>
void HashTable<K, V>::makeEmpty()
{
	for (auto & emptyList: hashVector)
		emptyList.clear();
}

template <typename K, typename V>
void HashTable<K, V>::rehash()
{
	vector<list<pair<K,V>>> oldList = hashVector;
	hashVector.resize(prime_below(2 * hashVector.size()));

	for (auto & emptyList: hashVector)
		emptyList.clear();
	
	currentSize = 0;

	for (auto & insertList: oldList)
		for (auto & kv: insertList)
			insert(move(kv));
}

template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K & k) const
{
	hash<K> myhash;
	return myhash(k) % hashVector.size();
}

template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below(unsigned long n)
{
	if (n <= 1)
	{
			cerr << "** input too small \n";
		return 0;
	}
		
	if (n > max_prime)
   	 {
      		cerr << "** input too large for prime_below()\n";
 		return 0;
   	 }

 	if (n == max_prime)
  	 {
   		return max_prime;
   	 }

 	vector <unsigned long> v (n+1);
	setPrimes(v);
	while (n > 2)
   	{
     		 if (v[n] == 1)
 		       return n;
                 --n;
    }	
 	return 2;
}
 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  	int i = 0;
  	int j = 0;

  	vprimes[0] = 0;
  	vprimes[1] = 0;
  	int n = vprimes.capacity();

 	 for (i = 2; i < n; ++i)
  		  vprimes[i] = 1;

	 for(i = 2; i*i < n; ++i)
   	 {
      		if (vprimes[i] == 1)
       		for(j = i + i ; j < n; j += i)
     		     vprimes[j] = 0;
   	 }
}
#endif

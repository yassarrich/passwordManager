//Name:Yassar Rich
#ifndef PASSSERVER_H
#define PASSSERVER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>
#include <crypt.h>
#include <vector>
#include <list>
#include <utility>
#include "hashtable.h"

using namespace std;
using namespace cop4530;

class PassServer
{
	public:
		PassServer(size_t size = 101);
		~PassServer();

		bool load(const char * filename);
		bool addUser(const pair<string, string> & kv);
		bool addUser(pair<string, string> && kv);
		bool removeUser(const string & k);
		bool changePassword(const pair<string, string> &p, const string & newpasswd);
		bool find(const string & k) const;
		void dump();
		size_t size() const;
		bool write_to_file(const char * filename) const;

	private:
		HashTable<string, string> passwords;
		string encrypt(const string & str);
};

#endif

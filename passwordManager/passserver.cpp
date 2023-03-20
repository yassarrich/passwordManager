//Name:Yassar Rich
#include "passserver.h"
#include "hashtable.h"
#include <cstring>

PassServer::PassServer(size_t size) : passwords(size)
{}

PassServer::~PassServer()
{passwords.clear();}

bool PassServer::load(const char * filename)
{return passwords.load(filename);}

bool PassServer::removeUser(const string & k)
{passwords.remove(k);}

bool PassServer::find(const string & k) const
{return passwords.contains(k);}

void PassServer::dump()
{passwords.dump();}

size_t PassServer::size() const
{passwords.size();}

bool PassServer::write_to_file(const char * filename) const
{passwords.write_to_file(filename);}

bool PassServer::addUser(const pair<string, string> & kv)
{
	string encryptedPass = encrypt(kv.second);
	pair<string, string> encryptPair(kv.first, encryptedPass);
	return passwords.insert(encryptPair);
}

bool PassServer::addUser(pair<string, string> && kv)
{
	pair<string, string> encryptPair(std::move(kv));
	return addUser(encryptPair);
}


bool PassServer::changePassword(const pair<string, string> &p, const string & newpasswd)
{
	if ((p.second == newpasswd) || (!passwords.contains(p.first)))
		return false;

	else
	{
		string oldPass = encrypt(p.second);
		string newPass = encrypt(newpasswd);
		pair<string, string> oldPair(p.first, oldPass);

		//If passwords are the same
		if(!passwords.match(oldPair))
			return false;

		else
		{
			pair<string, string> newPair(p.first, newPass);
			passwords.insert(newPair);
			return false;
		}
	}
	return true;
}

string PassServer::encrypt(const string & str)
{
	//Preceding encryption string
	char salt[] = "$1$########";
	string encryptedPass = crypt(str.c_str(), salt);
	encryptedPass.replace(0, 12, "");
	return encryptedPass;
}

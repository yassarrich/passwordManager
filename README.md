# Password Manager

## Hash Table Class Template
This project contains a HashTable class template named HashTable, The implementation of HashTable is split between the following two files:

hashtable.h: contains the HashTable class template declaration.

hashtable.hpp: contains the implementation of member functions.

The HashTable class template is implemented using the technique of chaining with separate lists (separate chaining) where the internal data structure of the hash table class template is a vector of lists. The STL containers are used for the internal storage.

### Public HashTable interface
(K and V are template parameters (generic data types), which represent the key and value types for a table entry, respectively)

HashTable(size_t size = 101): constructor. Create a hash table, where the size of the vector is set to prime_below(size) (where size is default to 101), where prime_below() is a private member function of the HashTable and provided to you.


bool contains(const K & k): check if key k is in the hash table.

bool match(const std::pair &kv) : check if key-value pair is in the hash table.

bool insert(const std::pair & kv): add the key-value pair kv into the hash table. Don't add if kv is already in the hash table. If the key is the hash table but with a different value, the value should be updated to the new one with kv. Return true if kv is inserted or the value is updated; return false otherwise (i.e., if kv is in the hash table).

bool insert (std::pair && kv): move version of insert.

bool remove(const K & k): delete the key k and the corresponding value if it is in the hash table. Return true if k is deleted, return false otherwise (i.e., if key k is not in the hash table).

void clear(): delete all elements in the hash table

bool load(const char *filename): load the content of the file with name filename into the hash table. In the file, each line contains a single pair of key and value, separated by a white space.

void dump(): display all entries in the hash table. If an entry contains multiple key-value pairs, separate them by a semicolon character (:) (see the provided executable for the exact output format).

bool write_to_file(const char *filename): write all elements in the hash table into a file with name filename. Similar to the file format in the load function, each line contains a pair of key-value pair, separated by a white space.

## Password Server
This program implements a password server, named PassServer, as an adapter class for the HashTable class. The PassServer class stores username and encrypted password pairs in the hash table

### The PassServer class has the following member functions:

PassServer(size_t size = 101): Constructor that creates a hash table of the specified size. The size parameter is passed to the constructor of the HashTable, and the real hash table size may differ from the parameter size because the prime_below() function is called in the constructor of the HashTable.

bool addUser(std::pair<string, string> & kv): Adds a new username and password pair to the hash table. The password passed in is in plaintext, and it is encrypted before insertion.

bool addUser(std::pair<string, string> && kv): Move version of addUser().

bool removeUser(const string & k): Deletes an existing user with the specified username.

bool changePassword(const std::pair<string, string> &p, const string & newpassword): Changes an existing user's password. The old and new passwords are passed in as plaintext, and they are encrypted before being interacted with the hash table. Returns false if the user is not in the hash table or if the old password does not match the current password, or if the new password and the old password are the same.
bool find(const string & user): Checks if a user exists in the hash table.

bool write_to_file(const char *filename): Saves the username and password pairs to a file in the same format as the write_to_file() function in the HashTable class template.

### Please note that the program has functions not detailed above which improve either user or internal functionality


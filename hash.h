#include <bits/stdc++.h>
using namespace std;

#define TABLE_SIZE 13

#define PRIME 7
#define RESET "\033[0m"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"

#define BOLDRED "\033[1m\033[31m"
#define BOLDGREEN "\033[1m\033[32m"
#define BOLDBLUE "\033[1m\033[34m"
#define BOLDWHITE "\033[1m\033[37m"

#include <string>
#include <sstream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

class HashFunction
{

    int *hashTable;
    int curr_size;
    string username;
    string hashcode;

public:
    bool isFull()
    {

        return (curr_size == TABLE_SIZE);
    }

    int hash1(int key)
    {
        return (key % TABLE_SIZE);
    }

    int hash2(int key)
    {
        return (PRIME - (key % PRIME));
    }

    HashFunction()
    {
        hashTable = new int[TABLE_SIZE];
        curr_size = 0;
        for (int i = 0; i < TABLE_SIZE; i++)
            hashTable[i] = -1;
    }

    void insertuser(string key)
    {
        username = key;
    }

    string getusername()
    {
        return username;
    }

    void insertHash(int key)
    {
        if (isFull())
            return;

        int index = hash1(key);
        if (hashTable[index] != -1)
        {

            int index2 = hash2(key);
            int i = 1;
            while (1)
            {
                int newIndex = (index + i * index2) % TABLE_SIZE;

                if (hashTable[newIndex] == -1)
                {
                    hashTable[newIndex] = key;
                    break;
                }
                i++;
            }
        }

        else
            hashTable[index] = key;
        curr_size++;
    }

    void buildthashcode()
    {

        for (int i = 0; i < TABLE_SIZE ; i++)
        {

            hashcode += patch::to_string(i);
            if (hashTable[i] != -1)
                hashcode += patch::to_string(hashTable[i]);
            else
            {
                hashcode += "0";
            }
        }
    }

    string gethashcode()
    {
        return (hashcode);
    }

    void displayhashtable()
    {
        cout << BOLDWHITE "\nHash Table\n"
             << endl;
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            if (hashTable[i] != -1)
                cout << i << " --> "
                     << hashTable[i] << endl;
            else
                cout << i << endl
                     << RESET;
        }
    }

    bool validatehash(string pass)
    {
        HashFunction t;
        t.cleartemp();
        for (int i = 0; pass[i] != '\0'; i++)
        {
            t.insertHash(pass[i]);
        }
        t.buildthashcode();
        if (hashcode == t.gethashcode())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void cleartemp()
    {

        hashTable = new int[TABLE_SIZE];
        curr_size = 0;
        for (int i = 0; i < TABLE_SIZE; i++)
            hashTable[i] = -1;
        username = "";
        hashcode = "";
    }
};

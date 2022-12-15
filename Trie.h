#include<iostream>
#include<vector>
#include<string>
#define size_of_array 26
using namespace std;

struct trie
{
	trie *word[ size_of_array ];
	bool null_character;
	string meaning;
};

trie *newTrie()
{
	trie *root = new trie;
	root->null_character = false;
	for(int i = 0; i < size_of_array ; i++)
	{
		root->word[i] = NULL;
	}
	return root;
}

void insertTrie(trie *root, string word, string meaning)
{
	if( root == NULL )
	{
		root = newTrie();
	}
	for( int i = 0; word[i] ; i++ )
	{
		int position = int( word[ i ] - 'a' );
		if( root->word[ position ] == NULL)
		{
			root->word[ position ] = newTrie();
		}
		root = root->word[ position ];
	}
	root->null_character = true;
	root->meaning = meaning;
}

trie *searchTrie(trie *root, string word)
{
	if( root == NULL )
	{
		return NULL;
	}
	else
	{
		for( int i = 0; word[i] ; i++ )
		{
			int position = int( word[ i ] - 'a' );
			if( root->word[ position ] == NULL )
			{
				return NULL;
			}
			root = root->word[ position ];
		}
		if(root->null_character == true)
		{
			return root;
		}
		else
		{
			return NULL;
		}
	}
}
void autofill_reccursion(trie *root, string word, vector <string>&prefixs)
{
	if(root->null_character == true)
	{
		prefixs.push_back(word);
	}
	for( int i = 0; i < size_of_array; i++ )
	{
		if(root->word[i])
		{
			char character = i + 97;
			word.push_back( character );
			autofill_reccursion(root->word[i], word, prefixs);
			word.erase(word.size() - 1);
		}
	}
}

int autofill( trie *root, string word, vector <string>&prefixs )
{
	if( root == NULL )
	{
		return 0;
	}
	else
	{
		for( int i = 0; word[i] ; i++ )
		{
			int position = int( word[ i ] - 'a' );
			if( root->word[ position ] == NULL )
			{
				return 0;
			}
			root = root->word[ position ];
		}
		
		autofill_reccursion(root, word, prefixs);
		return 1;
	}
}



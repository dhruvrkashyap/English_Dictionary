#include<fstream>
#include "Trie.h"
#include<string.h>
using namespace std;
void readFile_insertTrie(trie *root)
{
	ifstream fin("Dictionary.txt");
	char word[30], meaning[100];
	while(fin)
	{
		fin.getline(word, 30, '\n');
		fin.getline(meaning, 100, '\n');
		insertTrie(root, word, meaning);
	}
	fin.close();
}
void writeFile_insertTrie(trie *root)
{
	fstream fout("Dictionary.txt", ios::binary | ios::out | ios::app);
	string word, meaning;
	
	cout<<"Enter word:";
	//cin.get();
	getline(cin, word);
	
	cout<<"Enter meaning of the word:";
	getline(cin, meaning);
	
	fout<<word<<"\n";
	fout<<meaning<<"\n";
	
	insertTrie(root, word, meaning);
	fout.close();
}

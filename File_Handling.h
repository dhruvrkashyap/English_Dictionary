#include<fstream>
#include "Trie.h"
#include"hash.h"
#include"color_set.h"
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
	//cin.get();
	getline(cin, meaning);
	
	fout<<word<<"\n";
	fout<<meaning<<"\n";
	
	insertTrie(root, word, meaning);
	fout.close();
}

void readAuthFile_insertTrie(trie *root)
{
	ifstream fin("Authentication.txt");
	char username[30], pass[100];
	while(fin)
	{
		fin.getline(username, 30, '\n');
		fin.getline(pass, 100, '\n');
		insertTrie(root, username, pass);
	}
	fin.close();
}

void writeAuthFile_insertTrie(trie *root)
{
	fstream fout("Authentication.txt", ios::binary | ios::out | ios::app);
	string username, pass="";
	
	
	cout<<"Enter username:";
	//cin.get();
	getline(cin, username);
	
	cout<<"Enter password:";
	char ch;
	int n=0;
	set_color("red");
	ch=getch();
	while(ch!='\r')
	{
		n++;
		pass=pass+ch;
		cout<<"*";
		ch=getch();
	}
	set_color("white");
	HashFunction ob;
	ob.cleartemp();
	for (int i = 0; pass[i] != '\0'; i++)
    {
       	ob.insertHash(pass[i]);
    }
    ob.buildthashcode();
    pass = ob.gethashcode();
	fout<<username<<"\n";
	fout<<pass<<"\n";
	
	insertTrie(root, username, pass);
	fout.close();
}

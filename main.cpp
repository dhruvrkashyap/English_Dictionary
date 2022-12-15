#include<conio.h>
#include<iomanip>
#include "File_Handling.h"
using namespace std;
void autocomplete_print(string word, vector <string>&prefix, int position_of_word)
{
	system("cls");
	cout<<setw(40)<<"English Dictionary\n";
	cout<<setw(20)<<"Enter a word:";
	set_color("red");
	cout<<word<<endl;
	set_color("white");	
	for(int i=0;i<prefix.size(); i++)
	{
		if( position_of_word == i)
		{
			set_color("yellow");
			cout<<prefix[i]<<endl;
			set_color("white");
		}
		else
		{
			set_color("green");
			cout<<prefix[i]<<endl;
			set_color("white");
		}
	}
}
int autocomplete(trie *root, string word, vector <string>&prefix)
{
	system("cls");
	char ch;
	int position_of_word=0, temp;
	word="";
	cout<<setw(40)<<"English Dictionary\n";
	cout<<setw(20)<<"Enter a word:";
	while( true )
	{
        if(kbhit())
		{
			set_color("red");
			ch=getche();
			set_color("white");
			if(ch == '\r')
			{
				break;
			}
			if(ch == (char)0 || ch == (char)224)
			{
				ch=getch();
				if(ch == 'P')
				{
					position_of_word++;
					if(position_of_word > prefix.size()-1)
						position_of_word--;
				}
				else if(ch == 'H')
				{
					position_of_word--;
					if(position_of_word < 0)
						position_of_word++;
				}
        		autocomplete_print(word, prefix, position_of_word);
			}
			else if(ch == (char)8)
			{
				if(word.empty())
					continue;
				word.erase(word.size() - 1);
        		prefix.clear();
        		temp=autofill(root, word, prefix);
        		if(word.empty())
        		{
        			system("cls");
					cout<<setw(40)<<"English Dictionary\n";
					cout<<setw(20)<<"Enter a word:";
					set_color("red");
					cout<<word<<endl;
					cout<<"\nPlease enter a word to search\n";
					set_color("white");
				}
        		else if(temp == 0)
        		{
        			system("cls");
					cout<<setw(40)<<"English Dictionary\n";
					cout<<setw(20)<<"Enter a word:";
					set_color("red");
					cout<<word<<endl;
					cout<<"\nWord not found\n";
					set_color("white");
				}
        		else
        		{
        			position_of_word=0;
					autocomplete_print(word, prefix, position_of_word);
				}
			}
			else
			{
				word=word+ch;
        		prefix.clear();
        		temp=autofill(root, word, prefix);
        		if(temp == 0)
        		{
					system("cls");
					cout<<setw(40)<<"English Dictionary\n";
					cout<<setw(20)<<"Enter a word:";
					set_color("red");
					cout<<word<<endl;
					cout<<"\nWord not found\n";
					set_color("white");
				}
        		else
        		{
					position_of_word=0;
        			autocomplete_print(word, prefix, position_of_word);
        		}
        	}
		}
	}
	return position_of_word;
}
void print_details(int position_of_choice)
{
	system("cls");
	cout<<"\n";
	cout<<setw(40)<<"English Dictionary\n\n";
	set_color("light blue");
	if(position_of_choice == 0)
	{
		set_color("blue");
	}
	cout<<setw(20)<<"Insert\n";
	set_color("light blue");
	if(position_of_choice == 1)
	{
		set_color("blue");
	}
	cout<<setw(20)<<"Search\n";
	set_color("light blue");
	cout<<"\n";
	if(position_of_choice == 2)
	{
		set_color("red");
	}
	cout<<setw(20)<<"Exit\n\n";
	set_color("white");
}
void instructions()
{
	cout<<"\n\n";
	cout<<setw(10)<<"Use Up/Down arrow keys to select the word\n";
}
void loading_bar()
{
	cout<<"\n\n";
	cout<<setw(40)<<"English Dictionary";
	set_color("light blue");
	instructions();
	cout<<"\n\n"<<setw(18);
	set_color("red");
	for(int i=0;i<27;i++)
	{
		cout<<(char)254;
		Sleep(100);
	}
	set_color("white");
	system("cls");
}
void check_auth(trie *auth)
{
	int flag=0, choice;
	do
	{
		string user, pass="";
		flag=0;
		int n=0;
		cout<<"\n\n";
		cout<<setw(40)<<"English Dictionary";
		set_color("light blue");
		cout<<"\n\n"<<setw(18);
		cout<<"Username:";
		set_color("white");
		getline(cin, user);
		if(user.empty())
		{
			set_color("red");
			cout<<setw(18)<<"ENTER A USERNAME";
			Sleep(2000);
			set_color("white");
			system("cls");
			continue;
		}
		set_color("light blue");
		cout<<setw(18)<<"Password:";
		set_color("red");
		char ch;
		ch=getch();
		while(ch!='\r')
		{
			pass=pass+ch;
			cout<<"*";
			ch=getch();
			n++;
		}
		HashFunction ob;
		ob.cleartemp();
		for (int i = 0; pass[i] != '\0'; i++)
        {
        	ob.insertHash(pass[i]);
        }
    	ob.buildthashcode();
    	pass = ob.gethashcode();
		trie *temp=searchTrie(auth, user);
		
		if(temp)
		{
			if(pass.compare(temp->meaning)==0)  //if(strcmp(pass, temp->meaning)==0)
			{
				set_color("green");
				system("cls");
				cout<<"\n\n";
				cout<<setw(18)<<"WElCOME "<<user;
				flag=1;
			}
			else
			{
				set_color("red");
				system("cls");
				cout<<setw(18)<<"ENTERED PASSWORD IS WRONG";
			}
		}
		else
		{
			set_color("red");
			system("cls");
			cout<<setw(18)<<"ENTERED USERNAME IS WRONG";
			set_color("white");
			cout<<setw(18)<<"\n\nSign Up";
			cout<<setw(18)<<"\n1. Yes\t2. No\n";
			cout<<setw(18)<<"\nEnter your choice:";
			cin>>choice;
			fflush(stdin);
			switch(choice)
			{
				case 1:
					writeAuthFile_insertTrie(auth);
					set_color("red");
					cout<<"\nInserted\n";
					set_color("white");
					system("pause");
					break;
				case 2:
					break;
				default:
					set_color("red");
					cout<<"\nINVALID CHOICE\n";
					set_color("white");
			}
			
		}
		set_color("white");
		Sleep(2000);
		system("cls");
	}while(flag!=1);
	
	system("cls");
}
int main()
{
	set_font_size(50,50);
	fullscreen();
	trie *root = newTrie(), *auth = newTrie(), *temp=NULL;
	readFile_insertTrie(root);
	readAuthFile_insertTrie(auth);
    string word="";
    vector <string>prefix;
    int position_of_word=0, position_of_choice=0, flag=0;
	char choice;
	check_auth(auth);
	loading_bar();
	do
    {
		print_details(position_of_choice);
    	choice=getch();
    	if(choice == (char)0 || choice == (char)224)
		{
			choice=getch();
			if(choice == 'P') //down 
			{
				position_of_choice++;
				if(position_of_choice > 2)
					position_of_choice--;
			}
			else if(choice == 'H') //up
			{
				position_of_choice--;
				if(position_of_choice < 0)
					position_of_choice++;
			}
			print_details(position_of_choice);
		}
		else if( choice == '\r' )
		{
    		switch( position_of_choice )
        	{
        		case 0:
    				writeFile_insertTrie(root);
    				set_color("red");
					cout<<"Inserted\n";
					set_color("white");
					system("pause");
					break;
        	    case 1:
        	    	position_of_word=autocomplete(root, word, prefix);
					word = prefix[ position_of_word ];
					temp=searchTrie(root, word);
					system("cls");
					if(temp)
        	    	{
        	    		cout<<setw(40)<<"English Dictionary\n\n";
        	    		set_color("grey");
        	    		cout<<setw(20)<<"Word:";
						set_color("purple");
						cout<<word<<endl;
           		 		set_color("grey");
           		 		cout<<setw(20)<<"Meaning:";
						set_color("light blue");
						cout<<temp->meaning<<endl<<endl;
            			set_color("white");
            			system("pause");
					}
					else
					{
						set_color("red");
						cout<<"Word not found\n";
						set_color("white");
					}
					break;
        		case 2:
        			flag=1;
        			break;
        		default:
            		cout<<"Incorrect Choice\n";
        	}
		}
	}while(position_of_choice != 2 || flag == 0);
}

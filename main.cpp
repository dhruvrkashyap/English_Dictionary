#include<conio.h>
#include<iomanip>
#include "File_Handling.h"
#include "color_set.h"
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
int main()
{
	set_font_size(50,50);
	fullscreen();
	trie *root = newTrie(), *temp=NULL;
	readFile_insertTrie(root);
    string word="";
    vector <string>prefix;
    int position_of_word=0, position_of_choice=0, flag=0;
	char choice;
	loading_bar();
	do
    {
		print_details(position_of_choice);
    	choice=getch();
    	if(choice == (char)0 || choice == (char)224)
		{
			choice=getch();
			if(choice == 'P')
			{
				position_of_choice++;
				if(position_of_choice > 2)
					position_of_choice--;
			}
			else if(choice == 'H')
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

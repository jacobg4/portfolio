#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <stdlib.h>
#include <random>
#include <time.h>
//#include "Monsters.h"
#include <fstream>

using namespace std;

void Red()
{
    SetConsoleTextAttribute
    (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
} //Intensive red console text color.

void Green()
{
    SetConsoleTextAttribute
    (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
} //Intensive green console text color.

void Normal()
{
    SetConsoleTextAttribute
        (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
} //Default console text color.

int monster_life;

struct Monster
{
    string monster;
    string attacktype;
    int damage;
    int ac;
    string type;
};

int monster_attack (int &player_life)
{
	int damage = (rand ()%(damage-1+1)) +1;
	player_life = player_life - damage;
	cout << "You have taken a hit." << "Damage: " << damage << endl;
	if (player_life < 0)
	{
		cout <<"You have died\n";
        cout<<"Aren't you a sorry exuse for an adventurer.\n";
	}
	else
	{
		cout << "Your life is now " << player_life << endl;
	}
	return player_life;
}

int player_attack (int monster_life)
{
    struct Montster mon;
	int damage = (rand ()%(8-1+1)) +1;
	monster_life = monster_life - damage;
	cout << "The "<<mon.monster<< "have taken a hit. " << "Damage: " << damage << endl;
	if (monster_life < 0)
	{
		cout <<"You have succesfully defeated the "<< mon.monster <<".\n";
	}
	return monster_life;
}

void getAction(int &player_life, int monster_life)
{
    int action;
    do{
        cout<<"Possible actions are as follows:\n"<<"1) to make an attack\n"
        <<"2) to make a stealth attack \n"<<"3) to retreat 4) to use item\n";
        cin>>action;
        switch (action)
        {
            case 1:
                while(player_life>0&&monster_life>0)
                {
                    monster_life=player_attack(monster_life);
                    if (monster_life>0)
                    {
                        player_life=monster_attack(player_life);
                    }
                };
                break;
            case 2:
                monster_life=player_attack(monster_life);
                while(player_life>0&&monster_life>0)
                {
                    monster_life=player_attack(monster_life);
                    if (monster_life>0)
                    {
                        player_life=monster_attack(player_life);
                    }
                };
                break;
            case 3:
                cout<<"You have escaped death... for now\n";
                break;
            case 4:
                for (int i=0;i<20;i++)
                {
                    //access inventory either vector or array
                }
                break;
            defualt:
                action=-1;
        }
    } while(action==-1);
}

void ChapterOne(char name[50], int &player_life)
{
    int choice;
    cout<<"--Chapter 1--\n";
    cout<<endl;
    cout<<"You leave your home town of Brimsby heading towards the call to adventure\n";
    cout<<"After leaving town you are attacked by a lone wolf\n";
    getAction(player_life, 20);
    system ("PAUSE");
    cout<<"As you continue down the path you chance upon a small babbing brook."
    <<"The water looks cool and refreshing. You can hear birds chirping an inviting tune like a song of rest\n";
    cout<<"Would you like to rest here?\n";
    cout<<"Enter 1 to rest or anyother key to continue\n";
    cin>>choice;
    if (choice==1)
    {
        cout<<"You rest and drink from the brook, you feel rejuvinated.\n"
        <<"your life is now "<<(player_life+(rand ()%(8-1+1)) +1)<<endl;
    }
    else
    {
        cout<<"ignoring the stream...";
    }
    cout<<"You continue on your way\n";
    system ("PAUSE");
}

void ChapterTwo(char name[50], int &player_life)
{
    cout<<"--Chapter 2--\n";
}

int main()
{
    char name[50];
    int choice;
    bool life;
    int player_life = 100;
    srand ( time(0) ); //initialize the random seed
    do{
        cout<<"What are you called?\n";
        cin.getline(name, 50);
        cout<<"The world awaits, "<<name<<". Are you ready to obtain glory and riches?\n";
        cout<<"Enter 1 to continue or 2 to change name... (this is the last time you can change your name)\n";
        cin>>choice;
    }while (choice!=1);
    system ("PAUSE");
    cout<<name<<", the adventure begins...\n";
    ChapterOne(name, player_life);
    if (life!=true)
    {

    }
    return 0;
}
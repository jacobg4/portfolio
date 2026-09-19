//Jacob Givhan
//j_givhan4@hotmail.com

#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <string>

using namespace std;
//functions and global variables
void displayMenu(int&);
void betPlacement(int&,int&);
bool validation(int, int&);
void dealer(int&,string&, int&);
void blackjack();
char blackjackWinLose(int,int&, int, int, int&);
void hit(int&, string&);
void stay(int&, string&);
void quit();
void writeHistory(int, string,int,string,char,int);
void displayHistory();
bool datOut(bool&);
ifstream dataIn;
ofstream dataOut;
int option, cardValue, bet, balance;
string dcard="", cardFace, playerhand, dealerhand;
int hand=0, cardsDealt;
int playerScore=0;
int dealerScore=0;
char winloss;

int main()
{
	int menu;
	dataOut.open("GivhanHistory.txt");
	srand(time(NULL));
	
	do
	{
		displayMenu(menu);
	}while(menu!=3);
	return 0;
}

//	********************************************************************************************************************************
//																	Menu
//
//	task:			This function gives the player the option to play a game, view game history or quit the game
//	data in:		N/A
//	data returned:	N/A
//
//	********************************************************************************************************************************
void displayMenu(int &men)
{
	cout<<"Menu\n"<<"1. Play new game\n"<<"2. View game history\n"<<"3. Quit Game\n";
	cout<<"Please enter 1, 2, or 3 to make your selection.\n";
	cin>>men;
	switch(men)
	{
		case 1:
			blackjack(); //cardValue(), hit(), stay(), and writeHistory, will be inside blackjackWinLose()
			break;
		case 2:
			displayHistory();
			break;
		case 3:
			quit();
			break;
		default:
			cout<<"Invalid entry\n";
			cout<<"Please enter 1, 2, or 3 to make your selection.\n";
	}
}

//	********************************************************************************************************************************
//																	bet
//
//	task:			This function asks for the balance and the wager
//	data in:		N/A
//	data returned:	bet, balance
//
//	********************************************************************************************************************************
void betPlacement(int &betting,int &bal)
{
	bool valid;
	
	if (bal>0)
	{
		cout<<"Your current balance is "<<bal<<endl;
	}
	else
	{
		do
		{
			cout<<"What is your current balance?\n";
			cin>>bal;
		}while(bal<=0);
		cout<<"What would you like to bet?\n";
	}
	do
	{
		cout<<"(Minimum bet of $10 required and max allowed bet of $150)\n";
		cin>>betting;
		valid = validation(betting, bal);
	}while(valid==false);
}

//	********************************************************************************************************************************
//																	validation
//
//	task:			This function validates the bet entry
//	data in:		bet
//	data returned:	validation
//
//	********************************************************************************************************************************
bool validation(int bet, int &balance)
{
	bool validity;
	
	if(bet<10||bet>150)
	{
		cout<<"Improper bet\n";
		validity = false;
	}
	else
	{
		balance-=bet;
		cout<<"New game starting\n";
		validity = true;
	}
	return validity;
}

/*
*********************************************************************************************************************************
																	main game function
																	
	task:			This function runs the actual game and is the core function of the play game menu option.
	data in:		bet, balance
	data returned:	None, it writes the game details to a .txt file.
	
*********************************************************************************************************************************
*/
void blackjack()
{
	int option, cardValue;
	string dcard="", cardFace, playerhand="", dealerhand="";
	int cardsDealt;
	int playerScore=0;
	int dealerScore=0;
	char winloss;
	//insert game code
	//call dealer(), hit(), and stay() as needed
	betPlacement(bet,balance); //validation() will be inside bet()
	for (cardsDealt=0;cardsDealt<2;++cardsDealt)
	{
		dealer(cardValue, cardFace, playerScore);
		playerhand+=cardFace;
		playerScore+=cardValue;
		dealer(cardValue, cardFace, dealerScore);
		dealerhand+=cardFace;
		dealerScore+=cardValue;
		dcard=cardFace;
	}
	if(playerScore<21)
	{
		for (cardsDealt=2;cardsDealt<5&&playerScore<21&&option!=2;++cardsDealt)
		{
			do
			{
				cout<<"Your hand is "<<playerhand<<endl;
				cout<<"The dealer has a "<<dcard<<" visible\n";
				cout<<"You can be dealt another card or stay\n";
				cout<<"To be dealt another card, enter 1\n";
				cout<<"To stay enter 2\n";
				cin>>option;
				switch(option)
				{
					case 1:
						hit(playerScore, playerhand);
						break;
					case 2:
						stay(dealerScore, dealerhand);
						break;
					default:
						cout<<"Improper input\n";
				}
			}while(option!=1&&option!=2);
		}
		if(playerScore>21)
		{
			winloss=blackjackWinLose(bet,balance,playerScore,dealerScore, hand);
		}
		else if (dealerScore<17)
		{
			stay(dealerScore, dealerhand);
			winloss=blackjackWinLose(bet,balance,playerScore,dealerScore, hand);
		}
		else
		{
			winloss=blackjackWinLose(bet,balance,playerScore,dealerScore, hand);
		}
	}
	else
	{
		winloss=blackjackWinLose(bet,balance,playerScore,dealerScore, hand);
	}
	writeHistory(hand,playerhand,bet,dealerhand,winloss,balance);
}

/*
																	winloss
																	
																	
	task:			This function compares the scores between the dealer and the player to declare a winner.

data in: 		bet, balance, playerScore, dealerScore
data returned: 	winloss
*/
char blackjackWinLose(int bet, int &bal, int playerScore, int dealerScore, int& round)
{
	char winloss;
	if(dealerScore>21||playerScore>21)
	{
		if(dealerScore>21&&playerScore>21)
		{
			cout<<"Push\n";
			bal+=bet;
			++round;
			winloss='D';
		}
		else if(dealerScore>21)
		{
			cout<<"Dealer Busts\n";
			bal+=(2*bet);
			++round;
			winloss='W';
		}
		else
		{
			cout<<"You busted...\n";
			++round;
			winloss='L';
		}
	}
	else if(dealerScore==21||playerScore==21)
	{
		if(dealerScore==21&&playerScore==21)
		{
			cout<<"Push\n";
			bal+=bet;
			++round;
			winloss='D';
		}
		else if(dealerScore==21)
		{
			cout<<"Dealer has Blackjack\n";
			++round;
			winloss='L';
		}
		else
		{
			cout<<"Congratulaions! You have Blackjack!\n";
			bal+=(2*bet);
			++round;
			winloss='W';
		}
	}
	else
	{
		if(playerScore>=dealerScore)
		{
			if(playerScore==dealerScore)
			{
				cout<<"Push\n";
				++round;
				bal+=bet;
				winloss='D';
			}
			else
			{
				cout<<"You win!\n";
				++round;
				bal+=(2*bet);
				winloss='W';
			}
		}
		else
		{
			cout<<"Dealer wins\n";
			++round;
			winloss='L';
		}
	}	
	return winloss;
}

/*
						Card dealer and value assignment
				
				
task:			This function takes a random number and uses it to generate the cards dealt to the player and dealer
data in:		score
data returned:	cardValue, cardFace	
*/
void dealer(int &value,string &face,int &score)
{
	int card;
	
	do
	{
		card = (rand()%14+1);
		switch(card)
		{
			case 1: 
				value=2;
				face="2";
				break;
			case 2:
				value=3;
				face="3";
				break;
			case 3:
				value=4;
				face="4";
				break;
			case 4:
				value=5;
				face="5";
				break;
			case 5:
				value=6;
				face="6";
				break;
			case 6:
				value=7;
				face="7";
				break;
			case 7:
				value=8;
				face="8";
				break;
			case 8:
				value=9;
				face="9";
				break;
			case 9:
				value=10;
				face="10";
				break;
			case 10:
				value=10;
				face="J";
				break;
			case 11:
				value=10;
				face="Q";
				break;
			case 12:
				value=10;
				face="K";
				break;
			case 13:
				if(score<=10)
					value=11;
				else
					value=1;
				face="A";
				break;
			default:
				card=14;
		}
	}while(card==14);
}
//deals an additional card by calling the cardValue() function
void hit(int &score, string &hand)
{
	int cardValue;
	string cardFace;
	dealer(cardValue,cardFace,score);
	hand+=cardFace;
	score+=cardValue;
}

//	********************************************************************************************************************************
//																	stay
//
//	task:			This function signifies the end of the players turn and allows the dealer to play out if they have less than 17
//	data in:		dealerhand, dealerScore, playerScore, playerhand, hand, balance
//	data returned:	N/A
//
//	********************************************************************************************************************************
void stay(int &score,string &hand)
{
	//dealer plays out if <17
	int cardsDealt;
	int cardValue;
	string cardFace;

	if(score<17)
	{
		for (cardsDealt=2;cardsDealt<5&&score<17;++cardsDealt)
		{
			dealer(cardValue,cardFace,score);
			hand+=cardFace;
			score+=cardValue;
		}
	}	
}

//	********************************************************************************************************************************
//																	writeHistory
//
//	task:			This function writes the game results to a .txt file
//	data in:		hand, playerhand, bet, dealerhand, winloss, balance
//	data returned:	N/A
//
//	********************************************************************************************************************************
void writeHistory(int hand,string playerhand,int bet,string dealerhand,char winloss,int balance)
{
	dataOut<<left<<setw(5)<<hand<<setw(20)<<playerhand<<setw(5)<<bet<<setw(20)<<dealerhand<<setw(5)<<winloss<<setw(5)<<balance<<endl;
}

//	********************************************************************************************************************************
//																	displayHistory
//
//	task:			This function displays the previous game history
//	data in:		N/A
//	data returned:	N/A
//
//	********************************************************************************************************************************
void displayHistory()
{
	dataOut.close();
	dataIn.open("GivhanHistory.txt");
	if(dataIn) //history here
	{
		cout<<setw(8)<<"hand"<<setw(15)<<"Players Cards"<<setw(15)<<"Bet"<<setw(15)<<"Dealer"<<setw(15)<<"W/L"<<setw(15)<<"Balance\n";
		while(dataIn>>hand>>playerhand>>bet>>dealerhand>>winloss>>balance)
		{
			cout<<setw(5)<<hand<<setw(12)<<playerhand<<setw(21)<<bet<<setw(14)<<dealerhand<<setw(15)<<winloss<<setw(15)<<balance<<endl;
		}
	}
	else
		cout<<"No game history found\n";
	dataIn.close();
	dataOut.open("GivhanHistory.txt");
}

void quit()
{
	cout<<"Thanks for playing\n";
	dataOut.close();
}
//Jacob Givhan
//j_givhan4@hotmail.com

#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <string>

using namespace std;

int main()
{
	ifstream dataIn;
	ofstream dataOut;
	int bet, balance, cards, cardValue, cardsDealt, hand, menu, menu2, playerScore=0, dealerScore=0,card1,card2,card3,card4,card5, dcard1, dcard2, dcard3, dcard4, dcard5;
	string playerhand, dealerhand, card, dcard, pcard1, pcard2, pcard3=" ", pcard4=" ", pcard5=" ";
	char winloss;
	dataOut.open("GivhanHistory.txt");
	do
	{
		
		
		
		cout<<"Menu\n"<<"1. Play new game\n"<<"2. View game history\n"<<"3. Quit Game\n";
		cout<<"Please enter 1, 2, or 3 to make your selection.\n";
		cin>>menu;
		
		switch(menu)
		{
			case 1:
				
				cout<<"What is your current balance?\n";
				cin>>balance;
				cout<<"What would you like to bet?\n";
				do
				{
					cout<<"(Minimum bet of $10 required and max allowed bet of $150)\n";
					cin>>bet;
					if(bet<10 || bet>150)
					{
						cout<<"Improper bet\n";
					}
					else
					{
						balance-=bet;
						cout<<"New game starting\n"; //game code here
					}
				}while(bet<10||bet>150);
				if(dataIn)
				{
					dataIn>>hand;
				}
				else
				{
					hand=1;
				}
				srand(time(NULL));
				card1 = (rand()%14+1);
				switch(card1)
				{
					case 1: 
						cardValue=2;
						pcard1="2";
						break;
					case 2:
						cardValue=3;
						pcard1="3";
						break;
					case 3:
						cardValue=4;
						pcard1="4";
						break;
					case 4:
						cardValue=5;
						pcard1="5";
						break;
					case 5:
						cardValue=6;
						pcard1="6";
						break;
					case 6:
						cardValue=7;
						pcard1="7";
						break;
					case 7:
						cardValue=8;
						pcard1="8";
						break;
					case 8:
						cardValue=9;
						pcard1="9";
						break;
					case 9:
						cardValue=10;
						pcard1="10";
						break;
					case 10:
						cardValue=10;
						pcard1="J";
						break;
					case 11:
						cardValue=10;
						pcard1="Q";
						break;
					case 12:
						cardValue=10;
						pcard1="K";
						break;
					case 13:
						if(playerScore<=10)
							cardValue=11;
						else
							cardValue=1;
						pcard1="A";
						break;
					default: cout<<"Game error";
				}
				playerhand+=" "+pcard1;
				playerScore+=cardValue;
				card2 = (rand()%14+1);
				switch(card2)
				{
					case 1: 
						cardValue=2;
						pcard2="2";
						break;
					case 2:
						cardValue=3;
						pcard2="3";
						break;
					case 3:
						cardValue=4;
						pcard2="4";
						break;
					case 4:
						cardValue=5;
						pcard2="5";
						break;
					case 5:
						cardValue=6;
						pcard2="6";
						break;
					case 6:
						cardValue=7;
						pcard2="7";
						break;
					case 7:
						cardValue=8;
						pcard2="8";
						break;
					case 8:
						cardValue=9;
						pcard2="9";
						break;
					case 9:
						cardValue=10;
						pcard2="10";
						break;
					case 10:
						cardValue=10;
						pcard2="J";
						break;
					case 11:
						cardValue=10;
						pcard2="Q";
						break;
					case 12:
						cardValue=10;
						pcard2="K";
						break;
					case 13:
						if(playerScore<=10)
							cardValue=11;
						else
							cardValue=1;
						pcard2="A";
						break;
					default: cout<<"Game error";
				}
				playerhand+=" "+pcard2;
				playerScore+=cardValue;
				dcard1 = (rand()%14+1);
				switch(dcard1)
				{
					case 1: 
						cardValue=2;
						card="2";
						break;
					case 2:
						cardValue=3;
						card="3";
						break;
					case 3:
						cardValue=4;
						card="4";
						break;
					case 4:
						cardValue=5;
						card="5";
						break;
					case 5:
						cardValue=6;
						card="6";
						break;
					case 6:
						cardValue=7;
						card="7";
						break;
					case 7:
						cardValue=8;
						card="8";
						break;
					case 8:
						cardValue=9;
						card="9";
						break;
					case 9:
						cardValue=10;
						card="10";
						break;
					case 10:
						cardValue=10;
						card="J";
						break;
					case 11:
						cardValue=10;
						card="Q";
						break;
					case 12:
						cardValue=10;
						card="K";
						break;
					case 13:
						if(dealerScore<=10)
							cardValue=11;
						else
							cardValue=1;
						card="A";
						break;
					default: cout<<"Game error";
				}
				dealerScore+=cardValue;
				dealerhand+=" "+card;
				dcard2 = (rand()%14+1);
				switch(dcard2)
				{
					case 1: 
						cardValue=2;
						card="2";
						break;
					case 2:
						cardValue=3;
						card="3";
						break;
					case 3:
						cardValue=4;
						card="4";
						break;
					case 4:
						cardValue=5;
						card="5";
						break;
					case 5:
						cardValue=6;
						card="6";
						break;
					case 6:
						cardValue=7;
						card="7";
						break;
					case 7:
						cardValue=8;
						card="8";
						break;
					case 8:
						cardValue=9;
						card="9";
						break;
					case 9:
						cardValue=10;
						card="10";
						break;
					case 10:
						cardValue=10;
						card="J";
						break;
					case 11:
						cardValue=10;
						card="Q";
						break;
					case 12:
						cardValue=10;
						card="K";
						break;
					case 13:
						if(dealerScore<=10)
							cardValue=11;
						else
							cardValue=1;
						card="A";
						break;
					default: cout<<"Game error";
				}
				dealerScore+=cardValue;
				dcard=card;
				dealerhand+=" "+card;
				if(dealerScore>21||playerScore>21)
				{
					if(dealerScore>21&&playerScore>21)
					{
						cout<<"Push\n";
						balance+=bet;
						++hand;
						winloss='D';
						
						dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
						dataOut.close();
					}
					else if(dealerScore>21)
					{
						cout<<"Dealer Busts\n";
						balance+=(2*bet);
						++hand;
						winloss='W';
						
						dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
						dataOut.close();
					}
					else
					{
						cout<<"You busted...\n";
						++hand;
						winloss='L';
						
						dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
						dataOut.close();
					}
				}
				else if(dealerScore==21||playerScore==21)
				{
					if(dealerScore>21&&playerScore>21)
					{
						cout<<"Push\n";
						balance+=bet;
						++hand;
						winloss='D';
						
						dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
						dataOut.close();
					}
					else if(dealerScore==21)
					{
						cout<<"Dealer has Blackjack\n";
						++hand;
						winloss='L';
						
						dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
						dataOut.close();
					}
					else
					{
						cout<<"Congratulaions! You have Blackjack!\n";
						balance+=(2*bet);
						++hand;
						winloss='W';
						
						dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
						dataOut.close();
					}
				}
				else
				{
					do
					{
						cout<<"Your hand is "<<pcard1<<","<<pcard2<<endl;
						cout<<"The dealer has a "<<dcard<<" visible\n";
						cout<<"You can be dealt another card or stay\n";
						cout<<"To be dealt another card, enter 1\n";
						cout<<"To stay enter 2\n";
						cin>>menu2;
						switch(menu2)
						{
							case 1:
								card3 = rand()%14+1;
								switch(card3)
								{
									case 1: 
										cardValue=2;
										card="2";
										break;
									case 2:
										cardValue=3;
										card="3";
										break;
									case 3:
										cardValue=4;
										card="4";
										break;
									case 4:
										cardValue=5;
										card="5";
										break;
									case 5:
										cardValue=6;
										card="6";
										break;
									case 6:
										cardValue=7;
										card="7";
										break;
									case 7:
										cardValue=8;
										card="8";
										break;
									case 8:
										cardValue=9;
										card="9";
										break;
									case 9:
										cardValue=10;
										card="10";
										break;
									case 10:
										cardValue=10;
										card="J";
										break;
									case 11:
										cardValue=10;
										card="Q";
										break;
									case 12:
										cardValue=10;
										card="K";
										break;
									case 13:
										if(playerScore<=10)
											cardValue=11;
										else
											cardValue=1;
										card="A";
										break;
									default: cout<<"Game error";
								}
								pcard3=card;
								playerScore+=cardValue;
								if(playerScore<=21)
								{
									do
									{
										cout<<"Your hand is "<<pcard1<<","<<pcard2<<","<<pcard3<<endl;
										cout<<"The dealer has a "<<dcard<<" visible\n";
										cout<<"You can be dealt another card or stay\n";
										cout<<"To be dealt another card, enter 1\n";
										cout<<"To stay enter 2\n";
										cin>>menu2;
										switch(menu2)
										{
											case 1:
												card4 = rand()%14+1;
												switch(card4)
												{
													case 1: 
														cardValue=2;
														card="2";
														break;
													case 2:
														cardValue=3;
														card="3";
														break;
													case 3:
														cardValue=4;
														card="4";
														break;
													case 4:
														cardValue=5;
														card="5";
														break;
													case 5:
														cardValue=6;
														card="6";
														break;
													case 6:
														cardValue=7;
														card="7";
														break;
													case 7:
														cardValue=8;
														card="8";
														break;
													case 8:
														cardValue=9;
														card="9";
														break;
													case 9:
														cardValue=10;
														card="10";
														break;
													case 10:
														cardValue=10;
														card="J";
														break;
													case 11:
														cardValue=10;
														card="Q";
														break;
													case 12:
														cardValue=10;
														card="K";
														break;
													case 13:
														if(playerScore<=10)
															cardValue=11;
														else
															cardValue=1;
														card="A";
														break;
													default: cout<<"Game error";
												}
												pcard4=card;
												playerScore+=cardValue;
												if(playerScore<=21)
												{
													do
													{
														cout<<"Your hand is "<<pcard1<<","<<pcard2<<","<<pcard3<<","<<pcard4<<endl;
														cout<<"The dealer has a "<<dcard<<" visible\n";
														cout<<"You can be dealt another card or stay\n";
														cout<<"To be dealt another card, enter 1\n";
														cout<<"To stay enter 2\n";
														cin>>menu2;
														switch(menu2)
														{
															case 1:
																card5 = rand()%14+1;
																switch(card5)
																{
																	case 1: 
																		cardValue=2;
																		card="2";
																		break;
																	case 2:
																		cardValue=3;
																		card="3";
																		break;
																	case 3:
																		cardValue=4;
																		card="4";
																		break;
																	case 4:
																		cardValue=5;
																		card="5";
																		break;
																	case 5:
																		cardValue=6;
																		card="6";
																		break;
																	case 6:
																		cardValue=7;
																		card="7";
																		break;
																	case 7:
																		cardValue=8;
																		card="8";
																		break;
																	case 8:
																		cardValue=9;
																		card="9";
																		break;
																	case 9:
																		cardValue=10;
																		card="10";
																		break;
																	case 10:
																		cardValue=10;
																		card="J";
																		break;
																	case 11:
																		cardValue=10;
																		card="Q";
																		break;
																	case 12:
																		cardValue=10;
																		card="K";
																		break;
																	case 13:
																		if(playerScore<=10)
																			cardValue=11;
																		else
																			cardValue=1;
																		card="A";
																		break;
																	default: cout<<"Game error";
																}
																pcard5=card;
																playerScore+=cardValue;
																if(playerScore<=21)
																{
																	if(dealerScore<17)
																	{
																		dcard3 = (rand()%14+1);
																		switch(dcard3)
																		{
																			case 1: 
																				cardValue=2;
																				card="2";
																				break;
																			case 2:
																				cardValue=3;
																				card="3";
																				break;
																			case 3:
																				cardValue=4;
																				card="4";
																				break;
																			case 4:
																				cardValue=5;
																				card="5";
																				break;
																			case 5:
																				cardValue=6;
																				card="6";
																				break;
																			case 6:
																				cardValue=7;
																				card="7";
																				break;
																			case 7:
																				cardValue=8;
																				card="8";
																				break;
																			case 8:
																				cardValue=9;
																				card="9";
																				break;
																			case 9:
																				cardValue=10;
																				card="10";
																				break;
																			case 10:
																				cardValue=10;
																				card="J";
																				break;
																			case 11:
																				cardValue=10;
																				card="Q";
																				break;
																			case 12:
																				cardValue=10;
																				card="K";
																				break;
																			case 13:
																				if(dealerScore<=10)
																					cardValue=11;
																				else
																					cardValue=1;
																				card="A";
																				break;
																			default: cout<<"Game error";
																		}
																		dealerScore+=cardValue;
																		dealerhand+=" "+card;
																		if(dealerScore<17)
																		{
																			dcard4 = (rand()%14+1);
																			switch(dcard4)
																			{
																				case 1: 
																					cardValue=2;
																					card="2";
																					break;
																				case 2:
																					cardValue=3;
																					card="3";
																					break;
																				case 3:
																					cardValue=4;
																					card="4";
																					break;
																				case 4:
																					cardValue=5;
																					card="5";
																					break;
																				case 5:
																					cardValue=6;
																					card="6";
																					break;
																				case 6:
																					cardValue=7;
																					card="7";
																					break;
																				case 7:
																					cardValue=8;
																					card="8";
																					break;
																				case 8:
																					cardValue=9;
																					card="9";
																					break;
																				case 9:
																					cardValue=10;
																					card="10";
																					break;
																				case 10:
																					cardValue=10;
																					card="J";
																					break;
																				case 11:
																					cardValue=10;
																					card="Q";
																					break;
																				case 12:
																					cardValue=10;
																					card="K";
																					break;
																				case 13:
																					if(dealerScore<=10)
																						cardValue=11;
																					else
																						cardValue=1;
																					card="A";
																					break;
																				default: cout<<"Game error";
																			}
																			dealerScore+=cardValue;
																			dealerhand+=" "+card;
																			if(dealerScore<17)
																			{
																				dcard5 = (rand()%14+1);
																				switch(dcard5)
																				{
																					case 1: 
																						cardValue=2;
																						card="2";
																						break;
																					case 2:
																						cardValue=3;
																						card="3";
																						break;
																					case 3:
																						cardValue=4;
																						card="4";
																						break;
																					case 4:
																						cardValue=5;
																						card="5";
																						break;
																					case 5:
																						cardValue=6;
																						card="6";
																						break;
																					case 6:
																						cardValue=7;
																						card="7";
																						break;
																					case 7:
																						cardValue=8;
																						card="8";
																						break;
																					case 8:
																						cardValue=9;
																						card="9";
																						break;
																					case 9:
																						cardValue=10;
																						card="10";
																						break;
																					case 10:
																						cardValue=10;
																						card="J";
																						break;
																					case 11:
																						cardValue=10;
																						card="Q";
																						break;
																					case 12:
																						cardValue=10;
																						card="K";
																						break;
																					case 13:
																						if(dealerScore<=10)
																							cardValue=11;
																						else
																							cardValue=1;
																						card="A";
																						break;
																					default: cout<<"Game error";
																				}
																				dealerScore+=cardValue;
																				dealerhand+=" "+card;
																				if(dealerScore>21)
																				{
																					cout<<"Dealer Busted\n";
																					balance+=(2*bet);
																					++hand;
																					winloss='W';
																					
																					dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																					dataOut.close();
																				}
																				else if(dealerScore==21)
																				{
																					cout<<"You and the Dealer have 21\n";
																					++hand;
																					winloss='D';
																					balance+=bet;
																					
																					dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																					dataOut.close();
																				}
																				else
																				{
																					if(playerScore>=dealerScore)
																					{
																						if(playerScore==dealerScore)
																						{
																							cout<<"Push\n";
																							++hand;
																							balance+=bet;
																							winloss='D';
																							
																							dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																							dataOut.close();
																						}
																						else
																						{
																							cout<<"You win!\n";
																							++hand;
																							balance+=(2*bet);
																							winloss='W';
																							
																							dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																							dataOut.close();
																						}
																					}
																					else
																					{
																						cout<<"Dealer wins\n";
																						++hand;
																						winloss='L';
																						
																						dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																						dataOut.close();
																					}
																				}
																			}
																			else
																			{
																				if(dealerScore>21)
																				{
																					cout<<"Dealer Busted\n";
																					balance+=(2*bet);
																					++hand;
																					winloss='W';
																					
																					dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																					dataOut.close();
																				}
																				else if(dealerScore==21)
																				{
																					cout<<"You and the Dealer have 21\n";
																					++hand;
																					winloss='D';
																					balance+=bet;
																					
																					dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																					dataOut.close();
																				}
																				else
																				{
																					if(playerScore>=dealerScore)
																					{
																						if(playerScore==dealerScore)
																						{
																							cout<<"Push\n";
																							++hand;
																							balance+=bet;
																							winloss='D';
																							
																							dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																							dataOut.close();
																						}
																						else
																						{
																							cout<<"You win!\n";
																							++hand;
																							balance+=(2*bet);
																							winloss='W';
																							
																							dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																							dataOut.close();
																						}
																					}
																					else
																					{
																						cout<<"Dealer wins\n";
																						++hand;
																						winloss='L';
																						
																						dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																						dataOut.close();
																					}
																				}
																			}
																		}
																		else
																		{
																			if(dealerScore>21)
																			{
																				cout<<"Dealer Busted\n";
																				balance+=(2*bet);
																				++hand;
																				winloss='W';
																				
																				dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																				dataOut.close();
																			}
																			else if(dealerScore==21)
																			{
																				cout<<"You and the Dealer have 21\n";
																				++hand;
																				winloss='D';
																				balance+=bet;
																				
																				dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																				dataOut.close();
																			}
																			else
																			{
																				if(playerScore>=dealerScore)
																				{
																					if(playerScore==dealerScore)
																					{
																						cout<<"Push\n";
																						++hand;
																						balance+=bet;
																						winloss='D';
																						
																						dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																						dataOut.close();
																					}
																					else
																					{
																						cout<<"You win!\n";
																						++hand;
																						balance+=(2*bet);
																						winloss='W';
																						
																						dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																						dataOut.close();
																					}
																				}
																				else
																				{
																					cout<<"Dealer wins\n";
																					++hand;
																					winloss='L';
																					
																					dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																					dataOut.close();
																				}
																			}
																		}
																	}
																	else
																	{
																		if(dealerScore>21)
																		{
																			cout<<"Dealer Busted\n";
																			balance+=(2*bet);
																			++hand;
																			winloss='W';
																			
																			dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																			dataOut.close();
																		}
																		else if(dealerScore==21)
																		{
																			cout<<"You and the Dealer have 21\n";
																			++hand;
																			winloss='D';
																			balance+=bet;
																			
																			dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																			dataOut.close();
																		}
																		else
																		{
																			if(playerScore>=dealerScore)
																			{
																				if(playerScore==dealerScore)
																				{
																					cout<<"Push\n";
																					++hand;
																					balance+=bet;
																					winloss='D';
																					
																					dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																					dataOut.close();
																				}
																				else
																				{
																					cout<<"You win!\n";
																					++hand;
																					balance+=(2*bet);
																					winloss='W';
																					
																					dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																					dataOut.close();
																				}
																			}
																			else
																			{
																				cout<<"Dealer wins\n";
																				++hand;
																				winloss='L';
																				
																				dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																				dataOut.close();
																			}
																		}
																	}
																}
																else
																{
																	cout<<"You busted...\n";
																	++hand;
																	winloss='L';
																	
																	dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																	dataOut.close();
																}
																break;
															case 2:
																if(dealerScore<17)
																{
																	dcard3 = (rand()%14+1);
																	switch(dcard3)
																	{
																		case 1: 
																			cardValue=2;
																			card="2";
																			break;
																		case 2:
																			cardValue=3;
																			card="3";
																			break;
																		case 3:
																			cardValue=4;
																			card="4";
																			break;
																		case 4:
																			cardValue=5;
																			card="5";
																			break;
																		case 5:
																			cardValue=6;
																			card="6";
																			break;
																		case 6:
																			cardValue=7;
																			card="7";
																			break;
																		case 7:
																			cardValue=8;
																			card="8";
																			break;
																		case 8:
																			cardValue=9;
																			card="9";
																			break;
																		case 9:
																			cardValue=10;
																			card="10";
																			break;
																		case 10:
																			cardValue=10;
																			card="J";
																			break;
																		case 11:
																			cardValue=10;
																			card="Q";
																			break;
																		case 12:
																			cardValue=10;
																			card="K";
																			break;
																		case 13:
																			if(dealerScore<=10)
																				cardValue=11;
																			else
																				cardValue=1;
																			card="A";
																			break;
																		default: cout<<"Game error";
																	}
																	dealerScore+=cardValue;
																	dealerhand+=" "+card;
																	if(dealerScore<17)
																	{
																		dcard4 = (rand()%14+1);
																		switch(dcard4)
																		{
																			case 1: 
																				cardValue=2;
																				card="2";
																				break;
																			case 2:
																				cardValue=3;
																				card="3";
																				break;
																			case 3:
																				cardValue=4;
																				card="4";
																				break;
																			case 4:
																				cardValue=5;
																				card="5";
																				break;
																			case 5:
																				cardValue=6;
																				card="6";
																				break;
																			case 6:
																				cardValue=7;
																				card="7";
																				break;
																			case 7:
																				cardValue=8;
																				card="8";
																				break;
																			case 8:
																				cardValue=9;
																				card="9";
																				break;
																			case 9:
																				cardValue=10;
																				card="10";
																				break;
																			case 10:
																				cardValue=10;
																				card="J";
																				break;
																			case 11:
																				cardValue=10;
																				card="Q";
																				break;
																			case 12:
																				cardValue=10;
																				card="K";
																				break;
																			case 13:
																				if(dealerScore<=10)
																					cardValue=11;
																				else
																					cardValue=1;
																				card="A";
																				break;
																			default: cout<<"Game error";
																		}
																		dealerScore+=cardValue;
																		dealerhand+=" "+card;
																		if(dealerScore<17)
																		{
																			dcard5 = (rand()%14+1);
																			switch(dcard5)
																			{
																				case 1: 
																					cardValue=2;
																					card="2";
																					break;
																				case 2:
																					cardValue=3;
																					card="3";
																					break;
																				case 3:
																					cardValue=4;
																					card="4";
																					break;
																				case 4:
																					cardValue=5;
																					card="5";
																					break;
																				case 5:
																					cardValue=6;
																					card="6";
																					break;
																				case 6:
																					cardValue=7;
																					card="7";
																					break;
																				case 7:
																					cardValue=8;
																					card="8";
																					break;
																				case 8:
																					cardValue=9;
																					card="9";
																					break;
																				case 9:
																					cardValue=10;
																					card="10";
																					break;
																				case 10:
																					cardValue=10;
																					card="J";
																					break;
																				case 11:
																					cardValue=10;
																					card="Q";
																					break;
																				case 12:
																					cardValue=10;
																					card="K";
																					break;
																				case 13:
																					if(dealerScore<=10)
																						cardValue=11;
																					else
																						cardValue=1;
																					card="A";
																					break;
																				default: cout<<"Game error";
																			}
																			dealerScore+=cardValue;
																			dealerhand+=" "+card;
																			if(dealerScore>21)
																			{
																				cout<<"Dealer Busted\n";
																				balance+=(2*bet);
																				++hand;
																				winloss='W';
																				
																				dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																				dataOut.close();
																			}
																			else if(dealerScore==21)
																			{
																				cout<<"You and the Dealer have 21\n";
																				++hand;
																				winloss='D';
																				balance+=bet;
																				
																				dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																				dataOut.close();
																			}
																			else
																			{
																				if(playerScore>=dealerScore)
																				{
																					if(playerScore==dealerScore)
																					{
																						cout<<"Push\n";
																						++hand;
																						balance+=bet;
																						winloss='D';
																						
																						dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																						dataOut.close();
																					}
																					else
																					{
																						cout<<"You win!\n";
																						++hand;
																						balance+=(2*bet);
																						winloss='W';
																						
																						dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																						dataOut.close();
																					}
																				}
																				else
																				{
																					cout<<"Dealer wins\n";
																					++hand;
																					winloss='L';
																					
																					dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																					dataOut.close();
																				}
																			}
																		}
																		else
																		{
																			if(dealerScore>21)
																			{
																				cout<<"Dealer Busted\n";
																				balance+=(2*bet);
																				++hand;
																				winloss='W';
																				 
																			}
																			else if(dealerScore==21)
																			{
																				cout<<"You and the Dealer have 21\n";
																				++hand;
																				winloss='D';
																				balance+=bet;
																				 
																			}
																			else
																			{
																				if(playerScore>=dealerScore)
																				{
																					if(playerScore==dealerScore)
																					{
																						cout<<"Push\n";
																						++hand;
																						balance+=bet;
																						winloss='D';
																						 
																					}
																					else
																					{
																						cout<<"You win!\n";
																						++hand;
																						balance+=(2*bet);
																						winloss='W';
																						 
																					}
																				}
																				else
																				{
																					cout<<"Dealer wins\n";
																					++hand;
																					winloss='L';
																					 
																				}
																			}
																		}
																	}
																	else
																	{
																		if(dealerScore>21)
																		{
																			cout<<"Dealer Busted\n";
																			balance+=(2*bet);
																			++hand;
																			winloss='W';
																			
																			dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																			dataOut.close();
																		}
																		else if(dealerScore==21)
																		{
																			cout<<"You and the Dealer have 21\n";
																			++hand;
																			winloss='D';
																			balance+=bet;
																			
																			dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																			dataOut.close();
																		}
																		else
																		{
																			if(playerScore>=dealerScore)
																			{
																				if(playerScore==dealerScore)
																				{
																					cout<<"Push\n";
																					++hand;
																					balance+=bet;
																					winloss='D';
																					
																					dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																					dataOut.close();
																				}
																				else
																				{
																					cout<<"You win!\n";
																					++hand;
																					balance+=(2*bet);
																					winloss='W';
																					
																					dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																					dataOut.close();
																				}
																			}
																			else
																			{
																				cout<<"Dealer wins\n";
																				++hand;
																				winloss='L';
																				
																				dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																				dataOut.close();
																			}
																		}
																	}
																}
																else
																{
																	if(dealerScore>21)
																	{
																		cout<<"Dealer Busted\n";
																		balance+=(2*bet);
																		++hand;
																		winloss='W';
																		
																		dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																		dataOut.close();
																	}
																	else if(dealerScore==21)
																	{
																		cout<<"You and the Dealer have 21\n";
																		++hand;
																		winloss='D';
																		balance+=bet;
																		
																		dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																		dataOut.close();
																	}
																	else
																	{
																		if(playerScore>=dealerScore)
																		{
																			if(playerScore==dealerScore)
																			{
																				cout<<"Push\n";
																				++hand;
																				balance+=bet;
																				winloss='D';
																				
																				dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																				dataOut.close();
																			}
																			else
																			{
																				cout<<"You win!\n";
																				++hand;
																				balance+=(2*bet);
																				winloss='W';
																				
																				dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																				dataOut.close();
																			}
																		}
																		else
																		{
																			cout<<"Dealer wins\n";
																			++hand;
																			winloss='L';
																			
																			dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																			dataOut.close();
																		}
																	}
																}
																break;
															default: cout<<"Improper input\n";
														}	
													}while(menu2<1||menu2>2);
												}
												else
												{
													cout<<"You busted...\n";
													++hand;
													winloss='L';
													
													dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
													dataOut.close();
												}
												break;
											case 2:
												if(dealerScore<17)
												{
													dcard3 = (rand()%14+1);
													switch(dcard3)
													{
														case 1: 
															cardValue=2;
															card="2";
															break;
														case 2:
															cardValue=3;
															card="3";
															break;
														case 3:
															cardValue=4;
															card="4";
															break;
														case 4:
															cardValue=5;
															card="5";
															break;
														case 5:
															cardValue=6;
															card="6";
															break;
														case 6:
															cardValue=7;
															card="7";
															break;
														case 7:
															cardValue=8;
															card="8";
															break;
														case 8:
															cardValue=9;
															card="9";
															break;
														case 9:
															cardValue=10;
															card="10";
															break;
														case 10:
															cardValue=10;
															card="J";
															break;
														case 11:
															cardValue=10;
															card="Q";
															break;
														case 12:
															cardValue=10;
															card="K";
															break;
														case 13:
															if(dealerScore<=10)
																cardValue=11;
															else
																cardValue=1;
															card="A";
															break;
														default: cout<<"Game error";
													}
													dealerScore+=cardValue;
													dealerhand+=" "+card;
													if(dealerScore<17)
													{
														dcard4 = (rand()%14+1);
														switch(dcard4)
														{
															case 1: 
																cardValue=2;
																card="2";
																break;
															case 2:
																cardValue=3;
																card="3";
																break;
															case 3:
																cardValue=4;
																card="4";
																break;
															case 4:
																cardValue=5;
																card="5";
																break;
															case 5:
																cardValue=6;
																card="6";
																break;
															case 6:
																cardValue=7;
																card="7";
																break;
															case 7:
																cardValue=8;
																card="8";
																break;
															case 8:
																cardValue=9;
																card="9";
																break;
															case 9:
																cardValue=10;
																card="10";
																break;
															case 10:
																cardValue=10;
																card="J";
																break;
															case 11:
																cardValue=10;
																card="Q";
																break;
															case 12:
																cardValue=10;
																card="K";
																break;
															case 13:
																if(dealerScore<=10)
																	cardValue=11;
																else
																	cardValue=1;
																card="A";
																break;
															default: cout<<"Game error";
														}
														dealerScore+=cardValue;
														dealerhand+=" "+card;
														if(dealerScore<17)
														{
															dcard5 = (rand()%14+1);
															switch(dcard5)
															{
																case 1: 
																	cardValue=2;
																	card="2";
																	break;
																case 2:
																	cardValue=3;
																	card="3";
																	break;
																case 3:
																	cardValue=4;
																	card="4";
																	break;
																case 4:
																	cardValue=5;
																	card="5";
																	break;
																case 5:
																	cardValue=6;
																	card="6";
																	break;
																case 6:
																	cardValue=7;
																	card="7";
																	break;
																case 7:
																	cardValue=8;
																	card="8";
																	break;
																case 8:
																	cardValue=9;
																	card="9";
																	break;
																case 9:
																	cardValue=10;
																	card="10";
																	break;
																case 10:
																	cardValue=10;
																	card="J";
																	break;
																case 11:
																	cardValue=10;
																	card="Q";
																	break;
																case 12:
																	cardValue=10;
																	card="K";
																	break;
																case 13:
																	if(dealerScore<=10)
																		cardValue=11;
																	else
																		cardValue=1;
																	card="A";
																	break;
																default: cout<<"Game error";
															}
															dealerScore+=cardValue;
															dealerhand+=" "+card;
															if(dealerScore>21)
															{
																cout<<"Dealer Busted\n";
																balance+=(2*bet);
																++hand;
																winloss='W';
																
																dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																dataOut.close();
															}
															else if(dealerScore==21)
															{
																cout<<"You and the Dealer have 21\n";
																++hand;
																winloss='D';
																balance+=bet;
																
																dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																dataOut.close();
															}
															else
															{
																if(playerScore>=dealerScore)
																{
																	if(playerScore==dealerScore)
																	{
																		cout<<"Push\n";
																		++hand;
																		balance+=bet;
																		winloss='D';
																		
																		dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																		dataOut.close();
																	}
																	else
																	{
																		cout<<"You win!\n";
																		++hand;
																		balance+=(2*bet);
																		winloss='W';
																		
																		dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																		dataOut.close();
																	}
																}
																else
																{
																	cout<<"Dealer wins\n";
																	++hand;
																	winloss='L';
																	
																	dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																	dataOut.close();
																}
															}
														}
														else
														{
															if(dealerScore>21)
															{
																cout<<"Dealer Busted\n";
																balance+=(2*bet);
																++hand;
																winloss='W';
																
																dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																dataOut.close();
															}
															else if(dealerScore==21)
															{
																cout<<"You and the Dealer have 21\n";
																++hand;
																winloss='D';
																balance+=bet;
																
																dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																dataOut.close();
															}
															else
															{
																if(playerScore>=dealerScore)
																{
																	if(playerScore==dealerScore)
																	{
																		cout<<"Push\n";
																		++hand;
																		balance+=bet;
																		winloss='D';
																		
																		dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																		dataOut.close();
																	}
																	else
																	{
																		cout<<"You win!\n";
																		++hand;
																		balance+=(2*bet);
																		winloss='W';
																		
																		dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																		dataOut.close();
																	}
																}
																else
																{
																	cout<<"Dealer wins\n";
																	++hand;
																	winloss='L';
																	
																	dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																	dataOut.close();
																}
															}
														}
													}
													else
													{
														if(dealerScore>21)
														{
															cout<<"Dealer Busted\n";
															balance+=(2*bet);
															++hand;
															winloss='W';
															
															dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
															dataOut.close();
														}
														else if(dealerScore==21)
														{
															cout<<"You and the Dealer have 21\n";
															++hand;
															winloss='D';
															balance+=bet;
															
															dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
															dataOut.close();
														}
														else
														{
															if(playerScore>=dealerScore)
															{
																if(playerScore==dealerScore)
																{
																	cout<<"Push\n";
																	++hand;
																	balance+=bet;
																	winloss='D';
																	
																	dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																	dataOut.close();
																}
																else
																{
																	cout<<"You win!\n";
																	++hand;
																	balance+=(2*bet);
																	winloss='W';
																	
																	dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																	dataOut.close();
																}
															}
															else
															{
																cout<<"Dealer wins\n";
																++hand;
																winloss='L';
																
																dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																dataOut.close();
															}
														}
													}
												}
												else
												{
													if(dealerScore>21)
													{
														cout<<"Dealer Busted\n";
														balance+=(2*bet);
														++hand;
														winloss='W';
														
														dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
														dataOut.close();
													}
													else if(dealerScore==21)
													{
														cout<<"You and the Dealer have 21\n";
														++hand;
														winloss='D';
														balance+=bet;
														
														dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
														dataOut.close();
													}
													else
													{
														if(playerScore>=dealerScore)
														{
															if(playerScore==dealerScore)
															{
																cout<<"Push\n";
																++hand;
																balance+=bet;
																winloss='D';
																
																dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																dataOut.close();
															}
															else
															{
																cout<<"You win!\n";
																++hand;
																balance+=(2*bet);
																winloss='W';
																
																dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
																dataOut.close();
															}
														}
														else
														{
															cout<<"Dealer wins\n";
															++hand;
															winloss='L';
															
															dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
															dataOut.close();
														}
													}
												}
												break;
											default: cout<<"Improper input\n";
										}	
									}while(menu2<1||menu2>2);
								}
								else
								{
									cout<<"You busted...\n";
									++hand;
									winloss='L';
									
									dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
									dataOut.close();
								}
								break;
							case 2:
								if(dealerScore<17)
								{
									dcard3 = (rand()%14+1);
									switch(dcard3)
									{
										case 1: 
											cardValue=2;
											card="2";
											break;
										case 2:
											cardValue=3;
											card="3";
											break;
										case 3:
											cardValue=4;
											card="4";
											break;
										case 4:
											cardValue=5;
											card="5";
											break;
										case 5:
											cardValue=6;
											card="6";
											break;
										case 6:
											cardValue=7;
											card="7";
											break;
										case 7:
											cardValue=8;
											card="8";
											break;
										case 8:
											cardValue=9;
											card="9";
											break;
										case 9:
											cardValue=10;
											card="10";
											break;
										case 10:
											cardValue=10;
											card="J";
											break;
										case 11:
											cardValue=10;
											card="Q";
											break;
										case 12:
											cardValue=10;
											card="K";
											break;
										case 13:
											if(dealerScore<=10)
												cardValue=11;
											else
												cardValue=1;
											card="A";
											break;
										default: cout<<"Game error";
									}
									dealerScore+=cardValue;
									dealerhand+=" "+card;
									if(dealerScore<17)
									{
										dcard4 = (rand()%14+1);
										switch(dcard4)
										{
											case 1: 
												cardValue=2;
												card="2";
												break;
											case 2:
												cardValue=3;
												card="3";
												break;
											case 3:
												cardValue=4;
												card="4";
												break;
											case 4:
												cardValue=5;
												card="5";
												break;
											case 5:
												cardValue=6;
												card="6";
												break;
											case 6:
												cardValue=7;
												card="7";
												break;
											case 7:
												cardValue=8;
												card="8";
												break;
											case 8:
												cardValue=9;
												card="9";
												break;
											case 9:
												cardValue=10;
												card="10";
												break;
											case 10:
												cardValue=10;
												card="J";
												break;
											case 11:
												cardValue=10;
												card="Q";
												break;
											case 12:
												cardValue=10;
												card="K";
												break;
											case 13:
												if(dealerScore<=10)
													cardValue=11;
												else
													cardValue=1;
												card="A";
												break;
											default: cout<<"Game error";
										}
										dealerScore+=cardValue;
										dealerhand+=" "+card;
										if(dealerScore<17)
										{
											dcard5 = (rand()%14+1);
											switch(dcard5)
											{
												case 1: 
													cardValue=2;
													card="2";
													break;
												case 2:
													cardValue=3;
													card="3";
													break;
												case 3:
													cardValue=4;
													card="4";
													break;
												case 4:
													cardValue=5;
													card="5";
													break;
												case 5:
													cardValue=6;
													card="6";
													break;
												case 6:
													cardValue=7;
													card="7";
													break;
												case 7:
													cardValue=8;
													card="8";
													break;
												case 8:
													cardValue=9;
													card="9";
													break;
												case 9:
													cardValue=10;
													card="10";
													break;
												case 10:
													cardValue=10;
													card="J";
													break;
												case 11:
													cardValue=10;
													card="Q";
													break;
												case 12:
													cardValue=10;
													card="K";
													break;
												case 13:
													if(dealerScore<=10)
														cardValue=11;
													else
														cardValue=1;
													card="A";
													break;
												default: cout<<"Game error";
											}
											dealerScore+=cardValue;
											dealerhand+=" "+card;
											if(dealerScore>21)
											{
												cout<<"Dealer Busted\n";
												balance+=(2*bet);
												++hand;
												winloss='W';
												
												dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
												dataOut.close();
											}
											else if(dealerScore==21)
											{
												cout<<"You and the Dealer have 21\n";
												++hand;
												winloss='D';
												balance+=bet;
												
												dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
												dataOut.close();
											}
											else
											{
												if(playerScore>=dealerScore)
												{
													if(playerScore==dealerScore)
													{
														cout<<"Push\n";
														++hand;
														balance+=bet;
														winloss='D';
														
														dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
														dataOut.close();
													}
													else
													{
														cout<<"You win!\n";
														++hand;
														balance+=(2*bet);
														winloss='W';
														
														dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
														dataOut.close();
													}
												}
												else
												{
													cout<<"Dealer wins\n";
													++hand;
													winloss='L';
													
													dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
													dataOut.close();
												}
											}
										}
										else
										{
											if(dealerScore>21)
											{
												cout<<"Dealer Busted\n";
												balance+=(2*bet);
												++hand;
												winloss='W';
												
												dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
												dataOut.close();
											}
											else if(dealerScore==21)
											{
												cout<<"You and the Dealer have 21\n";
												++hand;
												winloss='D';
												balance+=bet;
												
												dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
												dataOut.close();
											}
											else
											{
												if(playerScore>=dealerScore)
												{
													if(playerScore==dealerScore)
													{
														cout<<"Push\n";
														++hand;
														balance+=bet;
														winloss='D';
														
														dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
														dataOut.close();
													}
													else
													{
														cout<<"You win!\n";
														++hand;
														balance+=(2*bet);
														winloss='W';
														
														dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
														dataOut.close();
													}
												}
												else
												{
													cout<<"Dealer wins\n";
													++hand;
													winloss='L';
													
													dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
													dataOut.close();
												}
											}
										}
									}
									else
									{
										if(dealerScore>21)
										{
											cout<<"Dealer Busted\n";
											balance+=(2*bet);
											++hand;
											winloss='W';
											
											dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
											dataOut.close();
										}
										else if(dealerScore==21)
										{
											cout<<"You and the Dealer have 21\n";
											++hand;
											winloss='D';
											balance+=bet;
											
											dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
											dataOut.close();
										}
										else
										{
											if(playerScore>=dealerScore)
											{
												if(playerScore==dealerScore)
												{
													cout<<"Push\n";
													++hand;
													balance+=bet;
													winloss='D';
													
													dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
													dataOut.close();
												}
												else
												{
													cout<<"You win!\n";
													++hand;
													balance+=(2*bet);
													winloss='W';
													
													dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
													dataOut.close();
												}
											}
											else
											{
												cout<<"Dealer wins\n";
												++hand;
												winloss='L';
												
												dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
												dataOut.close();
											}
										}
									}
								}
								else
								{
									if(dealerScore>21)
									{
										cout<<"Dealer Busted\n";
										balance+=(2*bet);
										++hand;
										winloss='W';
										
										dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
										dataOut.close();
									}
									else if(dealerScore==21)
									{
										cout<<"You and the Dealer have 21\n";
										++hand;
										winloss='D';
										balance+=bet;
										
										dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
										dataOut.close();
									}
									else
									{
										if(playerScore>=dealerScore)
										{
											if(playerScore==dealerScore)
											{
												cout<<"Push\n";
												++hand;
												balance+=bet;
												winloss='D';
												
												dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
												dataOut.close();
												
											}
											else
											{
												cout<<"You win!\n";
												++hand;
												balance+=(2*bet);
												winloss='W';
												
												dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
												dataOut.close();
												
											}
										}
										else
										{
											cout<<"Dealer wins\n";
											++hand;
											winloss='L';
											
											dataOut<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
											dataOut.close();
										}
									}
								}
								break;
							default: cout<<"Improper input\n";
						}	
					}while(menu2<1||menu2>2);
				}
				cout<<"hand"<<setw(15)<<"Players Cards"<<setw(15)<<"Bet"<<setw(15)<<"Dealer"<<setw(15)<<"W/L"<<setw(15)<<"Balance\n";
				cout<<hand<<setw(6)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(15)<<bet<<setw(15)<<dealerhand<<setw(14)<<winloss<<setw(15)<<balance<<endl;
				dataOut.close();
				break;
			case 2:
				dataIn.open("GivhanHistory.txt");
				if(dataIn) //history here
				{
					cout<<"hand"<<setw(15)<<"Players Cards"<<setw(15)<<"Bet"<<setw(15)<<"Dealer"<<setw(15)<<"W/L"<<setw(15)<<"Balance\n";
					while(dataIn>>hand>>playerhand>>bet>>dealerhand>>winloss>>balance)
					{
						dataIn>>hand>>playerhand>>bet>>dealerhand>>winloss>>balance;
						cout<<hand<<setw(7)<<pcard1<<setw(3)<<pcard2<<setw(3)<<pcard3<<setw(3)<<pcard4<<setw(3)<<pcard5<<setw(5)<<bet<<setw(10)<<dealerhand<<setw(10)<<winloss<<setw(15)<<balance<<endl;
					}
				}
				else
					cout<<"No game history found\n";
				dataIn.close();
				break;
			case 3:
				cout<<"Thanks for playing\n"; //quit game
				break;
			default:
				cout<<"invalid entry\n";
				cout<<"Please enter 1, 2, or 3 to make your selection.\n";
		}
	}while(menu!=3);
	
	return 0;
}
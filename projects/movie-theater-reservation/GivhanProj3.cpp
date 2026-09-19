//Jacob Givhan
//j_givhan4@hotmail.com

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int MAXROWS=7;
const int MAXSEATS=8;
typedef char MovieTheater[MAXROWS][MAXSEATS];
ofstream dataOut("GivhanProj3.txt");
ofstream salesOut("SalesReport.txt");
ofstream profitsOut("ProfitsReport.txt");
ifstream salesIn("SalesReport.txt");
ifstream profitsIn("ProfitsReport.txt");
void display();
int select(string&, string&);
void buyTickets(MovieTheater, string, string);
void seating(MovieTheater);
void fileOut(MovieTheater);
void seatSelector(MovieTheater, int&);
void admin(int&);
void quit();
void boxOffice(float, int, int, int, int, int);
void getProfits();
void getSales();
void printSales();
void printProfits();
int seatsAvailable(MovieTheater, int);
int seatsRow(MovieTheater, int, int);
void seatBlocker(MovieTheater);
const string MOVIE1="Free Birds";
const string MOVIE2="Bethooven";
const string MOVIE1TIME1="3:30pm";
const string MOVIE1TIME2="6:00pm";
const string MOVIE2TIME1="5:30pm";
const string MOVIE2TIME2="7:30pm";
const float ADULT_MATINEE=6.00;
const float CHILD_MATINEE=4.00;
const float ADULT_EVENING=8.00;
const float CHILD_EVENING=6.00;


int main()
{
	string theater, showing;
	int hold;
	char placeholder='*';
	MovieTheater movie1time1;
	MovieTheater movie1time2;
	MovieTheater movie2time1;
	MovieTheater movie2time2;
	
	for (int row=0;row<MAXROWS;row++)
	{
		for (int col=0;col<MAXSEATS;col++)
		{
			movie1time1[row][col]=placeholder;
			movie1time2[row][col]=placeholder;
			movie2time1[row][col]=placeholder;
			movie2time2[row][col]=placeholder;
		}
	}
	
	do
	{
		display();
		hold=select(theater, showing);
		if (hold==-99)
			do
			{
				admin(hold);
			}while(hold!=-99&&hold!=-1);
		else
		{
			if (theater==MOVIE1)
			{
				if (showing==MOVIE1TIME1)
				{
					buyTickets(movie1time1,theater,showing);
				}
				else
				{
					buyTickets(movie1time2,theater,showing);
				}
			}
			else
			{
				if (showing==MOVIE2TIME1)
				{
					buyTickets(movie2time1,theater,showing);
				}
				else
				{
					buyTickets(movie2time2,theater,showing);
				}
			}
		}
	}while(hold!=-1);
	
	return 0;
}

void display()
{
	cout<<endl;
	cout<<fixed<<showpoint<<setprecision(2);
	cout<<MOVIE1<<setw(10)<<MOVIE1TIME1<<setw(10)<<MOVIE1TIME2<<endl;
	cout<<MOVIE2<<setw(11)<<MOVIE2TIME1<<setw(10)<<MOVIE2TIME2<<endl;
	cout<<endl;
	cout<<"Adult Tickets are: $"<<ADULT_MATINEE<<" (matinee before 6:00pm)"<<setw(5)<<"$"<<ADULT_EVENING<<" (evening)\n";
	cout<<"Child Tickets are: $"<<CHILD_MATINEE<<" (matinee before 6:00pm)"<<setw(5)<<"$"<<CHILD_EVENING<<" (evening)\n";
	cout<<endl;
	dataOut<<endl;
	dataOut<<fixed<<showpoint<<setprecision(2);
	dataOut<<MOVIE1<<setw(10)<<MOVIE1TIME1<<setw(10)<<MOVIE1TIME2<<endl;
	dataOut<<MOVIE2<<setw(11)<<MOVIE2TIME1<<setw(10)<<MOVIE2TIME2<<endl;
	dataOut<<endl;
	dataOut<<"Adult Tickets are: $"<<ADULT_MATINEE<<" (matinee before 6:00pm)"<<setw(5)<<"$"<<ADULT_EVENING<<" (evening)\n";
	dataOut<<"Child Tickets are: $"<<CHILD_MATINEE<<" (matinee before 6:00pm)"<<setw(5)<<"$"<<CHILD_EVENING<<" (evening)\n";
	dataOut<<endl;
}

int select(string &movie, string &t)
{
	int selection1, selection2;
	do
	{
		cout<<"For "<<MOVIE1<<" enter 1\n"<<"For "<<MOVIE2<<" enter 2\n";
		cin>>selection1;
		dataOut<<"For "<<MOVIE1<<" enter 1\n"<<"For "<<MOVIE2<<" enter 2\n";
		dataOut<<selection1<<endl;
		switch (selection1)
		{
			case 1:
				movie=MOVIE1;
				do
				{
					cout<<"For "<<MOVIE1TIME1<<" enter 1\n"<<"For "<<MOVIE1TIME2<<" enter 2\n";
					cin>>selection2;
					dataOut<<"For "<<MOVIE1TIME1<<" enter 1\n"<<"For "<<MOVIE1TIME2<<" enter 2\n";
					dataOut<<selection2<<endl;
					switch (selection2)
					{
						case 1:
							t=MOVIE1TIME1;
							break;
						case 2:
							t=MOVIE1TIME2;
							break;
						default:
							cout<<"Try again\n";
					}
				}while(selection2!=1&&selection2!=2);
				break;
			case 2:
				movie=MOVIE2;
				do
				{
					cout<<"For "<<MOVIE2TIME1<<" enter 1\n"<<"For "<<MOVIE2TIME2<<" enter 2\n";
					cin>>selection2;
					dataOut<<"For "<<MOVIE2TIME1<<" enter 1\n"<<"For "<<MOVIE2TIME2<<" enter 2\n";
					dataOut<<selection2<<endl;
					switch (selection2)
					{
						case 1:
							t=MOVIE2TIME1;
							break;
						case 2:
							t=MOVIE2TIME2;
							break;
						default:
							cout<<"Try again\n";
							dataOut<<"Try again\n";
					}
				}while(selection2!=1&&selection2!=2);
				break;
			default:
				cout<<"Try again\n";
				dataOut<<"Try again\n";
		}
	}while(selection1!=1&&selection1!=2&&selection1!=-99);
	return selection1;
}

void buyTickets(MovieTheater theater, string movie, string showtime)
{
	int adults=0, children=0, tickets, available, row, seat, seatsInRow, adultMatinee=0, adultEvening=0, childEvening=0, childMatinee=0;
	float adultCost, childCost, total;
	do
	{
		cout<<"How many adult tickets do you want?\n";
		cin>>adults;
		cout<<"How many child tickets do you want?\n";
		cin>>children;
		dataOut<<"How many adult tickets do you want?\n";
		dataOut<<adults<<endl;
		dataOut<<"How many child tickets do you want?\n";
		dataOut<<children<<endl;
		tickets=adults+children;
	}while(tickets<0||adults<0||children<0);
	if (movie=="Free Birds")
	{
		if (showtime=="3:30pm")
		{
			adultCost=adults*ADULT_MATINEE;
			childCost=children*CHILD_MATINEE;
			childMatinee=children;
			adultMatinee=adults;
		}
		else
		{
			adultCost=adults*ADULT_EVENING;
			childCost=children*CHILD_EVENING;
			childEvening=children;
			adultEvening=adults;
		}
	}
	else
	{
		if (showtime=="5:30pm")
		{
			adultCost=adults*ADULT_MATINEE;
			childCost=children*CHILD_MATINEE;
			childMatinee=children;
			adultMatinee=adults;
		}
		else
		{
			adultCost=adults*ADULT_EVENING;
			childCost=children*CHILD_EVENING;
			childEvening=children;
			adultEvening=adults;
		}
	}
	total=adultCost+childCost;
	boxOffice(total, tickets, adultMatinee, adultEvening, childEvening, childMatinee);
	cout<<"Select your seats\n";
	dataOut<<"Select your seats\n";
	available=seatsAvailable(theater, tickets);
	
	if (available>=tickets)
	{
		cout<<"There are "<<available<<" seats available\n"<<endl;
		dataOut<<"There are "<<available<<" seats available\n"<<endl;
		seating(theater);
		seatSelector(theater, tickets);
		dataOut<<fixed<<showpoint<<setprecision(2);
		cout<<"Your cost for "<<movie<<" at "<<showtime<<" is:"<<endl;
		if (adults>0)
			cout<<adults<<" adults for a total of $"<<adultCost<<endl;
		if (children>0)
			cout<<children<<" children for a total of $"<<childCost<<endl;
		cout<<"Total:"<<setw(10)<<"$"<<total<<endl;
		seating(theater);
		dataOut<<"Your cost for "<<movie<<" at "<<showtime<<" is:"<<endl;
		if (adults>0)
			dataOut<<adults<<" adults for a total of $"<<adultCost<<endl;
		if (children>0)
			dataOut<<children<<" children for a total of $"<<childCost<<endl;
		dataOut<<"Total:"<<setw(10)<<"$"<<total<<endl;
		fileOut(theater);
	}
	else
	{
		cout<<"There are not enough tickets available\n";
		dataOut<<"There are not enough tickets available\n";
	}
	
}

int seatsAvailable(MovieTheater theater, int tickets)
{
	int seats=0;
	
	for (int row=0;row<MAXROWS;row++)
	{
		for (int col=0;col<MAXSEATS;col++)
		{
			if (theater[row][col]=='*')
				seats++;
		}
	}
	
	return seats;
}

void seating(MovieTheater theater)
{
	cout<<"Seats|"<<setw(10)<<"Seat 1 |"<<setw(10)<<"Seat 2 |"<<setw(10)<<"Seat 3 |"<<setw(10)<<"Seat 4 |"<<setw(10)<<"Seat 5 |"<<setw(10)<<"Seat 6 |"<<setw(10)<<"Seat 7 |"<<setw(10)<<"Seat 8 |"<<endl;
	cout<<"-----+---------+---------+---------+---------+---------+---------+---------+---------+"<<endl;
	for (int row=0;row<MAXROWS;row++)
	{
		cout<<"Row "<<row+1<<"|";
		for (int col=0;col<MAXSEATS;col++)
		{
			cout<<setw(5)<<theater[row][col]<<setw(5)<<"|";
		}
		cout<<endl;
		cout<<"-----+---------+---------+---------+---------+---------+---------+---------+---------+";
		cout<<endl;
	}
}	
void fileOut(MovieTheater theater)
{
	dataOut<<"Seats|"<<setw(10)<<"Seat 1 |"<<setw(10)<<"Seat 2 |"<<setw(10)<<"Seat 3 |"<<setw(10)<<"Seat 4 |"<<setw(10)<<"Seat 5 |"<<setw(10)<<"Seat 6 |"<<setw(10)<<"Seat 7 |"<<setw(10)<<"Seat 8 |"<<endl;
	dataOut<<"-----+---------+---------+---------+---------+---------+---------+---------+---------+"<<endl;
	for (int row=0;row<MAXROWS;row++)
	{
		dataOut<<"Row "<<row+1<<"|";
		for (int col=0;col<MAXSEATS;col++)
		{
			dataOut<<setw(5)<<theater[row][col]<<setw(5)<<"|";
		}
		dataOut<<endl;
		dataOut<<"-----+---------+---------+---------+---------+---------+---------+---------+---------+";
		dataOut<<endl;
	}
}

int seatsRow(MovieTheater theater, int row, int tickets)
{
	int seats=0;
	
	for (int col=0;col<MAXSEATS;col++)
	{
		if (theater[row][col]=='*')
				seats++;
	}
	
	return seats;
}

void seatBlocker(MovieTheater theater)
{
	for (int row=0;row<MAXROWS;row++)
	{
		for (int col=0;col<MAXSEATS;col++)
		{
			if (theater[row][col]=='#')
			{
				if (theater[row][col]==theater[row][0]&&theater[row][col]==theater[0][col])
				{
					if (theater[row][col+1]!='#')
					{
						theater[row][col+1]='X';
					}
					if (theater[row+1][col]!='#')
					{
						theater[row+1][col]='X';
					}
				}
				else if(theater[row][col]==theater[row][7]&&theater[row][col]==theater[0][col])
				{
					if (theater[row][col-1]!='#')
					{
						theater[row][col-1]='X';
					}
					if (theater[row+1][col]!='#')
					{
						theater[row+1][col]='X';
					}
				}
				else if(theater[row][col]==theater[row][0]&&theater[row][col]==theater[6][col])
				{
					if (theater[row][col+1]!='#')
					{
						theater[row][col+1]='X';
					}
					if (theater[row-1][col]!='#')
					{
						theater[row-1][col]='X';
					}
				}
				else if(theater[row][col]==theater[row][7]&&theater[row][col]==theater[6][col])
				{
					if (theater[row][col-1]!='#')
					{
						theater[row][col-1]='X';
					}
					if (theater[row-1][col]!='#')
					{
						theater[row-1][col]='X';
					}
				}
				else if(theater[row][col]==theater[row][7])
				{
					if (theater[row][col-1]!='#')
					{
						theater[row][col-1]='X';
					}
					if (theater[row-1][col]!='#')
					{
						theater[row-1][col]='X';
					}
					if (theater[row+1][col]!='#')
					{
						theater[row+1][col]='X';
					}
				}
				else if(theater[row][col]==theater[row][0])
				{
					if (theater[row][col+1]!='#')
					{
						theater[row][col+1]='X';
					}
					if (theater[row-1][col]!='#')
					{
						theater[row-1][col]='X';
					}
					if (theater[row+1][col]!='#')
					{
						theater[row+1][col]='X';
					}
				}
				else if (theater[row][col]==theater[0][col])
				{
					if (theater[row][col-1]!='#')
					{
						theater[row][col-1]='X';
					}
					if (theater[row][col+1]!='#')
					{
						theater[row][col+1]='X';
					}
					if (theater[row+1][col]!='#')
					{
						theater[row+1][col]='X';
					}
				}
				else if(theater[row][col]==theater[6][col])
				{
					if (theater[row][col-1]!='#')
					{
						theater[row][col-1]='X';
					}
					if (theater[row][col+1]!='#')
					{
						theater[row][col+1]='X';
					}
					if (theater[row-1][col]!='#')
					{
						theater[row-1][col]='X';
					}
				}
				else
				{
					if (theater[row][col-1]!='#')
					{
						theater[row][col-1]='X';
					}
					if (theater[row][col+1]!='#')
					{
						theater[row][col+1]='X';
					}
					if (theater[row-1][col]!='#')
					{
						theater[row-1][col]='X';
					}
					if (theater[row+1][col]!='#')
					{
						theater[row+1][col]='X';
					}
				}
			}
		}
	}
}

void seatSelector(MovieTheater theater, int &ticks)
{
	int row, seat, seatsInRow, seats;
	do
	{
		do
		{
			cout<<"Enter row number\n";
			dataOut<<"Enter row number\n";
			cin>>row;
			dataOut<<row<<endl;
			row--;
			seatsInRow=seatsRow(theater,row , ticks);
			if (seatsInRow==0)
			{
				cout<<"This row is full, please select another one\n";
				dataOut<<"This row is full, please select another one\n";
			}
		}while(seatsInRow==0||row<0||row>6);
		if (ticks>seatsInRow)
		{
			cout<<"There are only "<<seatsInRow<<" left in the selected row\n";
			dataOut<<"There are only "<<seatsInRow<<" left in the selected row\n";
		}
		for (seats=0;seats<seatsInRow&&seats<ticks;seats++)
		{
			do
			{
				do
				{
					cout<<"Enter seat number\n";
					dataOut<<"Enter seat number\n";
					cin>>seat;
					dataOut<<seat<<endl;
					--seat;
				}while(seat<0||seat>7);
				if (theater[row][seat]=='X'||theater[row][seat]=='#')
				{
					cout<<"Seat unavailable\n";
					dataOut<<"Seat unavailable\n";
				}
			}while(theater[row][seat]=='X'||theater[row][seat]=='#');
			theater[row][seat]='#';
			seating(theater);
		}
		ticks=ticks-seats;
	}while(ticks>0);
	seatBlocker(theater);
	
}

void boxOffice(float total, int tickets, int adultMatinee, int adultEvening, int childEvening, int childMatinee)
{
	float amp, aep, cmp, cep, totalProfits;
	
	amp=adultMatinee*ADULT_MATINEE;
	aep=adultEvening*ADULT_EVENING;
	cmp=childMatinee*CHILD_MATINEE;
	cep=childEvening*CHILD_EVENING;
	totalProfits=amp+aep+cmp+cep;
	profitsOut<<fixed<<showpoint<<setprecision(2)<<amp<<setw(20)<<aep<<setw(20)<<cmp<<setw(20)<<cep<<setw(20)<<totalProfits<<endl;
	salesOut<<fixed<<adultMatinee<<setw(20)<<adultEvening<<setw(20)<<childMatinee<<setw(20)<<childEvening<<setw(20)<<tickets<<endl;
}

void admin(int &h)
{
	int menu2;
	do
	{
		cout<<"To show current sales enter 1\n";
		cout<<"To show current profits enter 2\n";
		cout<<"To turn off the system enter 3\n";
		cout<<"To return to the main screen enter -99\n";
		dataOut<<"To show current sales enter 1\n";
		dataOut<<"To show current profits enter 2\n";
		dataOut<<"To turn off the system enter 3\n";
		dataOut<<"To return to the main screen enter -99\n";
		cin>>menu2;
		dataOut<<menu2<<endl;
		if (menu2==1)
		{
			printSales();
			h=0;
		}
		else if (menu2==2)
		{
			printProfits();
			h=0;
		}
		else if (menu2==-99)
			h=-99;
		else if (menu2==3)
		{
			quit();
			h=-1;
		}
		else
		{
			cout<<"Try again\n";
			dataOut<<"Try again\n";
		}
	}while(menu2!=1&&menu2!=2&&menu2!=3&&menu2!=-99);
}


void printSales()
{
	int totalAdultMatinee, totalAdultEvening, totalChildMatinee, totalChildEvening, totalSales;
	int menu;
	int tam=0,tae=0,tcm=0,tce=0,ts=0;
	cout<<"Enter 1 for sales by type\n";
	cout<<"Enter 2 for total sales\n";
	cout<<"Enter 3 to return to admin menu\n";
	dataOut<<"Enter 1 for sales by type\n";
	dataOut<<"Enter 2 for total sales\n";
	dataOut<<"Enter 3 to return to admin menu\n";
	salesOut.close();
	if (salesIn)
	{
		while(salesIn>>totalAdultMatinee>>totalAdultEvening>>totalChildMatinee>>totalChildEvening>>totalSales)
		{
			tam+=totalAdultMatinee;
			tae+=totalAdultEvening;
			tcm+=totalChildMatinee;
			tce+=totalChildEvening;
			ts+=totalSales;
		}
	}
	else
	{
		cout<<"No file found\n";
		dataOut<<"No file found\n";
	}
	
	do
	{
		cin>>menu;
		dataOut<<menu<<endl;
		switch(menu)
		{
			case 1:
				cout<<setw(15)<<"Adult Matinee"<<setw(15)<<"Adult Evening"<<setw(15)<<"Child Matinee"<<setw(15)<<"Child Evening"<<endl;
				cout<<fixed<<setw(3)<<tam<<setw(15)<<tae<<setw(15)<<tcm<<setw(15)<<tce<<endl;
				dataOut<<setw(15)<<"Adult Matinee"<<setw(15)<<"Adult Evening"<<setw(15)<<"Child Matinee"<<setw(15)<<"Child Evening"<<endl;
				dataOut<<fixed<<setw(3)<<tam<<setw(15)<<tae<<setw(15)<<tcm<<setw(15)<<tce<<endl;
				break;
			case 2:
				cout<<fixed<<"Total Sales"<<setw(10)<<ts<<endl;
				dataOut<<fixed<<"Total Sales"<<setw(10)<<ts<<endl;
				break;
			case 3:
				break;
			default:
				cout<<"Invalid Entry\n";
				dataOut<<"Invalid Entry\n";
		}
	}while(menu!=3);
}

void printProfits()
{
	float amp, aep, cmp, cep, totalProfits;
	int menu;
	float tAmp=0,tAep=0,tCmp=0,tCep=0,tp=0;
	cout<<"Enter 1 for profits by type\n";
	cout<<"Enter 2 for total profits\n";
	cout<<"Enter 3 to return to admin menu\n";
	dataOut<<"Enter 1 for profits by type\n";
	dataOut<<"Enter 2 for total profits\n";
	dataOut<<"Enter 3 to return to admin menu\n";
	profitsOut.close();
	if (profitsIn)
	{
		while(profitsIn>>amp>>aep>>cmp>>cep>>totalProfits)
		{
			tAmp+=amp;
			tAep+=aep;
			tCmp+=cmp;
			tCep+=cep;
			tp+=totalProfits;
		}
	}
	else
	{
		cout<<"No file found\n";
		dataOut<<"No file found\n";
	}
	
	do
	{
		cin>>menu;
		dataOut<<menu<<endl;
		switch(menu)
		{
			case 1:
				cout<<setw(15)<<"Adult Matinee"<<setw(15)<<"Adult Evening"<<setw(15)<<"Child Matinee"<<setw(15)<<"Child Evening"<<endl;
				cout<<fixed<<showpoint<<setprecision(2)<<setw(3)<<"$"<<tAmp<<setw(11)<<"$"<<tAep<<setw(11)<<"$"<<tCmp<<setw(11)<<"$"<<tCep<<endl;
				dataOut<<setw(15)<<"Adult Matinee"<<setw(15)<<"Adult Evening"<<setw(15)<<"Child Matinee"<<setw(15)<<"Child Evening"<<endl;
				dataOut<<fixed<<showpoint<<setprecision(2)<<setw(3)<<"$"<<tAmp<<setw(11)<<"$"<<tAep<<setw(11)<<"$"<<tCmp<<setw(11)<<"$"<<tCep<<endl;
				break;
			case 2:
				cout<<fixed<<showpoint<<setprecision(2)<<"Total profit"<<setw(10)<<"$"<<tp<<endl;
				dataOut<<"Total profit"<<setw(10)<<"$"<<tp<<endl;
				break;
			case 3:
				break;
			default:
			cout<<"Invalid Entry\n";
			dataOut<<"Invalid Entry\n";
		}
	}while(menu!=3);
}

void quit()
{
	cout<<"Logging Off...";
	dataOut<<"Logging Off...";
	dataOut.close();
}
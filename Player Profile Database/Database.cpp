#include "pch.h"
#include "Database.h"
#include <iostream>
#include <fstream>
#include "Database.h"
#include <string>
#include <Windows.h>

using namespace std;

Database::Database()
{

	//Add a few players off the bat
	Player bruno("Bruno", 587);
	Player fugo("Fugo", 465);
	Player abbachio("Abbachio", 451);
	Player narancia("Narancia", 197);
	Player mista("Mista", 444);
	Player giorno("Giorno", 365);
	Player trish("Trish", 541);

	AddPlayer(bruno);
	AddPlayer(fugo);
	AddPlayer(abbachio);
	AddPlayer(narancia)
	AddPlayer(mista);
	AddPlayer(giorno);
	AddPlayer(trish)

}



Database::~Database()
{
}

void Database::getCommand()
{
	//Create the input buffer
	char input[50] = "\0";
	int inputInt = 0;

	cout << "Enter a Command" << endl;
	cout << "Search	";
	cout << "Exit" << endl;


	//Clear the input buffer, ready for player input
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());

	cin >> input;

	//exit the program
	if (strcmp(input, "exit") == 0) {
		gameover = true;
		return;
	}
	//enter player search menu
	else if (strcmp(input, "search") == 0)
	{
		search();
	}
	//if the inputs invalid
	else
	{
		cout << "Invalid input" << endl;
		system("pause");
	}
}

void Database::search()
{

	char input[30] = "\0";
	int inputint = 0;
	int index = 0;


	cout << "Search for a current player or make a new wntry" << endl;

	//Clear the input buffer, ready for player input
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());

	cin >> input;

	//search current players for name
	index = bineSearch(input);


	//If a matching name is found
	if (index != -1) {
		//display the player
		cout << "Name: " << m_players[index].m_name << endl;
		cout << "Score: " << m_players[index].m_score << endl;
		//ask player if they would like to edit player
		cout << "Would you like to alter this Profile Yes/No" << endl;
		cin.clear();
		cin >> input;
		if (strcmp(input, "Yes") == 0)
		{
			//change players name
		    cout << "Please Choose a new Name For this Profile " << endl;
			cout << "New Name:" << endl;
			cin.clear();
			cin >> input;
			m_players[index].setName(input);
			//get a new score for this profile
			cout << "Please Choose a new Score For this Profile";
			cout << "New Score:";
			cin.clear();
			cin >> inputint;
			//set score to score input
			m_players[index].setScore(inputint);
			return;
		}
		//return if no or anything else
		else if (strcmp(input, "No") == 0)
		{
			return;
		}
		else
		{
			system("CLS");
			cout << "Invalid Input" << endl;
		}
	}

	//generate new player if no player was found
	else
	{
		//display new name entered periviously
		cout << "Generating New Profile" << endl;
		cout << "New Name: " << input << endl;
		//std::cin >> input;
		//get new score for this profile
		cout << "Please Choose a new Score For this Profile" << endl;
		cout << "New Score: ";
		cin.clear();
		cin >> inputint;
		//generate new player and add to player list
		Player newplayer(input, inputint);
		AddPlayer(newplayer);
	}
}




//search list for player
int Database::binSearch(char* key)
{

	int max = m_playerCount - 1;
	int min = 0;


	while (max != min)
	{
		//set middle and check
		int middle = (min + max) / 2;
		if (strcmp(m_players[middle].m_name, key) == 0)
		{
			return middle;
		}
		//lower max if lower
		if (strcmp(m_players[middle].m_name, key) > 0)
		{
			max = middle - 1;

		}
		//lift min if higher
		else if (strcmp(m_players[middle].m_name, key) < 0)
		{
			min = middle + 1;
		}
		//set middle again and check again
		middle = (min + max) / 2;
		if (strcmp(m_players[middle].m_name, key) == 0)
		{
			return middle;
		}


	}
	//return that this name doesnt exist on current list
	return -1;
}

void Database::start()
{
	//load previous game state
	load();
	while (!gameover)
	{
		//sort list
		sort();
		//draw list
		draw();
		//get player command
		getCommand();
		//clear 
		system("CLS");
	}
	//save game
	save();

}
//draw player list
void Database::draw()
{
	//draw the list of players
	for (int i = 0; i < m_playerCount; i++)
	{
		//draw name
		cout << "Name: " << m_players[i].m_name << endl;
		//draw score
		cout << "Score: " << m_players[i].m_score << sendl;
	}

}
//add player to the player list
void Database::AddPlayer(Player x)
{
	//temporary array to hold players
	Player* temparr = new Player[m_playerCount + 1];
	//copy players over to temp
	for (int i = 0; i < m_playerCount; i++)
	{

		temparr[i] = m_players[i];
	}
	//set last player in temp to added player
	temparr[m_playerCount] = x;
	//incrament player count
	m_playerCount++;
	//set players to temp
	m_players = temparr;
}
//sort the players alphabetically
void Database::sort()
{
	bool done = false;

	while (!done)
	{
		//set check to true
		done = true;
		//go through player list seeing if any players are out of order and if they are swap them
		for (int i = 0; i < m_playerCount - 1; i++)
		{
			//compare two players
			if (strcmp(m_players[i].m_name, m_players[i + 1].m_name) > 0)
			{
				//swap to players if they need to be swapped
				swap(m_players, i, i + 1);
				//if any swaps occure then set to false and iterate again
				done = false;

			}

		}

	}
}
//swap to players position in the array
void Database::swap(Player* players, int n, int k)

{
	//set the two players to each other
	Player temp;

	//set player n to temp
	temp = players[n];

	//copy player over
	players[n] = players[k];
	//set k to previous n value
	players[k] = temp;

}

void Database::save()
{
	ofstream out;

	out.open("player_database_save.dat", ofstream::out | ofstream::trunc | ofstream::binary);

	if (out.is_open())
	{
		//save amount of players
		out.write((char*)&m_playerCount, sizeof(int));


		//save the amount of players equal to player count
		for (int i = 0; i < m_playerCount; i++)
		{
			m_players[i].save(out);
		}
	}
	else
	{
		cout << "The database could not be saved";
	}
	out.flush();
	out.close();

	//display user message
	cout << "Progress has been saved" << endl;
	system("pause");
	system("CLS");
}

bool Database::load()
{
	ifstream in;
	in.open("player_database_save.dat", ifstream::in | ifstream::binary);

	if (!in.is_open())
	{
		cout << "failure to load";
		system("pause");
		return false;
	}

	//Clear the temporary list
	if (m_tempPlayers != nullptr)
		delete[] m_tempPlayers;

	//Load the players
	in.read((char*)&m_tempPlayerCount, sizeof(int));
	if (in.rdstate() || m_tempPlayerCount < 0)
		return false;
	//Read the players
	m_tempPlayers = new Player[m_tempPlayerCount];
	for (int i = 0; i < m_tempPlayerCount; i++) {

		//if player doesnt load properly then delete all loaded players
		if (m_tempPlayers[i].load(in) == false) {
			delete[] m_tempPlayers;
			m_tempPlayers = nullptr;
			return false;
			cout << "failure to load";
			system("pause");
			system("CLS");
		}

	}
	//set players to temp players
	m_playerCount = m_tempPlayerCount;
	m_players = m_tempPlayers;

	//displays if load was successfuk
	cout << "Load Successful press any key to continue" << endl;
	system("pause");
	system("CLS");
	return true;
}

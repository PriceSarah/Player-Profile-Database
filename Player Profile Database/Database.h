#pragma once
class Database
{
public:

	Database();
	~Database();

	
	void start();
	void draw();

	void AddPlayer(Player x);
	void sort();
	void swap(Player * players, int q, int w);


private:

	Player* m_players;

	void getCommand();
	void search();
	void save();
	bool load();
	bool endProgram = false;
	int m_playerCount = 1;

	int m_tempPlayerCount = 1;
	Player* m_tempPlayers;/.: 

	int binSearch(char* key);

};


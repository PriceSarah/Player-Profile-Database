#include "pch.h"
#include "Database.h"
#include <iostream>
#include <fstream>
#include "Database.h"


Database::Database()
{
}


Database::~Database()
{
}

void Database::save()
{
	std::ofstream out;

	out.open("player_database_save.dat", std::ofstream::out | std::ofstream::trunc | std::ofstream::binary);

	if (out.is_open())
	{

	}
	else
	{
		std::cout << "The database could not be saved";
	}
	out.flush();
	out.close();
}

bool Database::load()
{
	std::ifstream in;
	in.open("player_database_save.dat", std::ifstream::in | std::ifstream::binary);

	if (!in.is_open())
	{
		return false;
	}
}

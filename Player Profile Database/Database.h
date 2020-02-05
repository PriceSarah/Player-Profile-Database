#pragma once
class Database
{
public:
	Database();
	~Database();

	void save();
	bool load();
	void setName();
	void setScore();
};


#pragma once

#include <string>

class SingleRecord
{
public:
	SingleRecord(int points, std::string playerName);

	bool operator<(const  SingleRecord & other)
	{
		return p_points < other.getPoints();
	}

	int  getPoints() const { return p_points; }
	std::string getPlayerName() const { return p_playerName; }

private:
	int p_points;
	std::string p_playerName;
};

#pragma once
#include <string>
#include <vector>

using namespace std;

struct ScoreRecord
{
	string points;
	string name;
};

class ScoreboardParser
{
public:
	void parseScores(const char* stateFile, vector<ScoreRecord> *records);
};
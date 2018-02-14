#pragma once
#include <string>
#include <vector>
#include "SingleRecord.h"

using namespace std;

struct ScoreRecord
{
	string points;
	string name;
};

class ScoreboardParser
{
public:
	void parseScores(const char* stateFile, vector<SingleRecord*> *records);
};
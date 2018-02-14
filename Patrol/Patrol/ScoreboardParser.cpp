#include "ScoreboardParser.h"
#include "tinyxml2.h"

void ScoreboardParser::parseScores(const char * scoresFile, vector<SingleRecord*> *records)
{
	// create a TinyXML document and load the map XML
	tinyxml2::XMLDocument scoresDocument;
	scoresDocument.LoadFile(scoresFile);
	
	// get the root node
	tinyxml2::XMLElement* pRoot = scoresDocument.RootElement();

	// parse all the scores
	for (tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		records->push_back(new SingleRecord(e->IntAttribute("points"), e->Attribute("name")));
	}
}

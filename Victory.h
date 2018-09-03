#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Victory {

private:
	int gameID;
	int vicID;
	string vicName;
	int vicPoints;

public:
	Victory(int gid, int vid, string name, int points)
	{
		gameID = gid;
		vicID = vid;
		vicName = name.substr(1, name.size()-2);
		vicPoints = points;
	}
	
	int getID()
	{
		return vicID;
	}

	int getPoints()
	{
		return vicPoints;
	}

	int getGameID()
	{
		return gameID;
	}

	string getName()
	{
		return vicName;
	}
};



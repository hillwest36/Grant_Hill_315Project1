#include <iostream>
#include <string>
#include <vector>
#include "Victory.h"
using namespace std;

class Player {

private:
	int playerID;
	string playerName;
	vector<Victory> victories;
	vector<int> friends;

public:
	Player(int id, string n)
	{
		playerID = id;
		playerName = n.substr(1, n.size()-2);
	}
	
	int getID()
	{
		return playerID;
	}

	string getName()
	{
		return playerName;
	}

	vector<int> getFriends()
	{
		return friends;
	}

	vector<Victory> playerVictories()
	{
		return victories;
	}
	
	void setVictories(vector<Victory> newVictories)
	{
		victories = newVictories;
	}
	
	void setFriends(vector<int> newFriends)
	{
		friends = newFriends;
	}
};


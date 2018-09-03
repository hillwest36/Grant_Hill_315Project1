// GameLeaderboard.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include <vector>
#include "Victory.h"
#include "Game.h"
#include "Player.h"
using namespace std;

//GIVEN COMMANDS--------------------------------

class GameLeaderboard
{
private:
	vector<Game> Games;
	vector<Player> Players;

public:
	GameLeaderboard() {};
	
	vector<Game> getGames()
	{
		return Games;
	}
	
	vector<Player> getPlayers()
	{
		return Players;
	}

	void AddPlayer(int pID, string pName)
	{
		Player newPlayer(pID, pName);
		Players.push_back(newPlayer);
	};

	void AddGame(int gID, string gName)
	{
		Game newGame(gID, gName);
		Games.push_back(newGame);
	};

	void AddVictory(int gID, int vID, string vName, int vPoints)
	{
		Victory newVictory(gID, vID, vName, vPoints);

		for (int i = 0; i < Games.size(); i++)
		{
			if (gID == Games.at(i).getID())
			{
				vector<Victory> tempVics = Games.at(i).gameVictories();
				tempVics.push_back(newVictory);
				Games.at(i).setVictories(tempVics);
			}
		}
	};

	void Plays(int pID, int gID, string pIGN)
	{
		for(int i = 0; i < Games.size(); i++)
		{
			if (gID == Games.at(i).getID())		//Compares given game ID to the list of games, looking for a match;
			{
				vector<int> intVector = Games.at(i).getIGID();
				intVector.push_back(pID);
				Games.at(i).setIGIDs(intVector);
				
				vector<string> strVector = Games.at(i).getIGN();
				strVector.push_back(pIGN);
				Games.at(i).setIGNs(strVector);
				
				i = Games.size();
			}
		}
	};

	void AddFriends(int pID1, int pID2)
	{
		int numPlayersUpdated = 0;
		for (int i = 0; i < Players.size(); i++)
		{
			if (pID1 == Players.at(i).getID())
			{
				vector<int> friendVector = Players.at(i).getFriends();
				friendVector.push_back(pID2);
				Players.at(i).setFriends(friendVector);
				numPlayersUpdated++;
			}
			else if (pID2 == Players.at(i).getID())
			{
				vector<int> friendVector = Players.at(i).getFriends();
				friendVector.push_back(pID1);
				Players.at(i).setFriends(friendVector);
				numPlayersUpdated++;
			}

			if (numPlayersUpdated == 2)
			{
				return;
			}
		}
	};

	void WinVictory(int pID, int gID, int vID)
	{
		for (int i = 0; i < Players.size(); i++)
		{
			if (pID == Players.at(i).getID())
			{
				for (int j = 0; j < Games.size(); j++)		//Finds the correct Game
				{
					if (gID == Games.at(j).getID())
					{
						for (int k = 0; k < Games.at(j).gameVictories().size(); k++)	//Finds the Victory within that Game
						{
							if (vID == Games.at(j).gameVictories().at(k).getID())
							{
								vector<Victory> vicVector = Players.at(i).playerVictories();
								vicVector.push_back(Games.at(j).gameVictories().at(k));
								Players.at(i).setVictories(vicVector);	//Adds the Victory to the Player's Victories
							}
						}
					}
				}
			}
		}
	};

	void FriendsWhoPlay(int pID, int gID)		
	{
		int gameIndex = -1;
		int playerIndex = -1;

		for (int i = 0; i < Games.size(); i++)		//Find Game index
		{
			if (gID == Games.at(i).getID())
			{
				gameIndex = i;
				i = Games.size();
			}
		}

		for (int i = 0; i < Players.size(); i++)	//Find Player index
		{
			if (pID == Players.at(i).getID())
			{
				playerIndex = i;
				i = Players.size();
			}
		}
		
		cout << "\n" << Players.at(playerIndex).getName() << "'s Friends who play " << Games.at(gameIndex).getName() << endl;
		cout << "-----------------------------------------------------------\n" << endl;

		for (int i = 0; i < Players.at(playerIndex).getFriends().size(); i++)	//Loop through friend IDs
		{
			for (int j = 0; j < Games.at(gameIndex).getIGID().size(); j++)		//Loop through in-game IDs
			{
				//cout << Players.at(playerIndex).getFriends().at(i) << "  " << Games.at(gameIndex).getIGID().at(j) << endl;
				if (Players.at(playerIndex).getFriends().at(i) == Games.at(gameIndex).getIGID().at(j))	//IF friend ID == in-game ID
				{
					cout << Players.at(i+1).getName() << endl;		//Prints name of friend who plays
				}
			}
		}
	};

	void ComparePlayers(int pID1, int pID2, int gID)	
	{
		int gameIndex = -1;
		
		int p1Index = -1;
		string player1Name = "";
		int p1Score = 0;
		
		int p2Index = -1;
		string player2Name = "";
		int p2Score = 0;

		for (int i = 0; i < Games.size(); i++)
		{
			if (gID == Games.at(i).getID())
			{
				gameIndex = i;
			}
		}

		int updated = 0;
		for (int i = 0; i < Players.size(); i++)
		{
			if (pID1 == Players.at(i).getID())
			{
				player1Name = Players.at(i).getName();
				updated++;
				p1Index = i;
			}
			else if (pID2 == Players.at(i).getID())
			{
				player2Name = Players.at(i).getName();
				updated++;
				p2Index = i;
			}

			if (updated == 2)	//Exit when both Players are found
			{
				i = Players.size();
			}
		}

		cout << "\n" << Games.at(gameIndex).getName() << endl;
		cout << "Victories" << "\t" << player1Name << "\t" << player2Name << endl;
		cout << "---------------------------------------" << endl;

		for (int i = 0; i < Games.at(gameIndex).gameVictories().size(); i++)
		{
			int victoryID = Games.at(gameIndex).gameVictories().at(i).getID();
			cout << Games.at(gameIndex).gameVictories().at(i).getName() << "\t";
			
			if(Games.at(gameIndex).gameVictories().at(i).getName().size() < 16)
			{
				cout << "\t";
				if(Games.at(gameIndex).gameVictories().at(i).getName().size() < 8)
				{
					cout << "\t";
				}
			}
			
			for (int j = 0; j < Players.at(p1Index).playerVictories().size(); j++)	//Print whether P1 has Victory
			{
				if (victoryID == Players.at(p1Index).playerVictories().at(j).getID())
				{
					cout << "Yes\t";
					p1Score += Players.at(p1Index).playerVictories().at(j).getPoints();
					j = Players.at(p1Index).playerVictories().size();
				}
				else if (j == (Players.at(p1Index).playerVictories().size() - 1))	//If not found, print No
				{
					cout << "No\t";
				}
			}

			for (int j = 0; j < Players.at(p2Index).playerVictories().size(); j++)	//Print whether P2 has Victory
			{
				if (victoryID == Players.at(p2Index).playerVictories().at(j).getID())
				{
					cout << "Yes\t";
					p2Score += Players.at(p2Index).playerVictories().at(j).getPoints();
					j = Players.at(p2Index).playerVictories().size();
				}
				else if (j == (Players.at(p2Index).playerVictories().size() - 1))	//If not found, print No
				{
					cout << "No\t";
				}
			}
			cout << endl;
		}
		cout << endl;
		cout << "Total Score:\t\t" << p1Score << "\t" << p2Score << endl;
		cout << endl;
	};

	void SummarizePlayer(int pID)		
	{
		//Print Player Name
		int playerIndex = -1;

		for (int i = 0; i < Players.size(); i++)	//Find Player index
		{
			if (pID == Players.at(i).getID())
			{
				playerIndex = i;
				i = Players.size();
			}
		}
		
		cout << "Player: " << Players.at(playerIndex).getName() << endl;

		//Print Total Score
		int totalScore = 0;
		for (int i = 0; i < Players.at(playerIndex).playerVictories().size(); i++)
		{
			totalScore += Players.at(playerIndex).playerVictories().at(i).getPoints();	//Sums all points from Victories
		}
		cout << "Total Gamerscore: " << totalScore << endl;

		//Print Game, Earned Victories out of Total Victories, Points per Game, and IGN
		cout << "\t" << "Game" << "\t\t" << "Victories" << "\t" << "Gamerscore" << "\t" << "IGN" << endl;
		cout << "------------------------------------------------------------------------------" << endl;

		int count = 0;
		for (int i = 0; i < Games.size(); i++)		//For each Game
		{
			for (int j = 0; j < Games.at(i).getIGID().size(); j++)
			{
				int totalVics = Games.at(i).gameVictories().size();
				int earnedVics = 0;
				int gameScore = 0;

				for (int k = 0; k < Players.at(playerIndex).playerVictories().size(); k++)
				{
					if (Players.at(playerIndex).playerVictories().at(k).getGameID() == Games.at(i).getID())	//Compares Victory Game IDs to current Games ID
					{
						earnedVics++;
						gameScore += Players.at(playerIndex).playerVictories().at(k).getPoints(); //Adds Victory Points to Score
					}
				}
				
				string currIGN = "";
				if (pID == Games.at(i).getIGID().at(j))		//If the Player ID is on the Game's in-Game ID list
				{
					count++;
					cout << count << ". " << Games.at(i).getName() << "\t";	//Print game name
					if(Games.at(i).getName().size() < 13) 
					{
						cout << "\t";		//Adds another tab for spacing
					}
					currIGN = Games.at(i).getIGN().at(j);
					
					cout << earnedVics << "/" << totalVics << "\t\t" << gameScore << " pts" <<  "\t\t" << currIGN << endl;

				}
			}
		}

		//Print Friends and Friend Total Gamerscores
		cout << "\t" << "Friend" << "\t\t" << "Gamerscore" << endl;
		cout << "--------------------------------------" << endl;

		for (int i = 0; i < Players.at(playerIndex).getFriends().size(); i++)	//Goes through friends
		{
			int friendID = Players.at(playerIndex).getFriends().at(i);
			int friendIndex = -1;
			for (int j = 0; j < Players.size(); j++)		//Finds friend in Players list
			{
				if (friendID == Players.at(j).getID())
				{
					friendIndex = j;
					j = Players.size();
				}
			}

			int totalScore = 0;
			for (int j = 0; j < Players.at(friendIndex).playerVictories().size(); j++)	//Calculates total Gamerscore for friend
			{
				totalScore += Players.at(friendIndex).playerVictories().at(j).getPoints();
			}

			cout << i + 1 << ".\t" << Players.at(friendIndex).getName() << "\t" << totalScore << "pts" << endl;
		}
	};

	void SummarizeGame(int gID)		
	{
		int gameIndex = -1;
		for (int i = 0; i < Games.size(); i++)
		{
			if (gID == Games.at(i).getID())
			{
				gameIndex = i;
			}
		}

		cout << "\n" << Games.at(gameIndex).getName() << endl;		//Print Game name
		cout << "-------------------------------------" << endl;

		//Print list of Players who play this Game
		cout << "Players:" << endl;
		for (int i = 0; i < Games.at(gameIndex).getIGID().size(); i++)	//Print Players who play the Game
		{
			int currPID = Games.at(gameIndex).getIGID().at(i);
			for (int j = 0; j < Players.size(); j++)
			{
				if (currPID == Players.at(j).getID())	//if current Player ID matches, then print name
				{
					cout << Players.at(j).getName() << endl;
				}
			}
		}

		//Print list of Victories + how many times each has been achieved
		cout << "\n";
		cout << "Victories:" << endl;

		for (int i = 0; i < Games.at(gameIndex).gameVictories().size(); i++)	//Cycles through Victories of Game
		{	
			int victoryID = Games.at(gameIndex).gameVictories().at(i).getID();
			int numTimesAchieved = 0;
			for (int j = 0; j < Players.size(); j++)	//Cycles through Players
			{
				for (int k = 0; k < Players.at(j).playerVictories().size(); k++)	//Cycles through Victories of Player
				{
					if (victoryID == Players.at(j).playerVictories().at(k).getID())	//If Player has Victory, increment numTimesAchieved
					{
						numTimesAchieved++;
						k = Players.at(j).playerVictories().size();
					}
				}
			}
			cout << Games.at(gameIndex).gameVictories().at(i).getName() << ":\t" ;
			if(Games.at(gameIndex).gameVictories().at(i).getName().size() < 15)
			{
				cout << "\t";
				if(Games.at(gameIndex).gameVictories().at(i).getName().size() < 7)
				{
					cout << "\t";
				}
			}
			cout << numTimesAchieved << endl;
		}
	};

	void SummarizeVictory(int gID, int vID)		
	{
		int gameIndex = -1;
		for (int i = 0; i < Games.size(); i++)
		{
			if (gID == Games.at(i).getID())
			{
				gameIndex = i;
				i = Games.size();
			}
		}

		string victoryName = "";
		for (int i = 0; i < Games.at(gameIndex).gameVictories().size(); i++)
		{
			if (vID == Games.at(gameIndex).gameVictories().at(i).getID())
			{
				victoryName = Games.at(gameIndex).gameVictories().at(i).getName();
				i = Games.at(gameIndex).gameVictories().size();
			}
		}

		cout << "\n" << Games.at(gameIndex).getName() << endl;
		cout << victoryName << endl;
		cout << "-----------------------------------\n" << endl;
		int numPlayersAchieved = 0;

		//List players who have achieved victory
		for (int i = 0; i < Players.size(); i++)	//Cycles through Players
		{
			for (int j = 0; j < Players.at(i).playerVictories().size(); j++)	//Cycles through Victories of current Player
			{
				if (vID == Players.at(i).playerVictories().at(j).getID())	//Compares Victory IDs
				{
					cout << Players.at(i).getName() << endl;
					numPlayersAchieved++;
				}
			}
		}

		//Calculate % of players with this victory
		cout << (numPlayersAchieved * 100) / Games.at(gameIndex).getIGID().size()  << "% of players have this Victory" << endl;
	};

	void VictoryRanking()		
	{
		vector<string> rankingsName;
		vector<int> rankingsPoints;

		for (int i = 0; i < Players.size(); i++)		//Cycle through Players
		{
			int totalPlayerScore = 0;
			for (int j = 0; j < Players.at(i).playerVictories().size(); j++)	//Cycle through Player's Victories
			{
				totalPlayerScore += Players.at(i).playerVictories().at(j).getPoints();	//Adds up points for Player
			}

			if (i == 0)	//First Player
			{
				rankingsName.push_back(Players.at(i).getName());
				rankingsPoints.push_back(totalPlayerScore);
			}
			else
			{
				int stopAt = rankingsName.size();	//Needed because size changes with each addition, creating infinite loop
				for (int j = 0; j < rankingsName.size(); j++)	//Cycles through current Rankings
				{
					if (totalPlayerScore > rankingsPoints.at(j))	//Sorts scores greatest to least
					{
						rankingsName.insert(rankingsName.begin() + j, Players.at(i).getName());
						rankingsPoints.insert(rankingsPoints.begin() + j, totalPlayerScore);

						j = rankingsName.size();
					}
					else if(j == (stopAt - 1))
					{	
						rankingsName.push_back(Players.at(i).getName());
						rankingsPoints.push_back(totalPlayerScore);
					}
				}
			}
			
		}

		cout << "\nRankings" << endl;
		cout << "------------------------------------\n" << endl;

		for (int i = 0; i < rankingsName.size(); i++)
		{
			cout << i + 1 << ".\t" << rankingsName.at(i) << "\t" << rankingsPoints.at(i) << endl;
		}
	};

};

//MAIN METHOD-----------------------------------------------------

int main()
{
	GameLeaderboard gl;
	string token;

	cout << "Welcome to the Game Leaderboard" << endl;
	while (cin >> token)
	{
		string arg1 = "";
		string arg2 = "";
		string arg3 = "";
		string arg4 = "";

		if(token.compare("AddPlayer") == 0)
		{
			cin >> arg1 >> arg2;
			while(arg2.at(arg2.size()-1) != '"')
			{
				string nextPartOfName;
				cin >> nextPartOfName;
				arg2 += " ";
				arg2 += nextPartOfName;
			}
			
			gl.AddPlayer(stoi(arg1), arg2);
		}

		else if(token.compare("AddGame") == 0)
		{
			cin >> arg1 >> arg2;
			while(arg2.at(arg2.size()-1) != '"')
			{
				string nextPartOfName;
				cin >> nextPartOfName;
				arg2 += " ";
				arg2 += nextPartOfName;
			}
			gl.AddGame(stoi(arg1), arg2);
		}

		else if(token.compare("AddVictory") == 0)
		{
			cin >> arg1 >> arg2 >> arg3;
			while(arg3.at(arg3.size()-1) != '"')
			{
				string nextPartOfName;
				cin >> nextPartOfName;
				arg3 += " ";
				arg3 += nextPartOfName;
			}
			cin >> arg4;
			gl.AddVictory(stoi(arg1), stoi(arg2), arg3, stoi(arg4));
		}

		else if(token.compare("Plays") == 0)
		{
			cin >> arg1 >> arg2 >> arg3;
			gl.Plays(stoi(arg1), stoi(arg2), arg3);
		}

		else if(token.compare("AddFriends") == 0)
		{
			cin >> arg1 >> arg2;
			gl.AddFriends(stoi(arg1), stoi(arg2));
		}

		else if(token.compare("WinVictory") == 0)
		{
			cin >> arg1 >> arg2 >> arg3;
			gl.WinVictory(stoi(arg1), stoi(arg2), stoi(arg3));
		}

		else if(token.compare("FriendsWhoPlay") == 0)
		{
			cin >> arg1 >> arg2;
			gl.FriendsWhoPlay(stoi(arg1), stoi(arg2));
		}

		else if(token.compare("ComparePlayers") == 0)
		{
			cin >> arg1 >> arg2 >> arg3;
			gl.ComparePlayers(stoi(arg1), stoi(arg2), stoi(arg3));
		}

		else if(token.compare("SummarizePlayer") == 0)
		{
			cin >> arg1;
			gl.SummarizePlayer(stoi(arg1));
		}

		else if(token.compare("SummarizeGame") == 0)
		{
			cin >> arg1;
			gl.SummarizeGame(stoi(arg1));
		}

		else if(token.compare("SummarizeVictory") == 0)
		{
			cin >> arg1 >> arg2;
			gl.SummarizeVictory(stoi(arg1), stoi(arg2));
		}

		else if(token.compare("VictoryRanking") == 0)
		{
			gl.VictoryRanking();
		}

	}

	return 0;
}




#include <iostream>
#include <chrono> 
#include <string>
#include <vector>
#include <array>
#include <chrono> 
#include <random>
#include <unordered_map>
#include <algorithm>

using namespace std;

//program that defines hex board as a class and runs it as a game in main. when program is run, game runs and takes input from each user until the game is over. 

class node
{
public:
	node()
	{
		color = "";
	}
	string color;
	vector<int> neighbors;

};


//blue go west <--> east
//red go north <--> south
class Hex
{
	//make a size by size hex board
public:

	int size;
	vector<node> linearNodes;
	unordered_map<int, string> filledSpots;
	int filledSpotsCounter;

	Hex(int size):size(size),linearNodes(size*size),filledSpotsCounter(0)
	{
		//setting neighbors for each node in the board.
		for(int i = 0; i < size; i++)
		{
			for(int j = 0; j < size; j ++)
			{
				//the first four if statements cover if the node is one of the 4 corners of the board. next 4 ifs cover the 4 edges. last if statement covers all "regular" internal nodes
				if(i == 0 && j == 0) 
				{
					int edge1 = (i*size) + j + 1;
					int edge2 = ((i+1)*size) + j;
					linearNodes[(i*size)+j].neighbors.push_back(edge1);
					linearNodes[(i*size)+j].neighbors.push_back(edge2);
				}
				else if(i == 0 && j == size-1)
				{
					int edge1 = (i*size) + j - 1;
					int edge2 = ((i+1)*size) + j;
					int edge3 = ((i+1)*size) + j - 1;
					linearNodes[(i*size)+j].neighbors.push_back(edge1);
					linearNodes[(i*size)+j].neighbors.push_back(edge2);
					linearNodes[(i*size)+j].neighbors.push_back(edge3);
				}
				else if(i == size - 1 && j == 0)
				{
					int edge1 = ((i-1)*size) + j;
					int edge2 = (i*size) + j + 1;
					int edge3 = ((i-1)*size) + j + 1;
					linearNodes[(i*size)+j].neighbors.push_back(edge1);
					linearNodes[(i*size)+j].neighbors.push_back(edge2);
					linearNodes[(i*size)+j].neighbors.push_back(edge3);					
				}
				else if(i == size - 1 && j == size -1)
				{
					int edge1 = ((i-1)*size) + j;
					int edge2 = (i*size) + j - 1;
					linearNodes[(i*size)+j].neighbors.push_back(edge1);
					linearNodes[(i*size)+j].neighbors.push_back(edge2);					
				}
				else if(i == 0)
				{
					int edge1 = (i*size) + j - 1;
					int edge2 = ((i+1)*size) + j;
					int edge3 = ((i+1)*size) + j - 1;
					int edge4 = (i*size) + j + 1;
					linearNodes[(i*size)+j].neighbors.push_back(edge1);
					linearNodes[(i*size)+j].neighbors.push_back(edge2);
					linearNodes[(i*size)+j].neighbors.push_back(edge3);
					linearNodes[(i*size)+j].neighbors.push_back(edge4);
				}
				else if(j == 0)
				{
					int edge1 = ((i-1)*size) + j;
					int edge2 = (i*size) + j + 1;
					int edge3 = ((i-1)*size) + j + 1;
					int edge4 = ((i+1)*size) + j;
					linearNodes[ ( i*size ) + j ].neighbors.push_back(edge2);
					linearNodes[(i*size)+j].neighbors.push_back(edge1);
					linearNodes[(i*size)+j].neighbors.push_back(edge3);
					linearNodes[(i*size)+j].neighbors.push_back(edge4);				
				}
				else if(i== size-1)
				{
					int edge1 = ((i-1)*size) + j;
					int edge2 = (i*size) + j + 1;
					int edge3 = ((i-1)*size) + j + 1;
					int edge4 = (i*size) + j - 1;
					linearNodes[(i*size)+j].neighbors.push_back(edge1);
					linearNodes[(i*size)+j].neighbors.push_back(edge2);
					linearNodes[(i*size)+j].neighbors.push_back(edge3);
					linearNodes[(i*size)+j].neighbors.push_back(edge4);
				}
				else if (j == size - 1)
				{
					int edge1 = (i*size) + j - 1;
					int edge2 = ((i+1)*size) + j;
					int edge3 = ((i+1)*size) + j - 1;
					int edge4 = ((i-1)*size) + j;
					linearNodes[(i*size)+j].neighbors.push_back(edge1);
					linearNodes[(i*size)+j].neighbors.push_back(edge2);
					linearNodes[(i*size)+j].neighbors.push_back(edge3);
					linearNodes[(i*size)+j].neighbors.push_back(edge4);					
				}
				else //general case for internal nodes
				{
					int edge1 = (i*size) + j - 1;
					int edge2 = ((i+1)*size) + j;
					int edge3 = ((i+1)*size) + j - 1;
					int edge4 = ((i-1)*size) + j;
					int edge5 = ((i-1)*size) + j + 1;
					int edge6 = (i*size) + j + 1;
					linearNodes[(i*size)+j].neighbors.push_back(edge1);
					linearNodes[(i*size)+j].neighbors.push_back(edge2);
					linearNodes[(i*size)+j].neighbors.push_back(edge3);
					linearNodes[(i*size)+j].neighbors.push_back(edge4);	
					linearNodes[(i*size)+j].neighbors.push_back(edge5);
					linearNodes[(i*size)+j].neighbors.push_back(edge6);	
				}

			}
		}

	}

	//is this a valid move
	bool isValid(int x, int y)
	{
		if(x < 0 || y < 0 || x >= size || y >= size)
		{
			return false;
		}
		else if (linearNodes[(x*size) + y].color != "")
		{
			return false;
		}
		else
		{
			return true;
		}

	}


	//recursive function to see if the given color won.
	//algo for blue: on first call, check first column for all blues
	//for each blue, if it has a neighbor in next column over call function again with 
	//spot++, location of that neighbor, and location of current node.
	//repeat process untl you've hit other end of board (finished) or there are no new
	//blue neighbors in the next or same column (not finished). for red, use rows.
	bool isFinished(string color, int spot, int coord, int previous)
	{

		vector<int> findings;
		if(coord == -1)
		{
			for(int i = 0; i < size; i ++)
			{
				if(color == "Blue")
				{
					if(linearNodes[(i*size) + spot].color == "Blue")  //left to right  / right to left
					{
						findings.push_back((i*size) + spot);
					}
				}
				else
				{
					if(linearNodes[(spot*size)+i].color == "Red")  //top to bottom / bottom to top
					{
						findings.push_back((spot*size) + i);
					}					
				}
			}
		}
		else
		{
			findings.push_back(coord);
		}

		if(findings.size() == 0)
		{
			return false;
		}

		if(spot == size -1)
		{
			return true;
		}

		int a, b, value;

		for(int finding : findings)
		{

			for( int neighbor : linearNodes[finding].neighbors )
			{
				a = neighbor/size;
				b = neighbor - (a * size);
				if(color == "Blue")
				{
					value = b;
				}
				else
				{
					value = a;
				}
				if(value == spot + 1 && linearNodes[neighbor].color == color && neighbor != previous )
				{
					 if(isFinished(color, value, neighbor, finding) == true )
					 {
					 	return true;
					 }
				}
				else if(value == spot && linearNodes[neighbor].color == color && neighbor != previous )
				{
					 if(isFinished(color, value, neighbor, finding) == true )
					 {
					 	return true;
					 }
				}
			}
		}

		return false;
	}

	void drawBoard()
	{
		for(int i = 0; i < size; i++ )
		{
			for(int a = 0; a < i; a++)
			{
				cout << " ";
			}
			for(int j = 0; j < size; j++)
			{
				if(linearNodes[(i*size)+j].color == "Blue")
				{
					cout << "B";
				}
				else if(linearNodes[(i*size)+j].color == "Red")
				{
					cout << "R";
				}	
				else
				{
					cout << ".";
				}
				if( j != size - 1)
				{
					cout << " - ";
				}
				else
				{
					cout << endl;
				}
			}
			for(int b = 0; b < i; b++)
			{
				cout << " ";
			}
			if( i != size - 1 )
			{
				for(int j = 0; j < size-1; j++)
				{
					cout << "\\ / ";
				}
				cout << "\\" << endl;

			}
		}
	}

	void addPiece(int x, int y, string color)
	{
		/*
			add piece to board for human move
		*/

		int i = (x*size) + y;
		linearNodes[i].color = color;
		filledSpots[i] = color;
		filledSpotsCounter++;
		// 11x11 maps to    0-121
	}

	void makeAiMove(string color)
	{
		/*for every empty spot on the board:
			fill in that spot with this color
			fill in all nodes automatically 
			add to counter if this color won.
			repeat n times.
			divide counter by n and check if it is the highest win to trial ratio so far
			set board back to normal
		move with highest win to trial ratio is move to make
		*/

		double highestWinRatio = -1.0;
		int highestWinRatioMove = -1;
		double wins = 0.0;
		double currentWinRatio;
		string currentColor;
		for(int i = 0; i < size*size; i++)
		{
			
			wins = 0;
			if (linearNodes[i].color == "")
			{

				for(int r = 0; r < 1000; r++)
				{

					fillColors(color, i);
					//graph is now filled... 

					if (isFinished(color, 0, -1, -1) )
					{
						wins++;
					}
				}

				currentWinRatio = wins/1000.0;
				if(currentWinRatio > highestWinRatio)
				{
					highestWinRatioMove = i;
					highestWinRatio = currentWinRatio;
				}

				//regenerate board to normal with filledSpots info
				for(int z = 0; z < (size*size); z++)
				{
					linearNodes[z].color = filledSpots[z];
				}

			}

			
		}
		linearNodes[highestWinRatioMove].color = color;
		filledSpots[highestWinRatioMove] = color;
		filledSpotsCounter++;
	}

	void fillColors(string color, int potentialMoveSpot)
	{
		string currentColor;
		if(color == "Blue")
		{
			currentColor = "Red";
		}
		else
		{
			currentColor = "Blue";
		}

		unordered_map<int, bool> taken;
		linearNodes[potentialMoveSpot].color = color;
		taken[potentialMoveSpot] = true;

		int end = (size*size)-1;
		unsigned seed1 = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		mt19937 generator(seed1);
		uniform_int_distribution<int> distribution(0, end); // define the range

		int remaining = (size * size) - filledSpotsCounter -1;
		int current;
		while(remaining > 0)
		{
			current = distribution(generator);

			while(filledSpots[current] != "" || taken[current] == true)
			{
				current = distribution(generator);
			}
			linearNodes[current].color = currentColor;
			taken[current] = true;
			if(currentColor == "Blue")
			{
				currentColor = "Red";
			}
			else
			{
				currentColor = "Blue";
			}

			remaining--;
		}

	}


};

int main()
{
	char length[20];
	cout << "Type in the size of one side (recommended: 5 ) for the hex board you would like to play on and then hit enter: ";
	cin.getline(length, 10);
	int size = atoi(length);
	cout << endl;
	cout << "about to make board" << endl;
	Hex hexBoard(size);
	int turn = 0;
	cout << endl;
	string color;
	cout << "Row and Column Coordinate: top left of the board is 0, 0. Bottom right most node is " << size-1 << ", " << size-1 << " in the case of an " << size << "x" << size << " board." << endl;
	cout << "Blue needs to connect in the horizantal direction to win. Red in the vertical direction to win. Blue player goes first and Red player goes second." << endl;

	string playerColor;
	cout << "Please type in which color (Blue or Red - make sure to capitalize) you would like to play as and then hit enter: ";
	getline(cin, playerColor);


	while(turn < (size*size) )
	{

		hexBoard.drawBoard();

		if(turn %2 == 0)
		{
			color = "Blue";
		}
		else
		{
			color = "Red";
		}
		
		if(playerColor == color)
		{
			string coord;
			cout << color << " player, enter the row and column coordinate of the node you want to fill with one comma in between the numbers. no spaces. : ";
			getline(cin,coord);
			int pos = coord.find(",");
			cout << endl;
			string first = coord.substr(0,pos); 
			string second = coord.substr(pos+1);
			int x = stoi(first);
			int y = stoi(second);

			
			while(hexBoard.isValid(x, y) == false)
			{
				cout << color << " player, that coordinate was invalid. Please enter in another row and column coordinate: ";
				getline(cin,coord);
				pos = coord.find(",");
				cout << endl;
				first = coord.substr(0,pos); 
				second = coord.substr(pos+1);
				x = stoi(first);
				y = stoi(second);
			}
			

			hexBoard.addPiece(x,y,color);
		}
		else
		{
			cout << "The Artificial Intelligence " << color << " Player will now make a move." << endl;
			hexBoard.makeAiMove(color);
		}


		if(hexBoard.isFinished(color, 0, -1, -1))
		{
			hexBoard.drawBoard();

			cout << color << " player is the winner!" << endl;
			cout << "---------END OF GAME-------" << endl;
			return 0;
		}

		turn++;
	}

	return 0;

}

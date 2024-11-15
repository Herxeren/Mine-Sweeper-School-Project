#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <vector>
#include "gameSlot.h"
struct Position
{
	int row{ 0 };
	int column{ 0 };
	Position& operator++();
	friend bool operator<(const Position& srcL, const int& srcR);
	friend bool operator>(const Position& srcL, const int& srcR);
	friend bool operator>=(const Position& srcL, const int& srcR);
	friend bool operator==(const Position& srcL, const Position& srcR);
	friend bool operator!=(const Position& srcL, const Position& srcR);
	friend Position operator+(const Position& srcL, const Position& srcR);
};

/*Notes:
* -Notice that this is the GameBoard class and all of the declerations are functions dependant on it
* this allows you to call on these functions by calling GameBoard::function() when defining them
* 
* -In the latter half of the public class you have a gameSlot bit of code. To sum it up, this is drawing from
gameSlot to complete the code. The gameSlot is read only while the gameSlot& is returning a reference to gameSlot
making it read and write. 
*/





class GameBoard
{
public:

	enum class Difficulty { easy = 25, medium = 30, hard = 40 };
	enum class Size { small = 10, medium = 15, large = 25 };
	GameBoard();
	void makeMove();
	bool gameOver();
	bool wonGame();

	void revealMines();
	
	gameSlot getSlot(Position slotNum) const;
	gameSlot& modifySlot(Position slotNum);
	

	friend std::ostream& operator<<(std::ostream& o, const GameBoard& src);
	static Size dimension;//static for Position++ (which means it doesn't need a definition)
private:
	int countMines(Position slot);
	
	//The difficulty is an enum class which means it is fully defined here and doesn't need to be defined in the .cpp
	Difficulty level{ Difficulty::easy };
	//This is creating the board vector, it is fully defined here. 
	std::vector<gameSlot> board;
};
#endif // !GAMEBOARD_H


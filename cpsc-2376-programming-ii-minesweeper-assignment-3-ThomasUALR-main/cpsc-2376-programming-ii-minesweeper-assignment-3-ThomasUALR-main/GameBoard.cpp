#include <iostream>
#include <random>
#include "GameBoard.h"
#include "gameSlot.h"
GameBoard::Size GameBoard::dimension{ GameBoard::Size::small };

//it isn't the chance of a mine, I reduced that to 0 and we still had mines, so
//the hidden mine thing is being applied when it shouldn't be applied

bool operator<(const Position& srcL, const int& srcR)
{
	return srcL.row < srcR&& srcL.column < srcR;
}

bool operator>(const Position& srcL, const int& srcR)
{
	return srcR < srcL.row && srcR < srcL.column;
}

bool operator>=(const Position& srcL, const int& srcR)
{
	return (srcL.row > srcR || srcL.row == srcR) 
		&& (srcL.column > srcR || srcL.column == srcR);
}

bool operator==(const Position& srcL, const Position& srcR)
{
	return srcL.row == srcR.row && srcL.column == srcR.column;
}

bool operator!=(const Position& srcL, const Position& srcR)
{
	return !(srcL==srcR);
}

Position operator+(const Position& srcL, const Position& srcR)
{
	return { srcL.row + srcR.row, srcL.column + srcR.column };
}


Position& Position::operator++()
{
	column++;
	if (column >= (int)GameBoard::dimension)
	{
		column = 0;
		row++;
	}
	return *this;
}

/* CNOTE: General notes
The way classes are constucted means that you have GameBoard() as the main driver with all these smaller
things like makeMove() defined as declared as dependants. Here in the .cpp, which includes the .h file of
the same name, you have to declare these. GameBoard::GameBoard is okay cause it references itself but you
need to use GameBoard::makeMove since these are dependant on GameBoard to begin with.

- GameBoard::dimensions is using ::, which is a resolution scope operator. This means that we narrow our scope
using it. An example is if we want to talk about a city. Say we want to go to springfield, there are a few of those.
We narrow it down by saying we want to go to the springfield in illinoi. We would write it as Illinoi::SpringField.
We are narrowing where the location of the data is for the codes sake. Despite the narrowing, it doesn't carry info,
it just narrows where we are looking. 

- If you want to proceed with good practice, initialize using int x {3}; instead of int x = 3; the first is
simply good practice.
*/



// Class Defenitions (Public)

GameBoard::GameBoard()
{
	//Difficutly and Size Selection
	char difficultyselection{ 'Z' };
	char sizeselection{ 'Z' };
	while (!(difficultyselection == 'E' || difficultyselection == 'M' || difficultyselection == 'H'))
	{
		std::cout << "Choose a difficulty ( E - 25 | M - 30 | H - 40 ): ";
		std::cin >> difficultyselection;
	}
		
	while (!(sizeselection == 'S' || sizeselection == 'M' || sizeselection == 'L'))
	{
		std::cout << "Choose a size ( S - 10X10 | M - 15X15 | L - 25X25 ): ";
		std::cin >> sizeselection;
	}
	
	//Implimentatoin of Difficulty and Size (also the int for difficulty)

	switch (difficultyselection)
	{
	case 'E':
		level = Difficulty::easy;
		break;
	case 'M':
		level = Difficulty::medium;
		break;
	case 'H':
		level = Difficulty::hard;
		break;
	}

	switch (sizeselection)
	{
	case 'S':
		dimension = Size::small;
		break;
	case 'M':
		dimension= Size::medium;
		break;
	case 'L':
		dimension = Size::large;
		break;
	}
	
	//Board Setup
	
	// CNOTE:The std::vector<gameSlot> board comes from GameBoard.h. It was declared there so use it
	// to define it better here.
	
	//
	//std::vector<gameSlot> board((int)dimension * (int)dimension); 
	
	static std::random_device seed;
	static std::default_random_engine e(seed());
	//you're going to want to cast that to a double.... -10
	static std::bernoulli_distribution mined((int)level / 100.0);
	
	board.resize((int)dimension * (int)dimension);
	std::generate(board.begin(), board.end(), [&]() -> gameSlot
		{
			//This should retrun the slot as hiddenMine if mined(e) returns true and hiddenEmpty if false
			return gameSlot(mined(e));

		});
	
	//NOTE: return board; doesn't work here becuase this is a local constructor that exists only in here, so you
	// can't keep referencing the thing and expect it to continue existing. What you do by putting it into board
	// though is you attach it to the board vector class created in the .h file, which means you can reference it
	// at any time just by going there.
	//return board;	

	
	for (int row{ 0 }; row < (int)dimension; row++)
	{
		for (int column{ 0 }; column < (int)dimension; column++)
			board.at(row * (int)dimension + column)
			.setNumNeighbors(countMines({ row,column }));
	}
	/*
	*std::generate(gameBoard.begin(), gameBoard.end(), [&]() ->GameSlot
		{
			//*GameSlot::setNumNeighbors(0);
			return GameSlot{ mined(engine) };
		});
	
	//need old fashioned for loops nested to iterate over the board and set the numNeighbors member for each slot.
	/*for (auto& slot : board)
	{
		slot.setNumNeighbors(countMines(slot));
	}
	for (int row{ 0 }; row < (int)dimension; row++)
	{
		for (int column{ 0 }; column < (int)dimension; column++)
			board.at(row * (int)dimension + column)
			.setNumNeighbors(countMines({ row,column }));
	}
	*/



}

void GameBoard::makeMove()
{
	char row{ 'Z' };
	int column{ -1 };
	int numRow{ 0 };
	do
	{
		//FIX Don't know how to fix this but essentially you need to figure out how to line up the columns and the slots
		//NOTE: Just like before, since the term dimension is just a class at the time of calling it, you
		//need to determine what it will be, so you have to declare it as an int when called
		if (dimension == Size::large)
		{
			while (row < 'A' || row > 'A' + (int)dimension - 1)
			{
				std::cout << "Choose a row: ";
				std::cin >> row;
			}
		}
		else
		{
			while (row < 'A' || row > 'A' + (int)dimension)
			{
				std::cout << "Choose a row: ";
				std::cin >> row;
			}
		}
		numRow = row - 'A';
		while (column < 0 || column > (int)dimension)
		{
			std::cout << "Choose a column: ";
			std::cin >> column;
			column--;
		}
	} while (getSlot({ numRow, column }).isRevealed());
	//******** NEW *************
	char flagResponse{ ' ' };
	while (flagResponse != 'N' && flagResponse != 'Y')
	{
		std::cout << "Do you wish to flag/unflag this spot? ";
		std::cin >> flagResponse;
	}

	if (flagResponse == 'Y')
	{
		modifySlot({ numRow, column }).flipFlag();
	}
	//***********************
	else
	{
		modifySlot({ numRow, column }).reveal();
	}
}

bool GameBoard::gameOver()
{
	bool stillEmptyM{ false };
	for (auto slot : board)
	{
		if (slot.exploded())
		{
			stillEmptyM = true;
		}
	}
	return stillEmptyM;
}

bool GameBoard::wonGame()
{
	bool stillEmpty{ true };
	for (auto slot : board)
	{
		if (!slot.isRevealed())
		{
			stillEmpty = true;
		}
	}
	//If there is still an empty slot, it should return false
	return !stillEmpty;
}

void GameBoard::revealMines()
{
	for (auto slot : board)
	{
		if (slot.isMined() && !slot.isRevealed())
		{
			slot.reveal();
		}
	}
}

gameSlot GameBoard::getSlot(Position slotNum) const
{
	return board.at(slotNum.row * (int)dimension + slotNum.column);
}

gameSlot& GameBoard::modifySlot(Position slotNum)
{
	return board.at(slotNum.row * (int)dimension + slotNum.column);
}

//The reason that the following definition doesn't need a GameBoard:: before it is becauase it
//is a friend, or in other words, not dependant on the GameBoard class itself. This allows the
//operator<< to gain access to the private class without being a depandant of GameBoard

std::ostream& operator<<(std::ostream& o, const GameBoard& src)
{
	char rowName{ 'A' };
	int colName{ 1 };
	system("CLS");

	o << "   ";
	for (int i{ 0 }; i < (int)GameBoard::dimension; i++)
	{
		o << colName << " ";
		colName++;
	}
	o << std::endl;
	for (int row{ 0 }; row < (int)GameBoard::dimension; row++)
	{
		o << rowName << "| ";
		rowName++;
		for (int column{ 0 }; column < (int)GameBoard::dimension; column++)
		{
			o << src.getSlot({ row,column });
		}
		o << "\n";
	}
	return o;
}

//Class Defenitions (Private)

int GameBoard::countMines(Position slot)
{
//I am assuming what this needs. Since it is an int it probobly counts the mines around the slot
//picked and returns the number.
	int mineCount{ 0 };
	for (int neighborRow{ -1 }; neighborRow <= 1; neighborRow++)
	{
		for (int neighborColumn{ -1 }; neighborColumn <= 1; neighborColumn++)
		{
			if ((neighborColumn != 0 || neighborRow != 0)
				&& slot.row + neighborRow >= 0 && slot.row + neighborRow < (int)dimension
				&& slot.column + neighborColumn >= 0 && slot.column + neighborColumn < (int)dimension
				&& (getSlot({ slot.row + neighborRow, slot.column + neighborColumn }).isMined()) == true)
			{
				mineCount++;
			}
		}
	}
	return mineCount;
}
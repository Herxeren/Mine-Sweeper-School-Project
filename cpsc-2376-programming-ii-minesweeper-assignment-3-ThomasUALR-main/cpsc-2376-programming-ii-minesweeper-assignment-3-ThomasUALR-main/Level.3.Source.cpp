#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include "gameSlot.h"
#include "GameBoard.h"

void splashScreen();
void displayGameDone(GameBoard& board);

int main()
{
	splashScreen();

	char playAgain{ 'y' };
	while (playAgain == 'y' || playAgain == 'Y')
	{
		GameBoard board;
		while (!board.gameOver())
		{
			std::cout << board;
			board.makeMove();
		}
		displayGameDone(board);
		std::cout << "\nDo you wish to play another game? (y/n): ";
		std::cin >> playAgain;

	}
}
void splashScreen()
{
	std::cout << "Mine Sweeper!" << std::endl;
	std::cout << std::endl;
	std::cout << "by, Christian Thomas (2024)" << std::endl;
	std::cout << std::endl;
	std::cout << "INSTRUCTIONS:" << std::endl;
	std::cout << std::endl;
	std::cout << "Clear the minefield without hitting a mine!" << std::endl;
	system("PAUSE");
}

void displayGameDone(GameBoard& board)
{
	board.revealMines();
	std::cout << board;
	if(!board.wonGame())
	{
		std::cout << "The mine exploded.... You are dead!!!!\n";
		std::cout << "Better luck next time!";
		return;
	}
	std::cout << "You have cleared the mine field!\n";
	std::cout << "You are loved by all! Use your power for good!";
}




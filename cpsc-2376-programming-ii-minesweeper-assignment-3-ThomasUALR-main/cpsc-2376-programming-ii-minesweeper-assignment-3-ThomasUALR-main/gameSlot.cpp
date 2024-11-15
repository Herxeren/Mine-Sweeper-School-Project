#include "gameSlot.h"

/* Notes:
* -Interesting thing to note about the gameSlot::gameSlot() and why it is commented out. Since it is declared
* in the relevant .h file as a default constructor, it does not need to be defined in the .cpp file unlike the rest
* which are activly looking for a defenition in the relevant files.
* 
* -Relevant note, you can tell if something needs a defenition just by looking for the green squigly under the
* class declerations in the .h
*/




// Class Definitoins (Public)


gameSlot::gameSlot()
{
	//This is supposed to be empty
}

gameSlot::gameSlot(bool mined)
{
	if (mined == true)
	{
		piece = gamePieces::hiddenMine;
	}
	else
	{
		piece = gamePieces::hiddenEmpty;
	}
}

void gameSlot::setNumNeighbors(int num)
{
	numNeighbors = num;
}

void gameSlot::flipFlag()
{
	flagged = !flagged;
}

void gameSlot::reveal()
{
	switch (piece)
	{	
	case gamePieces::hiddenEmpty:
		piece = gamePieces::revealedEmpty;
		break;
	case gamePieces::hiddenMine:
		piece = gamePieces::revealedMine;
		break;
	}
}

bool gameSlot::isRevealed()
{
	switch (piece)
	{
	case gamePieces::revealedMine:
		return true;
		break;
	case gamePieces::revealedEmpty:
		return true;
		break;
	default:
		return false;
	}

}

bool gameSlot::isMined() const
{
	switch (piece)
	{
	case gamePieces::hiddenMine:
		return true;
		break;
	case gamePieces::revealedMine:
		return true;
		break;
	default:
		return false;
	}
}

bool gameSlot::exploded()
{
	if (piece == gamePieces::revealedMine)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::ostream& operator<<(std::ostream& o, const gameSlot& src)
{
	if (src.flagged)
	{
		o << "F ";
	}
	else
	{
		switch (src.piece)
		{
		case gameSlot::gamePieces::hiddenEmpty:
			o << "- ";
			break;
		case gameSlot::gamePieces::hiddenMine:
			o << "- ";
			break;
		case gameSlot::gamePieces::revealedMine:
			o << "* ";
			break;
		case gameSlot::gamePieces::revealedEmpty:
			if (src.numNeighbors == 0)
			{
				o << "  ";
			}
			else
			{
				o << src.numNeighbors << " ";
			}
			break;
		}
		
	}
	return o;
}
#ifndef GAMESLOT_H
#define GAMESLOT_H
#include <iostream>
class gameSlot
{
public:
	
	gameSlot();
	gameSlot(bool mined);

	void setNumNeighbors(int num);

	void flipFlag();
	void reveal();

	bool isRevealed();
	bool isMined() const;
	bool exploded();
	
	friend std::ostream& operator<<(std::ostream& o, const gameSlot& src);
private:
	//Remember, enum classes are fully defined in their respective .h files, no need to define them in their
	//respective .cpp files unless you want to mess with them, I think.
	enum class gamePieces { hiddenEmpty, revealedEmpty, hiddenMine, revealedMine };
	gamePieces piece{ gamePieces::hiddenEmpty };
	bool flagged{ false };
	int numNeighbors{ 0 };
};

#endif // !GAMESLOT_H
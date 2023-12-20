#pragma once
#include <iostream>
#include "Board.h"

class Game {
	private:
		char _currPlayer;

	public:
		Game();
		~Game();

		int turn(const std::string& playerMove);
		bool checkIfTurnPossible() const;
		std::string getBoardAsString() const;

};
#include "HumanPlayer.h"

#include <iostream>

void HumanPlayer::TakeTurn()
{
	int turn;
	std::cin >> turn;
}

void HumanPlayer::PlaceShips()
{
	std::cout << std::endl << "Place ships randomly? [Y] or [N]";

	char input;
	std::cin >> input;

	if ( input == 'Y' )
	{
		PlaceShipsRandomly();
	}
}

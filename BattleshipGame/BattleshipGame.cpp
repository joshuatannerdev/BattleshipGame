// BattleshipGame.cpp : Executes the game loop.

#include <iostream>
#include <stdlib.h>     
#include <time.h>     
#include <Windows.h>

#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "InputValidation.h"

bool RunMainMenu();
void RunGame();

int main()
{
	// Random seed - used for random placement and strikes
	srand( static_cast<unsigned int>( time( NULL ) ) );

	while ( true )
	{
		if ( RunMainMenu() )
		{
			RunGame();
		}
		else
		{
			// Quit
			return 0;
		}
	}
	return 0;
}

/// <summary>
/// Runs the main menu. Returns true if starting a game.
/// </summary>
bool RunMainMenu()
{
	system( "cls" );

	const char* titleText = " ____    ____  ______  ______  _        ___  _____ __ __  ____  ____   \n"
		"|    \\  /    ||      ||      || |      /  _]/ ___/|  |  ||    ||    \\ \n"
		"|  o  )|  o  ||      ||      || |     /  [_(   \\_ |  |  | |  | |  o  ) \n"
		"|     ||     ||_|  |_||_|  |_|| |___ |    _]\\__  ||  _  | |  | |   _/  \n"
		"|  O  ||  _  |  |  |    |  |  |     ||   [_ /  \\ ||  |  | |  | |  |    \n"
		"|     ||  |  |  |  |    |  |  |     ||     |\\    ||  |  | |  | |  |    \n"
		"|_____||__|__|  |__|    |__|  |_____||_____| \\___||__|__||____||__|    \n";


	std::cout << titleText << std::endl << std::endl;
	std::cout << "[1] Start game" << std::endl;
	std::cout << "[2] Quit" << std::endl;

	int input = GetInputInt( 1, 2 );
	return input == 1 ? true : false;
}

/// <summary>
/// Run a game until completion.
/// </summary>
void RunGame()
{
	system( "cls" );

	HumanPlayer humanPlayer;
	ComputerPlayer computerPlayer;

	humanPlayer.PlaceShips();
	computerPlayer.PlaceShips();

	bool humanWon = false;
	bool computerWon = false;

	while ( !humanWon && !computerWon )
	{
		humanPlayer.DrawPlayerGrid();
		computerPlayer.DrawPlayerGrid();

		Vector2dInt strikePos = humanPlayer.ChooseStrikePos( computerPlayer.GetGridReadOnly() );
		computerPlayer.StrikePlayerGrid( strikePos );
		if ( computerPlayer.CheckAllShipsDestroyed() )
		{
			humanWon = true;
			break;
		}

		strikePos = computerPlayer.ChooseStrikePos( humanPlayer.GetGridReadOnly() );
		humanPlayer.StrikePlayerGrid( strikePos );
		if ( humanPlayer.CheckAllShipsDestroyed() )
		{
			computerWon = true;
			break;
		}
	}

	system( "cls" );
	humanPlayer.DrawPlayerGrid();
	computerPlayer.DrawPlayerGrid();

	std::cout << std::endl << ( humanWon ? "YOU WIN!" : "YOU LOSE!" );
	Sleep( 3000 );
}
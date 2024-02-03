// BattleshipGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <Windows.h>

#include "HumanPlayer.h"
#include "ComputerPlayer.h"


bool RunMainMenu();
void RunGame();

int main()
{
    srand( static_cast<unsigned int>( time( NULL ) ) );

    while ( true )
    {
        if ( RunMainMenu() )
        {
            RunGame();
        }
        else
        {
            // Program ends
            return 0;
        }
    }

    return 0;
}

bool RunMainMenu()
{
    system( "cls" );

    std::cout << "Welcome to Battleship!" << std::endl << std::endl;
    std::cout << "Choose:" << std::endl;
    std::cout << "[1] Start game" << std::endl;
    std::cout << "[2] Quit" << std::endl;

    int input;
    std::cin >> input;

    return input == 1 ? true : false;
}

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
        computerPlayer.DrawPlayerGrid( 30 );

        Vector2dInt strikePos = humanPlayer.ChooseStrikePos(computerPlayer.GetGridReadOnly());
        computerPlayer.StrikePlayerGrid( strikePos );
        if ( computerPlayer.CheckAllShipsDestroyed() )
        {
            humanWon = true;
            break;
        }

        Vector2dInt strikePos2 = computerPlayer.ChooseStrikePos(humanPlayer.GetGridReadOnly());
        humanPlayer.StrikePlayerGrid( strikePos );
        if ( humanPlayer.CheckAllShipsDestroyed() )
        {
            computerWon = true;
            break;
        }
    }

    std::cout << ( humanWon ? "YOU WIN!" : "YOU LOSE!" );
    Sleep( 3000 );
}

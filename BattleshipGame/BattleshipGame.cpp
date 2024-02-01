// BattleshipGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "HumanPlayer.h"
#include "ComputerPlayer.h"

int main()
{
    bool gameActive = true;

    HumanPlayer humanPlayer;
    ComputerPlayer computerPlayer;

    while ( true )
    {
        if ( !gameActive )
        {
            // Run main menu
        }
        else
        {
            humanPlayer.DrawPlayerGrid();
            computerPlayer.DrawPlayerGrid( 30 );

            humanPlayer.TakeTurn();
            computerPlayer.TakeTurn();
        }
    }


   
   


}
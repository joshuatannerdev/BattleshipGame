#include "HumanPlayer.h"
#include "Grid.h"
#include "Ship.h"

#include <Windows.h>
#include <iostream>


constexpr static int charAInt = static_cast<int>( 'A' );

Vector2dInt HumanPlayer::ChooseStrikePos( const Grid* const _opponentGrid )
{
	system( "cls" );
	DrawPlayerGrid();

	// Data validation 

	int column;
	char row;
	std::cout << "Enter coordinates to strike..." << std::endl;
	std::cout << "Column: ";
	std::cin >> column;
	std::cout << "Row: ";
	std::cin >> row;

	Vector2dInt const strikePos = Vector2dInt( static_cast<int> ( column ) - 1, static_cast<int>( toupper( row ) ) - charAInt );
	return strikePos;	
}

void HumanPlayer::PlaceShips()
{
	std::cout << std::endl << "Auto place ships? [Y] or [N]: ";

	char input;
	std::cin >> input;

	if ( input == 'y' )
	{
		PlaceShipsRandomly();
		return;
	}

	constexpr int charAInt = static_cast<int>( 'A' );

	for ( unsigned int i = 0; i < ShipType::SHIPTYPE_COUNT; i++ )
	{
		Ship* ship = m_ships[i];		

		bool positionConfirmed = false;
		while ( !positionConfirmed )
		{
			system( "cls" );
			DrawPlayerGrid();

			// Data validation 

			int column;
			char row;
			std::cout << "Enter coordinates for next ship..." << std::endl;
			std::cout << "Column: ";
			std::cin >> column;
			std::cout << "Row: ";
			std::cin >> row;

			std::cout << "Select orientation ";
			for ( unsigned int i = 0; i < ShipOrientation::SHIPORIENTATION_COUNT; i++ )
			{
				std::cout << "[" << i + 1 << "] " << ShipOrientationToString( static_cast<ShipOrientation>( i ) ) << " ";
			}

			int orientation;
			std::cin >> orientation;

			Vector2dInt const newStartPoint = Vector2dInt( static_cast<int> ( column ) - 1, static_cast<int>( toupper( row ) ) - charAInt );
			ShipOrientation const newOrientation = static_cast<ShipOrientation>( orientation - 1 );
			
			ship->SetPosition( newStartPoint.x, newStartPoint.y );
			ship->SetOrientation( newOrientation );

			if ( TryPlaceShipOnGrid( static_cast<ShipType>( i ) ) )
			{
				positionConfirmed = true;
			}
			else
			{
				std::cout << "Invalid placement, try again...";
				Sleep( 2000 );
			}
		}
	}

}

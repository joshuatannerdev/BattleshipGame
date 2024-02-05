#include "HumanPlayer.h"
#include "Grid.h"
#include "Ship.h"
#include "InputValidation.h"

#include <Windows.h>
#include <iostream>

// Static char-to-int, used in converting input to coordinates.
constexpr static int g_charAInt = static_cast<int>( 'A' );

/// <summary>
/// Takes user input to select strike position against opponent.
/// </summary>
/// <returns>Strike Position</returns>
Vector2dInt HumanPlayer::ChooseStrikePos( const Grid* const _opponentGrid )
{
	// Draw both player's grids.
	system( "cls" );
	m_grid->Draw();
	_opponentGrid->Draw(); 
	std::cout << std::endl;
	
	std::cout << "Enter coordinates to strike..." << std::endl;
	std::cout << "Column: "; 
	std::cout << std::endl;
	int column = GetInputInt(1, g_gridWidth);
	std::cout << "Row: "; 
	std::cout << std::endl;
	char row = GetInputChar(static_cast<char>(g_charAInt), static_cast<char>( g_charAInt + g_gridHeight));

	Vector2dInt const strikePos = Vector2dInt( static_cast<int> ( column ) - 1, static_cast<int>( toupper( row ) ) - g_charAInt );
	return strikePos;	
}

/// <summary>
/// Places ships - either automatically or manually.
/// </summary>
void HumanPlayer::PlaceShips()
{
	system( "cls" );
	DrawPlayerGrid();

	std::cout << std::endl << "Auto place ships? [Y] or [N/Any]: ";

	char input = GetInputChar();
	if ( toupper(input) == 'Y' )
	{
		PlaceShipsRandomly();
		return;
	}

	// Run through each ship, requesting input and validating placement.
	for ( unsigned int i = 0; i < ShipType::SHIPTYPE_COUNT; i++ )
	{
		ShipType const shipType = static_cast<ShipType>(i);
		Ship* ship = m_ships[shipType];

		bool positionConfirmed = false;
		while ( !positionConfirmed )
		{			
			std::cout << "Enter coordinates for " << ShipTypeToString( shipType ) << "..." << std::endl;
			std::cout << "Column: " << std::endl;
			int column = GetInputInt( 1, g_gridWidth );
			std::cout << "Row: " << std::endl;
			char row = GetInputChar( static_cast<char>( g_charAInt ), static_cast<char>( g_charAInt + g_gridHeight - 1 ) );
			std::cout << "Select orientation";
			for ( unsigned int j = 0; j < ShipOrientation::SHIPORIENTATION_COUNT; j++ )
			{
				std::cout << " [" << j + 1 << "] " << ShipOrientationToString( static_cast<ShipOrientation>( j ) );
			}
			std::cout << ": " << std::endl;
			int orientation = GetInputInt( 1, static_cast<int>( ShipOrientation::SHIPORIENTATION_COUNT ) );

			Vector2dInt const newStartPos = Vector2dInt( static_cast<int> ( column ) - 1, static_cast<int>( toupper( row ) ) - g_charAInt );
			ShipOrientation const newOrientation = static_cast<ShipOrientation>( orientation - 1 );
			ship->SetPosition( newStartPos );
			ship->SetOrientation( newOrientation );

			if ( TryPlaceShipOnGrid( shipType ) )
			{
				system( "cls" );
				DrawPlayerGrid();
				positionConfirmed = true;
			}
			else
			{
				std::cout << "Invalid placement, try again..." << std::endl;
			}
		}
	}
}
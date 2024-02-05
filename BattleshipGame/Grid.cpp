#include "Grid.h"

#include <iostream>
#include <Windows.h>
#include <assert.h>

/// <summary>
/// Helper function - get the char to output for a grid type.
/// </summary>
char static GetCharForGridType( GridType _gridType )
{
	switch ( _gridType )
	{
		case EMPTY:
			return '_';
		case MISS:
			return 'O';
		case HIT:
			return 'X';
		case SHIP:
			return '*';
		case SHIP_SUNK:
			return '#';
	}
	assert( false && "Unknown GridType" );
	return '?';
}

/// <summary>
/// Helper function - get the output color for a grid type.
/// https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c
/// </summary>
int static GetColourForGridType( GridType _gridType )
{
	switch ( _gridType )
	{
		case EMPTY:
			return 15; // White
		case MISS:
			return 10; // Green
		case HIT:
			return 12; // Red
		case SHIP:
			return 9; // Blue
		case SHIP_SUNK:
			return 12; // Red
	}
	assert( false && "Unknown GridType" );
	return 0;
}

/// <summary>
/// Helper function - set the console cursor position
/// </summary>
/// <param name="_xPos"></param>
/// <param name="_yPos"></param>
void static GoToXY( int _xPos, int _yPos )
{
	COORD point{ static_cast<SHORT>( _xPos ), static_cast<SHORT>( _yPos ) };
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), point );
}

/// <summary>
/// Helper function - set console text. Default is 15 (white).
/// </summary>
/// <param name="_colourValue"></param>
void static SetTextColour( int _colourValue = 15 )
{
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hConsole, _colourValue );
}

/// <summary>
/// Grid constructor. 
/// </summary>
/// <param name="_xDrawOffset">Calls to draw grid will start at this offset.</param>
/// <param name="_hideShipGridType">If true, don't show ships when the grid is drawn.</param>
Grid::Grid( int _xDrawOffset, bool _hideShipGridType )
	: m_gridTypes()
	, m_xDrawOffset( _xDrawOffset )
	, m_hideShipGridType( _hideShipGridType )
{
	for ( unsigned int i = 0; i < g_gridHeight; i++ )
	{
		for ( unsigned int j = 0; j < g_gridWidth; j++ )
		{
			m_gridTypes[i][j] = GridType::EMPTY;
		}
	}
}

/// <summary>
/// Grid destructor.
/// </summary>
Grid::~Grid()
{
}

/// <summary>
/// Output the grid to console, including borders and column/row indicators.
/// </summary>
void Grid::Draw() const
{
	// Start drawing from the defined offset, so player grids don't overlap.
	int drawPosX = m_xDrawOffset;
	int drawPosY = 0;
	GoToXY( drawPosX, drawPosY );

	// Column numbers and border
	std::cout << "  ";
	for ( unsigned int j = 0; j < g_gridWidth; j++ )
	{
		std::cout << " " << j + 1;
	}
	GoToXY( drawPosX, ++drawPosY );
	std::cout << "  +";
	for ( unsigned int j = 0; j < g_gridWidth; j++ )
	{
		std::cout << "-+";
	}
	GoToXY( drawPosX, ++drawPosY );

	// Draw each row
	char rowLetter = 'A';
	for ( unsigned int i = 0; i < g_gridHeight; i++ )
	{		
		std::cout << rowLetter << " |";
		rowLetter++;

		for ( unsigned int j = 0; j < g_gridWidth; j++ )
		{
			GridType gridType = m_gridTypes[i][j];
			if ( m_hideShipGridType && gridType == GridType::SHIP )
			{
				gridType = GridType::EMPTY;
			}
			SetTextColour( GetColourForGridType( gridType ) );
			std::cout << GetCharForGridType( gridType );
			SetTextColour();
			std::cout << "|";
		}
		GoToXY( drawPosX, ++drawPosY );
	}
}

/// <summary>
/// Get the GridType for a given position.
/// </summary>
GridType Grid::GetGridTypeAtPos( const Vector2dInt& _pos ) const
{
	if ( _pos.x < 0 || _pos.x > g_gridWidth || _pos.y < 0 || _pos.y > g_gridHeight )
	{
		// Invalid - out of bounds
		return GridType::GRIDTYPE_COUNT;
	}
	return m_gridTypes[_pos.y][_pos.x];
}

/// <summary>
/// Set the GridType for a given position.
/// </summary>
void Grid::SetGridTypeAtPos( const Vector2dInt& _pos, GridType _gridType )
{
	assert( _gridType >= 0 && _gridType < GridType::GRIDTYPE_COUNT );
	if ( _pos.x < 0 || _pos.x > g_gridWidth || _pos.y < 0 || _pos.y > g_gridHeight )
	{
		// Invalid - out of bounds
		return;
	}
	m_gridTypes[_pos.y][_pos.x] = _gridType;
}
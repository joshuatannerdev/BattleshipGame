#include "Grid.h"
#include "Windows.h"

#include <iostream>

char GetCharForGridType( GridType _gridType )
{
	switch ( _gridType )
	{
		case EMPTY:
			return ' ';
		case MISS:
			return 'O';
		case HIT:
			return 'X';
		case SHIP:
			return '+';
	}
	// Assert - unexpected value!
	return '?';
}


void GoToXY( int _xPos, int _yPos )
{
	COORD point{ static_cast<SHORT>( _xPos ), static_cast<SHORT>( _yPos ) };
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), point );
}

void GetCursorPositon( int& o_xPos, int& o_yPos )
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if ( GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &cbsi ) )
	{
		o_xPos = cbsi.dwCursorPosition.X;
		o_yPos = cbsi.dwCursorPosition.Y;
;	}
}


Grid::Grid()
	:m_gridTypes()
{
	for ( unsigned int i = 0; i < gridHeight; i++ )
	{
		for ( unsigned int j = 0; j < gridWidth; j++ )
		{
			m_gridTypes[i][j] = GridType::EMPTY;
		}
	}
}

Grid::~Grid()
{
}

void Grid::Draw( int _startPosX, int _startPosY ) const
{
	int drawPosX = _startPosX;
	int drawPosY = _startPosY;
	GoToXY( drawPosX, drawPosY );

	for ( unsigned int j = 0; j < gridWidth; j++ )
	{
		std::cout << " " << j + 1;
	}
	GoToXY( drawPosX, ++drawPosY );
	std::cout << " __";
	for ( unsigned int j = 0; j < gridWidth; j++ )
	{
		std::cout << "__";
	}
	GoToXY( drawPosX, ++drawPosY );

	char letter = 'A';

	for ( unsigned int i = 0; i < gridHeight; i++ )
	{		
		std::cout << letter << " |";
		letter++;

		for ( unsigned int j = 0; j < gridWidth; j++ )
		{
			std::cout << GetCharForGridType( m_gridTypes[i][j] ) << "|";
		}

		GoToXY( drawPosX, ++drawPosY );
	}
}

GridType Grid::GetGridTypeAtPos( int _posX, int _posY ) const
{
	if ( _posX < 0 || _posX > gridWidth || _posY < 0 || _posY > gridHeight )
	{
		// Invalid - out of bounds
		return GridType::GRIDTYPE_COUNT;
	}
	return m_gridTypes[_posY][_posX];
}

void Grid::SetGridTypeAtPos( int _posX, int _posY, GridType _gridType )
{
	if ( _posX < 0 || _posX > gridWidth || _posY < 0 || _posY > gridHeight )
	{
		// Invalid - out of bounds
		return;
	}
	m_gridTypes[_posY][_posX] = _gridType;
}

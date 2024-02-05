#include "ComputerPlayer.h"
#include "Grid.h"
#include "ShipDeclare.h"

ComputerPlayer::ComputerPlayer()
	: Player( 30, false )
	, m_lastSuccesfulStrikePos( 0, 0 )
{
}

Vector2dInt ComputerPlayer::ChooseStrikePos( const Grid* const _opponentGrid )
{
	bool foundStrikePos = false;
	Vector2dInt strikePos( 0, 0 );

	if ( _opponentGrid->GetGridTypeAtPos( m_lastSuccesfulStrikePos ) == GridType::HIT )
	{
		// Our last strike hit a ship but did not sink it - focus on destroying this one.

		// Check each of the four directions around this point - have we hit any others?
		// If so, we know the direction we should strike in. Otherwise, pick a random direction.
		Vector2dInt testStrikePos = m_lastSuccesfulStrikePos;
		Vector2dInt directionToStrike = Vector2dInt( 0, 0 );
		bool directionFound = false;

		for ( unsigned int i = 0; i < ShipOrientation::SHIPORIENTATION_COUNT; i++ )
		{
			Vector2dInt direction = GetDirectionForShipOrientation( static_cast<ShipOrientation>( i ) );
			Vector2dInt adjacentPos = m_lastSuccesfulStrikePos + direction;
			if ( _opponentGrid->GetGridTypeAtPos( adjacentPos ) == GridType::HIT )
			{
				// This seems to be the direction of the ship, strike in this direction.
				directionToStrike = direction;		
				directionFound = true;
			}
		}

		if ( !directionFound )
		{
			ShipOrientation randomOrientation = static_cast<ShipOrientation>( 
				rand() % static_cast<int>( ShipOrientation::SHIPORIENTATION_COUNT ) );
			directionToStrike = GetDirectionForShipOrientation( randomOrientation );
		}

		bool encounteredMiss = false;
		while ( true )
		{
			testStrikePos += directionToStrike;
			GridType const adjacentGridType = _opponentGrid->GetGridTypeAtPos( testStrikePos );
			if ( adjacentGridType == GridType::MISS )
			{
				// We've tried hitting here before and there was nothing.
				if ( encounteredMiss )
				{
					// We've already encountered a MISS in both directions. Find a random strike pos intead.
					break;
				}				
				// Let's start moving in the opposite direction (but along the same plane).
				encounteredMiss = true;
				directionToStrike *= -1;
				testStrikePos = m_lastSuccesfulStrikePos;
			}
			else if ( adjacentGridType != GridType::HIT )
			{
				// We haven't hit here before, so let's try.
				strikePos = testStrikePos;
				foundStrikePos = true;
				break;
			}
		}
	}

	if ( !foundStrikePos )
	{
		GridType testGridType = GridType::HIT;

		while ( testGridType == GridType::HIT || testGridType == GridType::MISS || testGridType == GridType::SHIP_SUNK  )
		{
			strikePos = Vector2dInt( rand() % g_gridWidth, rand() % g_gridHeight );
			testGridType = _opponentGrid->GetGridTypeAtPos( strikePos );
		}
	}

	if ( _opponentGrid->GetGridTypeAtPos( strikePos ) == SHIP )
	{
		m_lastSuccesfulStrikePos = strikePos;
	}

	return strikePos;
}

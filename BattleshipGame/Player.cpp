#include "Player.h"
#include "Grid.h"
#include "Ship.h"

#include <algorithm>
#include <stdlib.h>     /* srand, rand */


Player::Player()
	: m_hasPlacedShips(false)
	, m_ships()
{
	m_grid = new Grid();

	for ( unsigned int i = 0; i < ShipType::SHIPTYPE_COUNT; i++ )
	{
		m_ships[i] = new Ship( static_cast<ShipType>(i) );
	}

}

Player::~Player()
{
	delete m_grid;
	m_grid = nullptr;

	for ( unsigned int i = 0; i < ShipType::SHIPTYPE_COUNT; i++ )
	{
		if ( m_ships[i] )
		{
			delete m_ships[i];
			m_ships[i] = nullptr;
		}
	}
}

void Player::PlaceShips()
{
	PlaceShipsRandomly();
}

void Player::DrawPlayerGrid( int _startPosX, int _startPosY ) const
{
	m_grid->Draw( _startPosX, _startPosY );
}

void Player::StrikePlayerGrid( Vector2dInt _strikePos ) // Const reference
{
	if ( m_grid->GetGridTypeAtPos( _strikePos.x, _strikePos.y ) != GridType::SHIP )
	{
		return;
	}

	for ( unsigned int i = 0; i < ShipType::SHIPTYPE_COUNT; i++ )
	{
		if ( m_ships[i]->IsPosInShipBounds( _strikePos ) )
		{
			bool isNowDestroyed = m_ships[i]->StrikeShip();
			if ( isNowDestroyed )
			{
				MarkShipAsSunkOnGrid( static_cast<ShipType>( i ) );
			}
			else
			{
				m_grid->SetGridTypeAtPos( _strikePos.x, _strikePos.y, GridType::HIT );
			}
			break;
		}
	}
}

bool Player::CheckAllShipsDestroyed() const
{
	for ( unsigned int i = 0; i < ShipType::SHIPTYPE_COUNT; i++ )
	{
		if ( !m_ships[i]->IsShipDestroyed() )
		{
			return false;
		}
	}
	return true;
}

void Player::PlaceShipsRandomly()
{
	for ( unsigned int i = 0; i < ShipType::SHIPTYPE_COUNT; i++ )
	{
		while ( true )
		{
			ShipOrientation orientation = static_cast<ShipOrientation>( rand() % ShipOrientation::SHIPORIENTATION_COUNT );

			int x = rand() % gridWidth;
			int y = rand() % gridHeight;

			m_ships[i]->SetOrientation( orientation );
			m_ships[i]->SetPosition( x, y );

			// TODO: Smarter generation of random values that account for length and orientation

			if ( TryPlaceShipOnGrid( static_cast<ShipType>( i ) ) )
			{
				break;
			}
		}

	}
}

bool Player::TryPlaceShipOnGrid( ShipType _shipType )
{
	// Assert that ship type is a sensible value	

	const Ship* const ship = m_ships[_shipType];

	Vector2dInt startPoint, endPoint;
	ship->GetShipBounds( startPoint, endPoint );

	bool inBounds = m_grid->IsPosInGridBounds( startPoint ) && m_grid->IsPosInGridBounds( endPoint );
	if ( !inBounds )
	{
		// Can't place here...
		return false;
	}

	bool overlapsAnotherShip = false;

	Vector2dInt pointIter = startPoint;
	Vector2dInt delta = endPoint - pointIter;
	Vector2dInt clampedDelta = Vector2dInt(
		std::clamp( delta.x, -1, 1 ),
		std::clamp( delta.y, -1, 1 )
	);
	for ( int i = 0; i < delta.Length(); i++ )
	{
		if ( m_grid->GetGridTypeAtPos( pointIter.x, pointIter.y ) == GridType::SHIP )
		{
			overlapsAnotherShip = true;
			break;
		}

		pointIter += clampedDelta;
	}

	if ( overlapsAnotherShip )
	{
		// Can't place here...
		return false;
	}


	// Otherwise, its safe to place on the grid
	pointIter = startPoint;
	for (int i = 0; i < delta.Length(); i++)	
	{
		m_grid->SetGridTypeAtPos( pointIter.x, pointIter.y, GridType::SHIP );
		pointIter += clampedDelta;
	}

	return true;
}

void Player::MarkShipAsSunkOnGrid( ShipType _shipType )
{
	const Ship* const ship = m_ships[_shipType];

	Vector2dInt startPoint, endPoint;
	ship->GetShipBounds( startPoint, endPoint );

	Vector2dInt pointIter = startPoint;
	Vector2dInt delta = endPoint - pointIter;
	Vector2dInt clampedDelta = Vector2dInt(
		std::clamp( delta.x, -1, 1 ),
		std::clamp( delta.y, -1, 1 )
	);
	for ( int i = 0; i < delta.Length(); i++ )
	{
		m_grid->SetGridTypeAtPos( pointIter.x, pointIter.y, GridType::SHIP_SUNK );
		pointIter += clampedDelta;
	}
}

#include "Ship.h"


int GetLengthForShipType( ShipType _shipType )
{
	switch ( _shipType )
	{
		case PATROL_BOAT:
			return 2;
		case SUBMARINE:
			return 3;
		case DESTROYER:
			return 4;
		case BATTLESHIP:
			return 4;
		case AIRCRAFT_CARRIER:
			return 5;
		default:
			break;
	}
	// Assert - should never hit here!
	return 0;
}

Vector2dInt GetDirectionForShipOrientation( ShipOrientation _shipOrientation )
{
	switch ( _shipOrientation )
	{
		case LEFT:
			return Vector2dInt( -1, 0 );
		case RIGHT:
			return Vector2dInt( 1, 0 );
		case UP:
			return Vector2dInt( 0, -1 );
		case DOWN:
			return Vector2dInt( 0, 1 );		
		default:
			break;
	}
	// Assert - should never hit here!
	return Vector2dInt( 0, 0 );
}

Ship::Ship( ShipType _shipType )
	: m_shipType(_shipType)
	, m_shipOrientation(ShipOrientation::RIGHT)
	, m_startPos(0, 0)
	, m_endPos(0, 0)
	, m_health(GetLengthForShipType(_shipType))
{
}

Ship::~Ship()
{
}


void Ship::SetOrientation( ShipOrientation _shipOrientation )
{
	m_shipOrientation = _shipOrientation;

	CacheEndPosition();
}

void Ship::SetPosition( int _posX, int _posY )
{
	m_startPos.x = _posX;
	m_startPos.y = _posY;

	CacheEndPosition();
}


bool Ship::IsPosInShipBounds( Vector2dInt _pos ) const
{
	// Ship can be orienated in different directions, so check
	// if pos lands in either Start to End OR End to Start.
	if ( ( _pos >= m_startPos && _pos <= m_endPos ) ||
		 ( _pos >= m_endPos && _pos <= m_startPos ) )
	{
		return true;
	}

	return false;
}

bool Ship::StrikeShip()
{
	// Assert health > 0

	m_health--;
	return m_health <= 0;
}

// We need to easily check that no points within the ship are already marked as SHIP on the grid...
// Passing the grid through to check is rather messy through
// Can we devise some kind of GetShipBounds method? E.g. start and end coordinates? Start at the start, 

bool Ship::IsShipDestroyed() const
{
	return m_health <= 0;
}

void Ship::GetShipBounds( Vector2dInt& o_startPos, Vector2dInt& o_endPos ) const
{
	o_startPos = m_startPos;
	o_endPos = m_endPos;
}

void Ship::CacheEndPosition()
{
	// Cache the end point for easier queries of the ship's bounds
	Vector2dInt endPointOffset = GetDirectionForShipOrientation( m_shipOrientation ) *
		GetLengthForShipType( m_shipType );

	m_endPos = m_startPos + endPointOffset;
}

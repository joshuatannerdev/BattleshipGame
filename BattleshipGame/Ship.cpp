#include "Ship.h"

#include <assert.h>

/// <summary>
/// Helper function - return the length for a given ship type.
/// </summary>
int static GetLengthForShipType( ShipType _shipType )
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
	assert( false && "Unknown ShipType" );
	return 0;
}

/// <summary>
/// Ship constructor.
/// </summary>
/// <param name="_shipType">Determines size, and therefore health.</param>
Ship::Ship( ShipType _shipType )
	: m_shipType( _shipType )
	, m_shipOrientation( ShipOrientation::RIGHT )
	, m_startPos( 0, 0 )
	, m_endPos( 0, 0 )
	, m_health( GetLengthForShipType( _shipType ) )
{
}

/// <summary>
/// Ship destructor.
/// </summary>
Ship::~Ship()
{
}

/// <summary>
/// Set the ship's orientation. Triggers a cache of the end position.
/// </summary>
void Ship::SetOrientation( ShipOrientation _shipOrientation )
{
	m_shipOrientation = _shipOrientation;
	CacheEndPosition();
}

/// <summary>
/// Set the ship's position. Triggers a cache of the end position.
/// </summary>
void Ship::SetPosition( const Vector2dInt& _pos )
{
	m_startPos.x = _pos.x;
	m_startPos.y = _pos.y;
	CacheEndPosition();
}

/// <summary>
/// Return true if a given position is within the ship's start and end positions.
/// </summary>
bool Ship::IsPosInShipBounds( const Vector2dInt& _pos ) const
{
	// Ship can be orienated in different directions, so check
	// if pos lands in either Start-to-End OR End-to-Start.
	if ( ( _pos >= m_startPos && _pos <= m_endPos ) ||
		( _pos >= m_endPos && _pos <= m_startPos ) )
	{
		return true;
	}
	return false;
}

/// <summary>
/// Populates o_startPos and o_endPos with the ships start and end positions.
/// </summary>
void Ship::GetShipBounds( Vector2dInt& o_startPos, Vector2dInt& o_endPos ) const
{
	o_startPos = m_startPos;
	o_endPos = m_endPos;
}

/// <summary>
/// Reduce a ship's health by one. This should only be called when a ship tile is hit for the first time.
/// Otherwise, health would fall below 0. Returns true if the ship is now destroyed.
/// </summary>
bool Ship::StrikeShip()
{
	assert( m_health > 0 && "Striking a ship that is already destroyed." );
	m_health--;
	return m_health <= 0;
}

/// <summary>
/// Return true if the ship is at 0 health.
/// </summary>
bool Ship::IsShipDestroyed() const
{
	return m_health <= 0;
}

/// <summary>
/// Return the ship's length.
/// </summary>
int Ship::GetLength() const
{
	return GetLengthForShipType( m_shipType );
}

/// <summary>
/// Cache the ship's end position to streamline queries of the ship's bounds.
/// </summary>
void Ship::CacheEndPosition()
{
	Vector2dInt endPointOffset = GetDirectionForShipOrientation( m_shipOrientation ) *
		GetLengthForShipType( m_shipType );

	m_endPos = m_startPos + endPointOffset;
}
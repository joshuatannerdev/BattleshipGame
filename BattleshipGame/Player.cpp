#include "Player.h"
#include "Grid.h"
#include "Ship.h"

#include <algorithm>    
#include <assert.h>

/// <summary>
/// Default Player constructor.
/// </summary>
Player::Player()
	: m_ships()
{
	InitialisePlayer();
}

/// <summary>
/// Contstructor with paramters for grid behaviour.
/// </summary>
/// <param name="_xDrawOffset">Calls to draw grid will start at this offset.</param>
/// <param name="_hideShipGridType">If true, don't show ships when the grid is drawn.</param>
Player::Player( int _xDrawOffset, bool _hideShipGridType )
	: m_ships()
{
	InitialisePlayer( _xDrawOffset, _hideShipGridType );
}

/// <summary>
/// Destructor - cleanup memory.
/// </summary>
Player::~Player()
{
	if ( m_grid )
	{
		delete m_grid;
		m_grid = nullptr;
	}

	for ( unsigned int i = 0; i < ShipType::SHIPTYPE_COUNT; i++ )
	{
		if ( m_ships[i] )
		{
			delete m_ships[i];
			m_ships[i] = nullptr;
		}
	}
}

/// <summary>
/// Creates the grid and ships.
/// </summary>
void Player::InitialisePlayer( int _xDrawOffset, bool _hideShipGridType )
{
	m_grid = new Grid( _xDrawOffset, _hideShipGridType );

	for ( unsigned int i = 0; i < ShipType::SHIPTYPE_COUNT; i++ )
	{
		m_ships[i] = new Ship( static_cast<ShipType>( i ) );
	}
}

/// <summary>
/// Default functionality for ship placement is to place random.
/// </summary>
void Player::PlaceShips()
{
	PlaceShipsRandomly();
}

/// <summary>
/// Draws this player's grid.
/// </summary>
void Player::DrawPlayerGrid() const
{
	m_grid->Draw();
}

/// <summary>
/// Strike a position on player grid and update the grid type as appropriate.
/// </summary>
/// <param name="_strikePos">The position to strike</param>
void Player::StrikePlayerGrid( const Vector2dInt& _strikePos ) 
{
	
	GridType const gridType = m_grid->GetGridTypeAtPos( _strikePos );
	if ( gridType == GridType::HIT || gridType == GridType::SHIP_SUNK )
	{
		// This position has already been successfully hit. Do nothing.
		return;
	}
	else if ( gridType != GridType::SHIP )
	{
		// There's nothing here. Mark it as a miss on the grid.
		m_grid->SetGridTypeAtPos( _strikePos, GridType::MISS );
		return;
	}

	// Otherwise, find what ship has been affected.
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
				m_grid->SetGridTypeAtPos( _strikePos, GridType::HIT );
			}
			break;
		}
	}
}

/// <summary>
/// Returns true if all of the player ships have been destroyed i.e. the player lost
/// </summary>
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

/// <summary>
/// Randomly places each ship on the player grid.
/// </summary>
void Player::PlaceShipsRandomly()
{
	for ( unsigned int i = 0; i < ShipType::SHIPTYPE_COUNT; i++ )
	{
		while ( true )
		{
			int const shipLength = m_ships[i]->GetLength();
			ShipOrientation orientation = static_cast<ShipOrientation>( rand() % ShipOrientation::SHIPORIENTATION_COUNT );
			Vector2dInt startPosition = Vector2dInt();			
			
			// Generate a random startPosition, accounting for length and orientation.
			switch ( orientation )
			{
				case LEFT:
					startPosition.x = (rand() % g_gridWidth - shipLength) + shipLength;
					startPosition.y = rand() % g_gridHeight;
					break;
				case RIGHT:
					startPosition.x = ( rand() % g_gridWidth - shipLength );
					startPosition.y = rand() % g_gridHeight;
					break;
				case UP:
					startPosition.x = rand() % g_gridWidth;
					startPosition.y = ( rand() % g_gridHeight - shipLength ) + shipLength;
					break;
				case DOWN:
					startPosition.x = rand() % g_gridWidth;
					startPosition.y = ( rand() % g_gridHeight - shipLength );
					break;
				default:
					assert( false && "Unknown ShipOrientation" );
			}

			m_ships[i]->SetOrientation( orientation );
			m_ships[i]->SetPosition( startPosition );

			if ( TryPlaceShipOnGrid( static_cast<ShipType>( i ) ) )
			{
				break;
			}

			// Try again if we failed to place on the grid (e.g. if there was already another ship in this spot).
		}
	}
}

/// <summary>
/// Sets the grid type to ship for the relevant positions. Fails if position is out of bounds or overlaps 
/// with another ship. Returns true on success.
/// </summary>
/// <param name="_shipType"></param>
bool Player::TryPlaceShipOnGrid( ShipType _shipType )
{	
	if ( _shipType < static_cast<ShipType>( 0 ) || _shipType >= ShipType::SHIPTYPE_COUNT )
	{
		assert( false && "Invalid Ship Type" );
		return false;
	}

	const Ship* const ship = m_ships[static_cast<int>(_shipType)];

	// Test that the ship is within the grid
	Vector2dInt startPos, endPos;
	ship->GetShipBounds( startPos, endPos );
	bool inBounds = m_grid->IsPosInGridBounds( startPos ) && m_grid->IsPosInGridBounds( endPos );
	if ( !inBounds )
	{
		// Can't place here...
		return false;
	}

	// Test that the ship does not overlap another ship
	bool overlapsAnotherShip = false;
	Vector2dInt posIter = startPos;
	Vector2dInt delta = endPos - posIter;
	Vector2dInt clampedDelta = Vector2dInt(
		std::clamp( delta.x, -1, 1 ),
		std::clamp( delta.y, -1, 1 )
	);

	// Check each position one at a time
	for ( int i = 0; i < delta.Length(); i++ )
	{
		if ( m_grid->GetGridTypeAtPos( posIter ) == GridType::SHIP )
		{
			overlapsAnotherShip = true;
			break;
		}
		posIter += clampedDelta;
	}

	if ( overlapsAnotherShip )
	{
		// Can't place here...
		return false;
	}

	// Otherwise, its safe to place on the grid
	posIter = startPos;
	for (int i = 0; i < delta.Length(); i++)	
	{
		m_grid->SetGridTypeAtPos( posIter, GridType::SHIP );
		posIter += clampedDelta;
	}

	return true;
}

/// <summary>
/// Sets the GridType to SHIP_SUNK for each of the ship's positions. This is used by the ComputerPlayer
/// to know when to move on to a new target, and to provide visual distinciton for a destroyed ship.
/// </summary>
/// <param name="_shipType"></param>
void Player::MarkShipAsSunkOnGrid( ShipType _shipType )
{
	if ( _shipType < static_cast<ShipType>( 0 ) || _shipType >= ShipType::SHIPTYPE_COUNT )
	{
		assert( false && "Invalid Ship Type" );
		return;
	}
	const Ship* const ship = m_ships[_shipType];

	Vector2dInt startPos, endPos;
	ship->GetShipBounds( startPos, endPos );

	Vector2dInt posIter = startPos;
	Vector2dInt delta = endPos - posIter;
	Vector2dInt clampedDelta = Vector2dInt(
		std::clamp( delta.x, -1, 1 ),
		std::clamp( delta.y, -1, 1 )
	);
	for ( int i = 0; i < delta.Length(); i++ )
	{
		m_grid->SetGridTypeAtPos( posIter, GridType::SHIP_SUNK );
		posIter += clampedDelta;
	}
}


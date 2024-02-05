#pragma once

#include <string>
#include <assert.h>

#include "Vector.h"

/// <summary>
/// Declares for ship class and relevant enums/helper functions.
/// </summary>

class Ship;

enum ShipType
{
	PATROL_BOAT,
	SUBMARINE,
	DESTROYER,
	BATTLESHIP,
	AIRCRAFT_CARRIER,

	SHIPTYPE_COUNT
};

std::string static ShipTypeToString( ShipType _shipType )
{
	switch ( _shipType )
	{
		case PATROL_BOAT:
			return "Patrol Boat";
		case SUBMARINE:
			return "Submarine";
		case DESTROYER:
			return "Destroyer";
		case BATTLESHIP:
			return "Battleship";
		case AIRCRAFT_CARRIER:
			return "Aircraft Carrier";
		default:
			break;
	}
	assert( false && "Unkown ShipType" );
	return "Unknown Ship Type";
}

enum ShipOrientation
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	SHIPORIENTATION_COUNT
};

Vector2dInt static GetDirectionForShipOrientation( ShipOrientation _shipOrientation )
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
	assert( false && "Unkown ShipOrientation" );
	return Vector2dInt( 0, 0 );
}

std::string static ShipOrientationToString( ShipOrientation _shipOrientation )
{
	switch ( _shipOrientation )
	{
		case LEFT:
			return "Left";
		case RIGHT:
			return "Right";
		case UP:
			return "Up";
		case DOWN:
			return "Down";
		default:
			break;
	}
	assert( false && "Unkown ShipOrientation" );
	return "Unknown Ship Orientation";
}
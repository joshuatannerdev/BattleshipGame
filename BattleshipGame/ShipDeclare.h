#pragma once

#include <string>

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
	return "Unknown Ship Orientation";
}
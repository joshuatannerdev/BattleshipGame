#pragma once

#include "Vector.h"

enum ShipType
{
	PATROL_BOAT,
	SUBMARINE,
	DESTROYER,
	BATTLESHIP,
	AIRCRAFT_CARRIER,

	SHIPTYPE_COUNT
};

enum ShipOrientation
{	
	LEFT,
	RIGHT,
	UP,
	DOWN,

	SHIPORIENTATION_COUNT
};

class Ship
{
public:
	Ship( ShipType _shipType );
	~Ship();

private:
	Ship();

public:
	void SetOrientation( ShipOrientation _shipOrientation );
	void SetPosition( int _posX, int _posY );
	bool IsShipHit( int _posX, int _posY ) const;
	bool IsShipDestroyed() const;
	void GetShipBounds( Vector2dInt& o_startPos, Vector2dInt& o_endPos ) const;

private:
	ShipType m_shipType;
	ShipOrientation m_shipOrientation;
	Vector2dInt m_startPos;
	Vector2dInt m_endPos;
	int m_health;


};


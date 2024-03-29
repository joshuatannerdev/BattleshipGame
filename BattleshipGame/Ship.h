#pragma once

#include "ShipDeclare.h"
#include "Vector.h"

/// <summary>
/// Ship class.
/// </summary>
class Ship
{
public:
	Ship( ShipType _shipType );
	~Ship();

private:
	Ship();

public:
	void SetOrientation( ShipOrientation _shipOrientation );
	void SetPosition( const Vector2dInt& _pos );
	bool IsPosInShipBounds( const Vector2dInt& _pos ) const;
	void GetShipBounds( Vector2dInt& o_startPos, Vector2dInt& o_endPos ) const;
	bool StrikeShip();
	bool IsShipDestroyed() const;
	int GetLength() const;

private:
	void CacheEndPosition();

private:
	ShipType m_shipType;
	ShipOrientation m_shipOrientation;
	Vector2dInt m_startPos;
	Vector2dInt m_endPos;
	int m_health;
};
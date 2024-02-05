#pragma once

#include "ShipDeclare.h"
#include "Vector.h"

class Grid;

/// <summary>
/// Base Player class.
/// </summary>
class Player
{
public:
	Player();
	Player( int _xDrawOffset, bool _hideShipGridType );
	~Player();

private:
	void InitialisePlayer( int _xDrawOffset = 0, bool _hideShipGridType = false );

public:
	virtual Vector2dInt ChooseStrikePos( const Grid* const _opponentGrid ) = 0;
	virtual void PlaceShips();

	void DrawPlayerGrid() const;
	void StrikePlayerGrid( const Vector2dInt& _strikePos );
	bool CheckAllShipsDestroyed() const;
	const Grid* const GetGridReadOnly() const { return m_grid; }

protected:
	void PlaceShipsRandomly();
	bool TryPlaceShipOnGrid( ShipType _shipType );
	void MarkShipAsSunkOnGrid( ShipType _shipType );

protected:
	Ship* m_ships[ShipType::SHIPTYPE_COUNT];
	Grid* m_grid;
};
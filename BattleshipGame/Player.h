#pragma once

#include "ShipDeclare.h"
#include "Vector.h"

class Grid;

class Player
{
public:
	Player();
	~Player();

public:
	virtual Vector2dInt ChooseStrikePos(const Grid* const _opponentGrid) = 0;
	virtual void PlaceShips();

	void DrawPlayerGrid( int startPosX = 0, int startPosY = 0 ) const;
	void StrikePlayerGrid( Vector2dInt _strikePos );
	bool CheckAllShipsDestroyed() const;
	const Grid* const GetGridReadOnly() const { return m_grid; }

protected:
	void PlaceShipsRandomly();
	bool TryPlaceShipOnGrid( ShipType _shipType );
	void MarkShipAsSunkOnGrid( ShipType _shipType );

protected:
	Ship* m_ships[ShipType::SHIPTYPE_COUNT];
	Grid* m_grid;

private:

	bool m_hasPlacedShips;
};


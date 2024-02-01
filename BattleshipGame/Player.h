#pragma once

class Grid;

class Player
{
public:
	Player();
	~Player();

public:
	virtual void TakeTurn() = 0;
	virtual void PlaceShips();
	void DrawPlayerGrid( int startPosX = 0, int startPosY = 0 ) const;

protected:
	void PlaceShipsRandomly();

private:
	Grid* m_grid;
	bool m_hasPlacedShips;
};


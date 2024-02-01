#include "Player.h"
#include "Grid.h"

Player::Player()
	: m_hasPlacedShips(false)
{
	m_grid = new Grid();
}

Player::~Player()
{
	delete m_grid;
	m_grid = nullptr;
}

void Player::PlaceShips()
{
	PlaceShipsRandomly();
}

void Player::DrawPlayerGrid( int _startPosX, int _startPosY ) const
{
	m_grid->Draw( _startPosX, _startPosY );
}

void Player::PlaceShipsRandomly()
{
}

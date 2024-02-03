#pragma once
#include "Player.h"
class HumanPlayer :
    public Player
{
public:
    virtual Vector2dInt ChooseStrikePos( const Grid* const _opponentGrid );
    virtual void PlaceShips() override;
};


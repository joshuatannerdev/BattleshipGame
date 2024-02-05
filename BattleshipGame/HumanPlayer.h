#pragma once
#include "Player.h"

/// <summary>
/// HumanPlayer class. Supports player input for striking and ship placement.
/// </summary>
class HumanPlayer :
    public Player
{
public:
    virtual Vector2dInt ChooseStrikePos( const Grid* const _opponentGrid ) override;
    virtual void PlaceShips() override;
};
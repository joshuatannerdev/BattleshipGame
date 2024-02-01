#pragma once
#include "Player.h"
class HumanPlayer :
    public Player
{
public:
    virtual void TakeTurn();
    virtual void PlaceShips() override;
};


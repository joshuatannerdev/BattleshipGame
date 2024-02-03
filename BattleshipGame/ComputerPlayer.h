#pragma once
#include "Player.h"
class ComputerPlayer :
    public Player
{
public:
    ComputerPlayer();

public:
    virtual Vector2dInt ChooseStrikePos( const Grid* const _opponentGrid );

private:
    Vector2dInt m_lastStrikePos;
};


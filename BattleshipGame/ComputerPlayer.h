#pragma once
#include "Player.h"

/// <summary>
/// ComputerPlayer class. Supports basic AI to decide where to strike.
/// </summary>
class ComputerPlayer :
    public Player
{
public:
    ComputerPlayer();

public:
    virtual Vector2dInt ChooseStrikePos( const Grid* const _opponentGrid );

private:
    // Used to figure out where to strike next.
    Vector2dInt m_lastSuccesfulStrikePos;
};
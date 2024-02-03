#include "ComputerPlayer.h"
#include "Grid.h"

ComputerPlayer::ComputerPlayer()
	: Player()
	, m_lastStrikePos( 0, 0 )
{
}

Vector2dInt ComputerPlayer::ChooseStrikePos( const Grid* const _opponentGrid )
{
	Vector2dInt strikePos;

	if ( _opponentGrid->GetGridTypeAtPos( m_lastStrikePos.x, m_lastStrikePos.y ) == GridType::HIT )
	{
		// Our last strike hit a ship but did not sink it. Focus on destroying this one.

		// Check each of the four directions around this point - have we hit any others?
		// If so, we know the direction we should strike in. Otherwise, pick a random direction.
	}


	return strikePos;
}

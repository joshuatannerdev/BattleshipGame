#pragma once

struct Vector2dInt
{
	Vector2dInt()
		:x(0)
		,y(0)
	{};
	Vector2dInt(int _x, int _y)
		:x(_x)
		,y(_y)
	{}
	Vector2dInt operator*( const Vector2dInt& _rhs )
	{
		Vector2dInt result( this->x * _rhs.x, this->y * _rhs.y );
		return result;
	}
	Vector2dInt operator+( const Vector2dInt& _rhs )
	{
		Vector2dInt result( this->x + _rhs.x, this->y + _rhs.y );
		return result;
	}

	Vector2dInt operator*( const int _rhs )
	{
		Vector2dInt result( this->x * _rhs, this->y * _rhs );
		return result;
	}

	int x;
	int y;
};
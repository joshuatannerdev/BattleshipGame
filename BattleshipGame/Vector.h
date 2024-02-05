#pragma once
#include <math.h>

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
	bool operator==( const Vector2dInt& _rhs ) const { return this->x == _rhs.x && this->y == _rhs.y; }
	bool operator!=( const Vector2dInt& _rhs ) const { return this->x != _rhs.x || this->y != _rhs.y; }
	bool operator>=( const Vector2dInt& _rhs ) const { return this->x >= _rhs.x && this->y >= _rhs.y; }
	bool operator<=( const Vector2dInt& _rhs ) const { return this->x <= _rhs.x && this->y <= _rhs.y; }

	Vector2dInt operator*( const Vector2dInt& _rhs ) { return Vector2dInt( this->x * _rhs.x, this->y * _rhs.y ); }
	Vector2dInt operator+( const Vector2dInt& _rhs ) { return Vector2dInt( this->x + _rhs.x, this->y + _rhs.y ); }	
	Vector2dInt operator-( const Vector2dInt& _rhs ) { return Vector2dInt( this->x - _rhs.x, this->y - _rhs.y ); }
	Vector2dInt operator*( const int _rhs ) { return Vector2dInt( this->x * _rhs, this->y * _rhs ); }
	Vector2dInt& operator+=( const Vector2dInt& _rhs ) {
		this->x += _rhs.x;
		this->y += _rhs.y;
		return *this;
	}
	Vector2dInt& operator*=( const Vector2dInt& _rhs ) {
		this->x *= _rhs.x;
		this->y *= _rhs.y;
		return *this;
	}
	Vector2dInt& operator*=( const int _rhs ) {
		this->x *= _rhs;
		this->y *= _rhs;
		return *this;
	}
	Vector2dInt operator=( const Vector2dInt& _rhs ) {
		this->x = _rhs.x;
		this->y = _rhs.y;
		return *this;
	}


	int Length() const { return static_cast<int>(sqrt( pow( x, 2 ) + pow( y, 2 ) )); }

	int x;
	int y;
};
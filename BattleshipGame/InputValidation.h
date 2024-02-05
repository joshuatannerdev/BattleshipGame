#pragma once

#include <iostream>
#include <string>
#include <sstream>

/// <summary>
/// Helper funciton - shortened getline call.
/// </summary>
static std::string GetLine() {
	std::string input;
	std::getline( std::cin, input );
	return input;
}

/// <summary>
/// Return true if all characters are digits.
/// </summary>
static bool IsDigit( std::string const& _string )
{
	if ( _string.empty() )
	{
		return false;
	}
	for ( unsigned int i = 0; _string[i] != '\0'; i++ )
	{
		if ( !isdigit( _string[i] ) )
		{
			return false;
		}
	}
	return true;
}
static bool IsDigitInRange( std::string const& _string, int _inclMin, int _inclMax )
{
	if ( !IsDigit( _string ) )
	{
		return false;
	}

	int input = atoi( _string.c_str() );
	return input >= _inclMin && input <= _inclMax;
}
static bool IsAlpha( std::string const& _string )
{
	if ( _string.empty() )
	{
		return false;
	}

	for ( unsigned int i = 0; _string[i] != '\0'; i++ )
	{
		if ( !isalpha( _string[i] ) )
		{
			return false;
		}
	}
	return true;
}
static bool IsAlphaInRange( std::string const& _string, char _inclMin = CHAR_MIN, char _inclMax = CHAR_MAX )
{
	if ( !IsAlpha( _string ) )
	{
		return false;
	}

	char input =  toupper( _string.c_str()[0] );
	char min = toupper( _inclMin );
	char max = toupper( _inclMax );
	return input >= min && input <= max;
}

static int GetInputInt( int _inclMin = INT_MIN, int _inclMax = INT_MAX )
{
	std::string inputString = GetLine();
	while ( !IsDigitInRange( inputString, _inclMin, _inclMax ) )
	{
		std::cout << "Invalid...." << std::endl;
		inputString = GetLine();
	}
	return atoi( inputString.c_str() );
}
static char GetInputChar( char _inclMin = CHAR_MIN, char _inclMax = CHAR_MAX )
{
	std::string inputString = GetLine();
	while ( !IsAlphaInRange( inputString, _inclMin, _inclMax ) )
	{
		std::cout << "Invalid...." << std::endl;
		inputString = GetLine();
	}
	const char* input = inputString.c_str();
	return input[0];
}
#pragma once

#include <string>

struct Player
{
	Player() = default;
	Player(const std::string& aName)
	{
		name = aName;
	}

	std::string name = "";
};

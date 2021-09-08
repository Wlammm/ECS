#pragma once

#include "Types.hpp"
#include <set>

class System
{
public:
	virtual void Init() = 0;
	virtual void Update() = 0;

	std::set<Entity> myEntities;
};
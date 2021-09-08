#pragma once

#include "System.hpp"

class PlayerSystem : public System
{
public:
	void Init() override;
	void Update() override;
};
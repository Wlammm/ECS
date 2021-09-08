#pragma once

#include "System.hpp"

class WriterSystem : public System
{
public:
	void Init() override;
	void Update() override;
};
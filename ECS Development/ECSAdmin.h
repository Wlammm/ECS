#pragma once

#include <vector>
#include <array>
#include <typeindex>
#include <map>
#include <iostream>
#include "ObjectPool.hpp"
#include "SSet.h"
#include <any>
#include "Component.h"

using Entity = unsigned int;
#define MaxComponentCount 128

class ECSAdmin
{
public:
	ECSAdmin() = default;
	~ECSAdmin() = default;

private:


};

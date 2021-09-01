#include <iostream>
#include "ECSAdmin.h"
#include "ObjectPool.hpp"

#include "Component.h"

class TEstCOmponent : public Component
{

};

int main()
{
	ECSAdmin admin;

	TEstCOmponent* comp{};

	admin.AddComponent<int>(0, comp);

	return 0;
}
#include <iostream>
#include "ECSAdmin.h"

int main()
{
	ECSAdmin admin;

	int i = 3;
	admin.AddComponent<int>(0, i);


	return 0;
}
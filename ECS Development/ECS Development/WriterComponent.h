#pragma once

#include <string>

struct Writer
{
	Writer() = default;
	Writer(const std::string& someText)
	{
		text = someText;
	}

	std::string text = "";
};
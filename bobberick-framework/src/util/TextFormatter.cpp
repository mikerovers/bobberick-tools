#include "TextFormatter.h"

std::string TextFormatter::addSpaces(const std::string& string, const int goalChars, const bool leading)
{
	std::string spaces;
	for (int i = string.length(); i < goalChars; i++)
	{
		spaces += " ";
	}
	if (leading)
	{
		return spaces + string;
	}
	return string + spaces;
}
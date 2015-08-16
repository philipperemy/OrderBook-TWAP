#include <fstream>
#include <vector>
#include <stdexcept>

#include "Utils.h"

std::vector<std::string> trading::readFile(const std::string& filename)
{
	std::ifstream is(filename.c_str());
	if (!is)
	{
		throw std::runtime_error("File not found.");
	}
	std::string str;
	std::vector<std::string> lines;
	while (!is.eof())
	{
		std::getline(is, str);
		if(!str.empty())
        {
            lines.push_back(str);
        }
	}
	is.close();
	return lines;
}

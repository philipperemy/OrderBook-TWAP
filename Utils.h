#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

namespace trading {

    std::vector<std::string> readFile(const std::string& filename);

    std::vector<std::string> tokenize(const std::string& str, const char& delimiter);

}

inline std::vector<std::string> trading::tokenize(const std::string& str, const char& delimiter)
{
	std::vector<std::string> fields;
	std::istringstream is(str);
	std::string s;
	while (std::getline(is, s, delimiter))
    {
		fields.push_back(s);
	}
	return fields;
}

#endif /* UTILS_H_ */

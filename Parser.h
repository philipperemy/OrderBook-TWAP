#ifndef PARSER_H_
#define PARSER_H_

#include <sstream>
#include <iostream>
#include <vector>

#include "LimitOrder.h"
#include "Exceptions.h"
#include "Utils.h"

namespace trading
{
    class Parser
    {
        public:
        static LimitOrder parse(const std::string& msg);
    };
}


inline trading::LimitOrder trading::Parser::parse(const std::string& msg)
{
	std::vector<std::string> fields = tokenize(msg, ' ');

	LimitOrder order;
	order.timestamp = atol(fields.at(0).c_str());
    order.id = fields.at(2);

    std::string orderType = fields.at(1);
	if (orderType.compare("I") == 0)
    {
        //Insert
        order.type = add;
        order.price = atof(fields.at(3).c_str());
    }
    else if(orderType.compare("E") == 0)
    {
        //Erase
        order.type = cancel;
    }
    else
    {
        throw BadParse();
    }

	return order;
}

#endif /* PARSER_H_ */

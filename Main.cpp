#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <typeinfo>

#include "LimitOrder.h"
#include "Parser.h"
#include "Utils.h"
#include "OrderBook.h"

int main(int argc, char* argv[])
{
	try
	{
        if(argc != 2)
        {
            std::cerr << "Error with program arguments. Expected:" << std::endl;
			std::cerr << "./Program feed.txt" << std::endl;
			return EXIT_FAILURE;
        }

        std::vector<std::string> msgs = trading::readFile(argv[1]);
        std::vector<trading::LimitOrder> limitOrders;
        for(std::vector<std::string>::iterator it = msgs.begin(); it != msgs.end(); ++it)
        {
            std::cout << *it << std::endl;
            trading::LimitOrder order ( trading::Parser::parse(*it) );
            limitOrders.push_back(order);
        }

        trading::OrderBook orderbook;
        double twap = orderbook.computeTWAP(limitOrders);
        std::cout << "TWAP = " << twap << std::endl;
    }
	catch (const std::exception& e)
    {
        std::cerr << "Exception raised: " << e.what() << ". Program will exit";
        return EXIT_FAILURE;
    }

	return EXIT_SUCCESS;
}


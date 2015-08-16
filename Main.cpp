#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <typeinfo>

#include "MarketDataProvider.h"
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

        trading::MarketDataProvider mdp;
        mdp.readMarketDataFile(argv[1]);

        std::vector<trading::LimitOrder> limitOrders;
        while (mdp.hasNextMessage())
        {
            std::string msg (mdp.nextMessage());
            std::cout << msg << std::endl;
            trading::LimitOrder order ( trading::Parser::parse(msg) );
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


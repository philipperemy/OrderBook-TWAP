#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <typeinfo>

#include "MarketDataProvider.h"
#include "LimitOrder.h"
#include "Parser.h"
#include "Exceptions.h"
#include "Utils.h"
#include "OrderBook.h"


int main(int argc, char* argv[]) {

	try
	{
		std::cout << std::setiosflags(std::ios::fixed); // to show amounts as XXXX.XX

		std::cout << "Starting Program" << std::endl;

        if(argc != 2)
        {
            std::cerr << "Error with program arguments. Expected:" << std::endl;
			std::cerr << "./Program feed.txt" << std::endl;
			return EXIT_FAILURE;
        }

        try
        {
            std::cout << "File is: " << argv[1] << std::endl;
            trading::MarketDataProvider mdp;
            mdp.readMarketDataFile(argv[1]);

            std::vector<trading::LimitOrder> limitOrders;
            while (mdp.hasNextMessage())
            {
                // "Receive" new message
                std::string msg;
                msg = mdp.nextMessage();
				std::cout << msg << std::endl;

                trading::LimitOrder order;
                try
                {
                    order = trading::Parser::parse(msg);
                    limitOrders.push_back(order);
                    //The timestamps are monotonically increasing.
                }
                catch (const trading::ParseException&)
                {
                    std::cerr << "Skipping this message due to parsing errors: " << msg << std::endl;
                    continue;
                }
            }

            trading::OrderBook orderbook;
            double twap = orderbook.processOrders(limitOrders);
            std::cout << "twap = " << twap << std::endl;
        }
        catch (const trading::BadMarketDataFile& e)
        {
            FILE_LOG(logERROR) << "Error opening the market data file";
            return EXIT_FAILURE;
        }

	}
	catch (const trading::Exception& e)
	{
		FILE_LOG(logERROR) << "Exception: " << typeid(e).name();
	}

	return EXIT_SUCCESS;
}


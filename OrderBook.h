#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "LimitOrder.h"
#include <vector>
#include <map>

namespace trading
{
    class OrderBook
    {
        public:
            double computeTWAP(std::vector<trading::LimitOrder> orders);
        private:
            double getHighestPriceOfLimitOrders(long int maxTimestamp);
            std::map<std::string, trading::LimitOrder*> restingOrderMap_;
    };
}

#endif // ORDERBOOK_H

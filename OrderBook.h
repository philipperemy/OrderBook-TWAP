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
            void insertOrder(LimitOrder* order);
            void eraseOrder(std::string id);

            std::map<std::string, trading::LimitOrder*> restingOrderMap_;
    };
}

#endif // ORDERBOOK_H

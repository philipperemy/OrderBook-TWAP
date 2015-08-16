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
            double processOrders(std::vector<trading::LimitOrder> orders);
        protected:
        private:
            double getHighestPriceOfLimitOrders(long int maxTimestamp);
            std::map<trading::LimitOrder::Id, trading::LimitOrder*> orderMap_;
    };
}

#endif // ORDERBOOK_H

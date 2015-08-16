#include "OrderBook.h"
#include <math.h>

double trading::OrderBook::computeTWAP(std::vector<trading::LimitOrder> orders)
{
    if(orders.empty())
    {
        return NAN;
    }

    //Fill resting order map first
    for(std::vector<trading::LimitOrder>::iterator it = orders.begin(); it != orders.end(); ++it)
    {
        if(it->type == add)
        {
            insertOrder(&(*it));
        }
    }

    //Fill Map<Timestamp, Highest Resting Price>
    std::map<long int, double> highestPriceMap;
    for(std::vector<trading::LimitOrder>::iterator it = orders.begin(); it != orders.end(); ++it)
    {
        //Order has been cancelled. Remove it from the resting orders map.
        if(it->type == cancel)
        {
            eraseOrder(it->id);
        }

        long int currentTimestamp = it->timestamp;
        highestPriceMap[currentTimestamp] = getHighestPriceOfLimitOrders(currentTimestamp); //highest order price up to now.
    }

    double twap = 0;
    for(std::map<long int, double>::iterator it = highestPriceMap.begin(); it != highestPriceMap.end(); it++)
    {
        long int lastTimestamp = it->first;
        if(it != highestPriceMap.end())
        {
            //std::next(it, 1); Can be done with C++11 with next!
            it++; long newVal = it->first-lastTimestamp; it--;
            twap += it->second * newVal;
        }
    }

    //The timestamps are monotonically increasing.
    long int firstTimestamp = orders.front().timestamp;
    long int finalTimestamp = orders.back().timestamp;
    twap /= (finalTimestamp - firstTimestamp);
    return twap;
}

void trading::OrderBook::insertOrder(LimitOrder* order)
{
    restingOrderMap_[order->id] = &(*order);
}

void trading::OrderBook::eraseOrder(std::string id)
{
    restingOrderMap_.erase(id);
}

double trading::OrderBook::getHighestPriceOfLimitOrders(long int maxTimestamp)
{
    double highestPrice = 0;
    for (std::map<std::string, trading::LimitOrder*>::iterator it = restingOrderMap_.begin(); it != restingOrderMap_.end(); it++)
    {
        double currentPrice = it->second->price;
        if(currentPrice > highestPrice && it->second->timestamp <= maxTimestamp)
        {
            highestPrice = currentPrice;
        }
    }
    return highestPrice;
}

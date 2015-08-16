#include "OrderBook.h"


double trading::OrderBook::processOrders(std::vector<trading::LimitOrder> orders)
{
    std::cout << "______________________" << std::endl;

    long int firstTimestamp = orders.front().timestamp;
    long int finalTimestamp = orders.back().timestamp;

    //Fill map first
    for(std::vector<trading::LimitOrder>::iterator it = orders.begin(); it != orders.end(); ++it)
    {
        if(it->type == add)
        {
            orderMap_[it->id] = &(*it); //Pointer to the elements
        }
        else
        {
            //Assume that each cancel order has been previously booked.
            LimitOrder* addOrder = orderMap_[it->id];
            //std::cout << it->timestamp - addOrder->timestamp << " " << (*addOrder).price << std::endl;
        }
    }

    //std::cout << "______________________" << std::endl;

    //Let's go. Iterate over all orders
    std::map<long int, double> priceMap;
    for(std::vector<trading::LimitOrder>::iterator it = orders.begin(); it != orders.end(); ++it)
    {
        if(it->type == cancel)
        {
            orderMap_.erase(it->id);
        }
        long int currentTimestamp = it->timestamp;
        double highestPrice = getHighestPriceOfLimitOrders(currentTimestamp); //highest order price up to now.
        priceMap[currentTimestamp] = highestPrice;
    }

    double twap = 0;
    for(std::map<long int, double>::iterator it = priceMap.begin(); it != priceMap.end(); it++)
    {
        long int lastTimestamp = it->first;
        if(it != priceMap.end())
        {
            it++;
            long newVal = it->first-lastTimestamp;
            it--;
            twap += it->second * newVal;
        }
        //std::cout << " " << it->first << " " << it->second << std::endl;
    }

    twap /= (finalTimestamp - firstTimestamp);
    return twap;
}

double trading::OrderBook::getHighestPriceOfLimitOrders(long int maxTimestamp)
{
    double highestPrice = 0;
    for (std::map<trading::LimitOrder::Id, trading::LimitOrder*>::iterator it = orderMap_.begin(); it != orderMap_.end(); it++)
    {
        double currentPrice = it->second->price;
        if(currentPrice > highestPrice && it->second->timestamp <= maxTimestamp)
        {
            highestPrice = currentPrice;
        }
    }
    return highestPrice;
}

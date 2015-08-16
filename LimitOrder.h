#ifndef MARKETORDER_H_
#define MARKETORDER_H_

#include <iostream>
#include <string>
#include <sstream>

namespace trading
{
    enum OrderType
    {
        add,
        cancel
    };

    // Limit Order
    struct LimitOrder
    {
        std::string         id;
        unsigned long int   timestamp; //ms
        OrderType           type;
        double              price; //optional

    };

}

#endif /* MARKETORDER_H_ */

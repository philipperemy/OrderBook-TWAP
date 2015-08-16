#ifndef MARKETORDER_H_
#define MARKETORDER_H_

#include <iostream>
#include <string>
#include <sstream>

namespace trading {

enum OrderType {add, cancel};

// Market Order
struct LimitOrder
{
	std::string toString() const;

	typedef unsigned long int Price;
	typedef std::string Id;

	OrderType type;
	unsigned long int timestamp; //ms
	Id id;
	Price price;

};

}

inline std::string trading::LimitOrder::toString() const
{
	std::stringstream oss;

	if (type == add) {
		oss << "AddOrder: ts = " << timestamp << " id = " << id << " " << " price = " << price;
	} else {
		oss << "ReduceOrder: ts = " << timestamp << " id = " << id;
	}
	return oss.str();
}

#endif /* MARKETORDER_H_ */

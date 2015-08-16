#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

namespace trading {

/*
 * Exception Root
 */

class Exception {
};


/*
 * General Exceptions
 */

// Index out of bounds
class OutOfBounds : public Exception {
};

/*
 * Market data exceptions
 */

class BadMarketDataFile : public Exception {
};

/*
 * Parse Exceptions
 */

// Parsing exception
class ParseException : public Exception {
};

// Parse exception
class BadParse: public ParseException {
};

// Invalid ticker
class BadTicker: public ParseException {
};



/*
 * Order Book exceptions
 */

// Root
class OrderBookException : public Exception {
};

// Order type is not Add or Reduce
class BadOrderType : public OrderBookException {
};

// Order type is not Buy or Sell
class BadOrderSide : public OrderBookException {
};

// Bad order size
class BadOrderSize : public OrderBookException {
};

// Duplicate Order ID
class DuplicateOrderId : public OrderBookException {
};

// Reduce message for an ID that we don't know
class AttempToReduceNonexistantOrder : public OrderBookException {
};

}

#endif /* EXCEPTIONS_H_ */


#ifndef MARKETDATAPROVIDER_H_
#define MARKETDATAPROVIDER_H_

#include <string>
#include <vector>

namespace trading
{
    class MarketDataProvider
    {
        public:

            void readMarketDataFile(const std::string& filename);
            bool hasNextMessage();
            const std::string& nextMessage();

        private:

            std::string filename_ = std::string();
            std::vector<std::string> messages_ = std::vector<std::string>();
            std::vector<std::string>::iterator cur_ = messages_.begin();
    };
}


#endif /* MARKETDATAPROVIDER_H_ */

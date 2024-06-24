#include <string>

namespace algorithms::dp
{
    int getMinOperationsToConvertString(std::string from, std::string to)
    {
        if(from.empty())
          return to.size() - 1;

        if(to.empty())
          return from.size() - 1;


        return 0;
    }
}
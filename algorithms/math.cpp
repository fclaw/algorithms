#include <string>
#include <iostream>

using ll = long long;

namespace algorithms::mathematics
{
    // two n-digit positive integers x and y
    // the product x · y
    // basic assumption: n is the power of 2
    // x = (10 ^ n) / 2 * a + b
    // y = (10 ^ n) / 2 * c + d
    ll multiplyRec(int n, int x, int y)
    {
        if(n == 1)
          return x * y;
        
        auto sx = std::to_string(x);
        auto sy = std::to_string(y);

        auto a = sx.substr(0, n / 2);
        auto b = sx.substr(n / 2, n / 2); 
       
        auto c = sy.substr(0, n / 2);
        auto d = sy.substr(n / 2, n / 2); 
       
        return 
           std::pow(10, n) * multiplyRec(n / 2, std::stoi(a), std::stoi(c)) +
           std::pow(10, n / 2) * (multiplyRec(n / 2, std::stoi(a), std::stoi(d)) + multiplyRec(n / 2, std::stoi(b), std::stoi(c))) +
           multiplyRec(n / 2, std::stoi(b), std::stoi(d));
    }
}
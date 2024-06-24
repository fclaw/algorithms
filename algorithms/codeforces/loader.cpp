#include <iostream>
#include "erasingZeroes.cpp"


int main()
{
    int n;
    std::cin >> n;
    std::string tests[n];
    
    for (int i = 0; i < n; i++)
        std::cin >> tests[i];

    for (auto t : tests)
        std::cout << algorithms::codeforces::eraseZero(t) << std::endl;

    return 0;  
}
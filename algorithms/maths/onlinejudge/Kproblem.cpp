#include <optional>
#include <iostream>

namespace algorithms::maths::onlinejudge::k_problem
{
    /** https://onlinejudge.org/external/100/10025.pdf */
    int n;
    void minN(int i, int target, int sum) {}
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          std::freopen(file.value(), "r", stdin);
        int tc;
        std::cin >> tc;
        std::cin.ignore();
        while(--tc >= 0)
        {
            int k;
            std::cin >> k;
            minN(1, k, 0);
            std::cout << n << std::endl;
            std::cin.ignore();
        }
    }
}
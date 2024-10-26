#include <optional>
#include <iostream>

namespace algorithms::maths::onlinejudge::steps
{
    /** https://onlinejudge.org/external/8/846.pdf, 
     * uses the sum of arithmetic progression formula,
     * What is the minimum number of steps in order to get from x to y? 
     * The length of the first and the last step must be 1.
     * The length of a step must be nonnegative and can be by one bigger than, equal to, or by one smaller 
     * than the length of the previous step  */
    int minSteps(int s, int e) { return 0; }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          std::freopen(file.value(), "r", stdin);
        int tc;
        std::cin >> tc;
        while(--tc >= 0)
        {
            int s, e;
            std::cin >> e >> e;
            std::cout << minSteps(s, e) << std::endl;
        }
    }
}
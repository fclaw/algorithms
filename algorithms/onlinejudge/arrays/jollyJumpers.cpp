#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <vector>
#include <bitset>

typedef std::vector<int> vi;

namespace algorithms::onlinejudge::arrays::jolly_jumpers
{
    // https://onlinejudge.org/external/100/10038.pdf,
    // sequence of n > 0 integers is called a jolly jumper if the absolute values of the difference between
    // successive elements take on all the values 1 through n − 1
    // use 1D boolean flags to check [1 .. n − 1]
    const size_t N = 3000; 
    bool isJolly(int n, const vi& nums) 
    {
        bool ans = true;
        std::bitset<N> full_set;
        for(int i = 1; i < nums.size(); i++)
        {
            int diff = std::abs(nums[i] - nums[i - 1]);
            if(diff >= n || full_set[diff]) { ans = false; break; }
            full_set.set(diff);
        }

        return ans = (full_set.count() == n - 1);
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        std::string line; 
        while (std::getline(std::cin, line) && !line.empty()) 
        { // Read until empty line
           std::stringstream ss(line);
           int num, n, i = 0;
           ss >> n;
           vi numbers = vi(n);
           while (ss >> num) 
             numbers[i++] = num;
           std::cout << (isJolly(n, numbers) ? "Jolly" : "Not jolly") << std::endl;
        }
    }
}
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>


typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<std::string> vs;

namespace algorithms::onlinejudge::complete_search::stamps
{
    /** https://onlinejudge.org/external/1/165.pdf, requires some DP too; can be pre-calculated 
     * This has been analysed by government mathematicians who have derived a formula for n(h, k), where
     * h is the number of stamps that may be attached to a document, k is the number of denominations of
     * stamps available, and n is the largest attainable value in a continuous sequence starting from $1. For
     * instance, if h = 3, k = 2 and the denominations are $1 and $4, we can make all the values from $1 to
     * $6 (as well as $8, $9 and $12). However with the same values of h and k, but using $1 and $3 stamps
     * we can make all the values from $1 to $7 (as well as $9). This is maximal, so n(3, 2) = 7.
    */
    int H, K;
    const size_t MAX_DENOM = 32;
    const size_t MAX_TARGET = 101;
    bool backtrack(int k, int target, const vi& xs)
    {
        if(target < 0 || (k == 0 && target > 0)) 
          return false;
        if(target == 0) 
          return true;

        bool isReachable = false;
        for(int i = 0; i < xs.size(); i++)
          isReachable |= backtrack(k - 1, target - xs[i], xs);
        return isReachable;
    }
    std::string toString(const vi& xs)
    {
        std::string s;
        for(int x : xs) 
          s += std::to_string(x) + " ";
        s.pop_back();
        return s;
    }
    vvi genDenominations()
    {
        vi xs(MAX_DENOM);
        std::iota(xs.begin(), xs.end(), 2); // fills with 2, 3, ... , n - 1
        vi mask(MAX_DENOM);
        for (int t = MAX_DENOM - K + 1; t < MAX_DENOM; mask[t++] = 1);
        vvi denominations;
        do
        {
            vi set = {1};
            for(int i = 0; i < mask.size(); i++)
              if(mask[i]) set.push_back(xs[i]);
              denominations.push_back(set);
        }while (std::next_permutation(mask.begin(), mask.end()));
        return denominations;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
          
        while(std::cin >> H >> K && H && K)
        {
            vs targets(MAX_TARGET);
            // the most heaviest part, 
            // needs optimizing or completely different tack ought to be applied
            // time complexity: C(MAX_DENOM, K), K = 8 C(50, 8) ~
            vvi xxs = genDenominations();
            for(auto xs : xxs)
            {
                bool canExtened = true;
                for(int t = 1; t < MAX_TARGET; t++)
                {
                    canExtened &= backtrack(H, t, xs);
                    if(!canExtened) break;
                    if(targets[t].empty() ||
                       targets[t] > toString(xs))
                      targets[t] = toString(xs);
                }
            }

            int i = 1;
            while(!(targets[i].empty())) i++;
            std::cout << targets[--i] << " -> " << i << std::endl;
        }          
    }
}
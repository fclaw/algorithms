#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>


typedef std::vector<std::string> vs;


namespace algorithms::onlinejudge::complete_search::hamming
{
    /** https://onlinejudge.org/external/7/729.pdf, 
     * generate all possible bit strings  */
    const size_t MAX = 16;
    void backtrack(int length, int diff, int i, int val, vs& strings) 
    {
        if(__builtin_popcount(val) == diff)
        {
            std::string res(length, '0');
            for (int j = 0; j < length; j++)
              if (val & (1 << j)) res[j] = '1';
            strings.push_back(res);
            return;
        }

        for(int j = i; j < length; j++)
          backtrack(length, diff, j + 1, val | (1 << j), strings);
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
         
        int tc;
        std::cin >> tc;
        std::cin.ignore();
        while(tc--)
        {
            vs strings;
            int length, diff;
            std::cin >> length >> diff;
            int tmp = 0;
            backtrack(length, diff, 0, tmp, strings);
            std::sort(strings.begin(), strings.end());
            for(auto s : strings) std::cout << s << std::endl;
            if(tc) std::cout << std::endl;
        }
    }
}
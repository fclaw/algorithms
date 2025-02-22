#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <map>
#include <vector>



typedef std::map<int, int> mii;
typedef std::vector<int> vi;


namespace algorithms::onlinejudge::bst::snow_flakes
{
    /** https://onlinejudge.org/external/115/11572.pdf
     * it's a thoroughly disguised well-known problem of the longest contiguous array
     * Given the constraint of 10⁹ for snowflake IDs, a map (ordered map) 
     * should be preferred over a hash map (unordered map/hash table) 
     * due to the high probability of collisions in hash functions. */
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        vi flakes;
        mii last_index;
        std::cin >> tc;
        while(tc--)
        {
            flakes.clear();
            last_index.clear();
            int N;
            std::cin >> N;
            flakes.resize(N);
            for(int i = 0; i < N; i++) 
              std::cin >> flakes[i];

            int max_length = 0;
            int left_ptr = 0;
            int right_ptr = 0;
            while(right_ptr < N)
            {
                // expand right ptr until a duplicate is encountered
                while(right_ptr < N && 
                      last_index.find(flakes[right_ptr]) ==
                      last_index.end())
                { last_index[flakes[right_ptr]] = right_ptr; right_ptr++; }

                auto it = last_index.find(flakes[right_ptr]); 
                if(right_ptr < N &&
                    it != last_index.end() &&
                   (*it).second < left_ptr)
                  last_index[flakes[right_ptr]] = right_ptr;
                else
                {
                    max_length = std::max(max_length, right_ptr - left_ptr);
                    left_ptr = last_index[flakes[right_ptr]] + 1;
                    last_index[flakes[right_ptr]] = right_ptr;
                }
                right_ptr++;
            }
            std::cout << max_length << std::endl;
        }
    }
}
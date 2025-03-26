#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <bitset>
#include <unordered_set>
#include <unordered_map>
#include <tuple>


struct TupleHash {
    template<typename T>
    std::size_t operator()(const T& t) const {
        return std::apply([](auto&&... args) {
            std::size_t seed = 0;
            (..., (seed ^= std::hash<std::decay_t<decltype(args)>>{}(args) + 0x9e3779b9 + (seed << 6) + (seed >> 2)));
            return seed;
        }, t);
    }
};

typedef long long ll;
typedef std::unordered_set<ll> sl;

namespace algorithms::onlinejudge::complete_search::bishop
{
    /** https://onlinejudge.org/external/8/861.pdf, 
     * backtracking with pruning as in 8-queens recursive backtracking solution; 
     * then pre-calculate the results  */
    int SIZE, BISHOPS;
    const int MAX_SIZE = 8;
    const size_t MAX_BIT = 2 * MAX_SIZE - 1;
    std::bitset<MAX_BIT> rw, ld, rd;
    bool checkPlacement(int c, int r) 
    { return !ld.test(r - c + MAX_SIZE - 1) && !rd.test(r + c); }
    void bits_set(int r, int c, bool flag) 
    { ld.set(r - c + MAX_SIZE - 1, flag); rd.set(r + c, flag); }
    sl bishops_map;
    std::unordered_map<std::tuple<int, int, int, ll>, int, TupleHash> memo;
    int backtrack(int r, int c, int bishops, ll mask)
    {
        int remaining = (SIZE - r) + (SIZE - c - 1) * SIZE;
        if (remaining < (BISHOPS - bishops))
          return 0;
  
        if(bishops == BISHOPS)
          if(!bishops_map.count(mask))
          { bishops_map.insert(mask); return 1; }
          else return 0;

         auto key = std::make_tuple(r, c, bishops, mask);
         if(memo.count(key)) return memo[key];

        int ways = 0;
        for(int i = r; i < SIZE; i++)
        { 
            for(int j = c; j < SIZE; j++)
            {
                int pos = i * SIZE + j;
                if(!checkPlacement(j, i))
                  continue;
        
                bits_set(i, j, true);
                ways += backtrack(i + 1, j, bishops + 1, mask | (1LL << pos));
                ways += backtrack(0, j + 1, bishops + 1, mask | (1LL << pos));
                bits_set(i, j, false);
            }
            c = 0;
        }
        return memo[key] = ways;
    }

    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        while(std::cin >> SIZE >> BISHOPS)
        {
            if(!BISHOPS && !SIZE)
              break;
            
            memo.clear();
            bishops_map.clear();
            std::cout << backtrack(0, 0, 0, 0) << std::endl;
        } 
    }
}
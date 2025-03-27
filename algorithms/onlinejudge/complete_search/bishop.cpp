#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <bitset>
#include <unordered_map>
#include <limits>



typedef long long ll;
typedef std::vector<ll> vl;

namespace algorithms::onlinejudge::complete_search::bishop
{
    /** https://onlinejudge.org/external/8/861.pdf, 
     * backtracking with pruning as in 8-queens recursive backtracking solution; 
     * then pre-calculate the results  */
    int SIZE, BISHOPS;
    int TOTAL_DIAGONALS;  // = 13
    const int MAX_SIZE = 8;
    uint64_t ld = 0, rd = 0;
    bool checkPlacement(int c, int r) 
    { return !(ld & (1 << (r - c + MAX_SIZE - 1))) && !(rd & (1 << (r + c)));  }
    void occupied_diagonals(int r, int c) 
    { 
        ld |= (1 << (r - c + MAX_SIZE - 1));
        rd |= (1 << (r + c));
    }
    void relieve_diagonals(int r, int c)
    {
        ld &= ~(1 << (r - c + MAX_SIZE - 1));
        rd &= ~(1 << (r + c));
    }
    int backtrack(int idx, int bishops)
    {

        int mask = (1 << TOTAL_DIAGONALS) - 1;  // e.g., if TOTAL_DIAGONALS = 13 → 0b0001_1111_1111_1111
        int used_ld = __builtin_popcount(ld & mask);
        int used_rd = __builtin_popcount(rd & mask);

        int free_ld = TOTAL_DIAGONALS - used_ld;
        int free_rd = TOTAL_DIAGONALS - used_rd;

        int free_diagonals = std::min(free_ld, free_rd);
        if (free_diagonals < (BISHOPS - bishops))
          return 0;

        int remaining = SIZE * SIZE - idx;
        if (remaining < (BISHOPS - bishops))
          return 0;

        if (bishops == BISHOPS) return 1;
        if (idx == SIZE * SIZE) return 0;
  
        int r = idx / SIZE;
        int c = idx % SIZE;
  
        int ways = 0;
        // try placing on the current cell
        if(checkPlacement(c, r))
        {
            occupied_diagonals(r, c);
            ways += backtrack(idx + 1, bishops + 1);
            relieve_diagonals(r, c);
        }
        // skip the current cell
        ways += backtrack(idx + 1, bishops);
        return ways;
    }

    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        bool precomputed = true;
        while(std::cin >> SIZE >> BISHOPS)
        {
            TOTAL_DIAGONALS = 2 * SIZE  - 1;
            if(!BISHOPS && !SIZE) break;
            std::cout << backtrack(0, 0) << std::endl;
        } 
    }
}
#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>






typedef std::vector<int> vi;
typedef std::vector<std::pair<vi, int>> vpvii;


namespace algorithms::onlinejudge::complete_search::rooks
{
    /** https://onlinejudge.org/external/6/639.pdf, generate 2 ^ 16 combinations and prune  */
    int S;
    bool validate(const vi& cfg, const vi& board)
    {
        int N = board.size();
        vi attacked(N); // marks attacked/occupied cells
        for (int i = 0; i < N; ++i)
        {
            if (!cfg[i]) continue;
            if (board[i] || attacked[i]) return false;
            // mark row to the right
            for(int col = i + 1; col < (i / S + 1) * S; ++col)
            {
                if(board[col]) break;
                if(cfg[col]) return false; // rook in line of fire
                attacked[col] = 1;
            }
    
            // mark column downward
            for(int row = i + S; row < N; row += S)
            {
                if (board[row]) break;
                if (cfg[row]) return false; // rook in line of fire
                attacked[row] = 1;
            }
        }
        return true;
    }
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        while(std::cin >> S && S)
        {
            vi board(S * S);
            for(int i = 0; i < S; i++)
              for(int j = 0; j < S; j++)
              {
                  char c;
                  std::cin >> c; 
                  board[i * S + j] = (c == '.' ? 0 : 1);
              }

            vpvii configs;
            for(int c = 1; c < (1 << S * S); c++)
            {
                vi sub_config(S * S);
                for(int p = 0; p < S * S; p++)
                  if((c & (1 << p)))
                    sub_config[p] = 1;
                configs.push_back({sub_config, __builtin_popcount(c)}); 
            }

            int max_rooks = INT32_MIN;
            for(auto& conf : configs)
              if(validate(conf.first, board))
                max_rooks = std::max(max_rooks, conf.second);

            std::cout << (max_rooks != INT32_MIN ? max_rooks : 0) << std::endl;
        }
    }
}
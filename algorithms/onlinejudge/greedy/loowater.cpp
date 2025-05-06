#include "../debug.h"
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>






typedef long long ll;
typedef std::vector<int> vi;


namespace algorithms::onlinejudge::greedy::loowater
{
    /**  */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }

        size_t N, M;
        while(std::cin >> N >> M && N && M)
        {
            vi dragon_heads(N);
            vi knights(M);
            for(size_t i = 0; i < N; i++)
              std::cin >> dragon_heads[i];
            for(size_t i = 0; i < M; i++)
              std::cin >> knights[i];
            
            std::sort(dragon_heads.begin(), dragon_heads.end());
            std::sort(knights.begin(), knights.end());
            size_t min_gold = 0;
            // i = iterator over knights, j - heads
            size_t i = 0, j = 0;
            while(j < N)
            {
                while(i < M && knights[i] < dragon_heads[j]) ++i;
                if(i >= M) break;
                min_gold += knights[i];
                ++j; ++i;
            }
            j < N ? printf("Loowater is doomed!\n") : printf("%zu\n", min_gold);
        }
    }
}
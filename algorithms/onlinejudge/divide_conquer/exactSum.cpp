#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>




typedef std::vector<int> vi;


namespace algorithms::onlinejudge::divide_conquer::exact_sum
{
    /**  https://onlinejudge.org/external/110/11057.pdf,  sort, for price p[i], check if price (M - p[i]) exists with binary search */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int N;
        while(std::cin >> N)
        {
            vi books(N);
            for(int i = 0; i < N; i++)
              std::cin >> books[i];
            std::sort(books.begin(), books.end()); 

            int sum;
            std::cin >> sum;
            int f_b, s_b, diff = INT32_MAX;
            for(int i = 0; i < books.size(); i++)
            {
                int t = sum - books[i];
                bool isf = std::binary_search(books.begin() + i + 1, books.end(), t);
                if(isf && diff > t - books[i])
                { 
                    f_b = books[i];
                    s_b = t;
                    diff = t - books[i]; 
                }
            }
            printf("Peter should buy books whose prices are %d and %d.\n\n", f_b, s_b);
        }
    }
}
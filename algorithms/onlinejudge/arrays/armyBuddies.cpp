#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>

#define FAST_IO ios::sync_with_stdio(false); cin.tie(nullptr);

typedef std::vector<int> vi;

namespace algorithms::onlinejudge::arrays::army_buddies
{
    // https://onlinejudge.org/external/123/12356.pdf
    // similar to deletion in doubly linked lists,
    // but we can still use a 1D array for the underlying data structure
    // 2 arrays for left and right neighbours are maintained to reduce time complexity to O(1)
    // the only cost of O(S) goes for the creation of them that is linear
    // overall time complexity must be O(S + B), S - warriors, B - the number of reports
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int S, R;
        while(true)
        {
            std::cin >> S >> R;
            if(S == 0 && R == 0) break;

            vi left_neighbours = vi(S);
            vi right_neighbours = vi(S);

            for(int i = 0; i < S; i++)
              left_neighbours[i] = i - 1,
              right_neighbours[i] = i + 1 < S ? i + 1 : -1;

            while(R--)
            {
                int l, r;
                std::cin >> l >> r;
                int left = left_neighbours[--l];
                int right = right_neighbours[--r];
                
                if (left != -1) right_neighbours[left] = right;
                if (right != -1) left_neighbours[right] = left;

                auto left_buddy = left != -1 ? std::to_string(left + 1) : "*";
                auto right_buddy = right != -1 ? std::to_string(right + 1) : "*";
                std::cout << left_buddy << " " << right_buddy << std::endl;
            }
            std::cout << "-" << std::endl;
        }
    }
}
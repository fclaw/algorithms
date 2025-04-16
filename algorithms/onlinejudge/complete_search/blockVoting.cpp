#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <numeric>
#include <cmath>
#include <string>
#include <algorithm>



typedef std::vector<int> vi;


namespace algorithms::onlinejudge::complete_search::block_voting
{
    /** https://onlinejudge.org/external/4/435.pdf, only 220 possible coalition combinations 
     *
     * The Banzhaf power index measures how often a party is critical in a winning coalition.
     *
     * Definitions:
     * - A coalition is any non-empty subset of parties.
     * - A winning coalition is one where the total number of votes > 50% of the overall votes.
     * - A party is critical if its removal from a winning coalition causes the total to drop below the majority threshold.
     *
     * To calculate the power index for each party:
     * 1. Let `votes[i]` be the vote count for each party.
     * 2. Compute the total number of votes and the majority threshold (total / 2 + 1).
     * 3. Iterate over all possible coalitions (use bitmasks from 1 to (1 << n) - 1).
     * 4. For each coalition:
     *    - If the coalition is winning:
     *      - For each member in the coalition:
     *          - Temporarily remove them and check if the coalition becomes losing.
     *          - If so, count that party as critical in this coalition.
     * 5. The number of times a party is found to be critical is its Banzhaf power index.
     *
     * Example:
     * For votes = {7, 4, 2, 6, 6}, total = 25, majority = 13
     * Party 1 (7 votes) is critical in 10 winning coalitions → Power Index = 10
     *
     * Final output: a vector of power indices per party.
     */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            int N;
            std::cin >> N;
            vi parties(N);
            for(int i = 0; i < N; i++)
              std::cin >> parties[i];
          
            int w_majority = std::round(std::accumulate(parties.begin(), parties.end(), 0) / 2 + 1);

            int total_blocks = (1 << N);
            vi vote_sum(total_blocks);
            
            /*
            * Precomputing vote sums for all possible subsets using bitmask DP:
            * 
            * For each subset (represented as a bitmask), we can determine its total vote count
            * by adding the vote of the last added party to the vote sum of a smaller subset.
            *
            * Example:
            *   mask = 0b1101 (parties 0, 2, 3)
            *   last_bit = 0 (rightmost set bit)
            *   prev_mask = 0b1100 (mask ^ (1 << last_bit))
            *   vote_sum[0b1101] = vote_sum[0b1100] + parties[0]
            *
            * This avoids recalculating the vote total from scratch every time,
            * reducing time complexity from O(2^N * N) to O(2^N).
            *
            * This precomputed vote_sum can then be used directly to:
            *  - Check if a coalition is a winning one (i.e., votes >= majority)
            *  - Efficiently assess each member's contribution to the coalition
            *
            * Smart memoisation of subsets like this is a key technique in subset-based problems.
            */
            for(int block = 1; block < total_blocks; ++block) 
            {
                int last_bit = __builtin_ctz(block); // rightmost set bit
                int prev_block = block ^ (1 << last_bit);
                vote_sum[block] = vote_sum[prev_block] + parties[last_bit];
            }

            vi power(N);
            for(int block = 1; block < total_blocks; block++)
            {
                int votes = vote_sum[block];
                if(votes < w_majority) continue;

                // The key idea is that a party’s power is determined by the number of minority coalitions
                // that it can join and turn into a (winning) majority coalition. 
                for (int i = 0; i < N; ++i)
                  if((block & (1 << i)))
                    if(votes - parties[i] < w_majority)
                      power[i]++;
            }
            
            std::string ans;
            for(int i = 0; i < N; i++)
              ans += "party " + std::to_string(i + 1) + " has power index " + std::to_string(power[i]) + "\n";
            
            std::cout << ans << std::endl;  
        }
    }
}
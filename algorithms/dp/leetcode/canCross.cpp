#include <vector>
#include <unordered_map>

namespace algorithms::dp::leetcode
{
    // https://leetcode.com/problems/frog-jump
    /**
     * A frog is crossing a river. The river is divided into some number of units, 
     * and at each unit, there may or may not exist a stone. The frog can jump on a stone, 
     * but it must not jump into the water. 
     * Given a list of stones positions (in units) in sorted ascending order, 
     * determine if the frog can cross the river by landing on the last stone. 
     * Initially, the frog is on the first stone and assumes the first jump must be 1 unit.
     * If the frog's last jump was k units, its next jump must be either k - 1, k, or k + 1 units. 
     * The frog can only jump in the forward direction.
     * Constraint:
     *   2 <= stones.length <= 2000
     *   0 <= stones[i] <= 2 ^ 31 - 1
     *   stones[0] == 0
     *   stones is sorted in a strictly increasing order
     * DFS Approach: 
     *   With the DFS solution, we explore all the possible jump lengths from each stone. 
     *   We start from the first stone and recursively try every possible next jump length (k - 1, k, k + 1). 
     *   If at any point we can jump to a stone that allows us to eventually reach the last stone, 
     *   we return true. We employ memoization to store the results of subproblems 
     *   (i.e., if a certain jump from a particular stone is possible or not), 
     *   which prevents us from recalculating the same scenarios multiple times, thus optimizing efficiency.
     */
    int STONES_SIZE;
    std::unordered_map<int, int> stones_existence;
    std::unordered_map<int, std::unordered_map<int, int>> stone_memo;
    bool dfs(const std::vector<int>& stones, int pos, int jump)
    {
        if(pos == STONES_SIZE - 1)
          return true;
        
        if(stone_memo[pos][jump])
          return stone_memo[pos][jump];

        bool ans = false;
        int max_pos = stones_existence[stones[pos] + jump + 1];
        if(max_pos) ans |= dfs(stones, max_pos, jump + 1);

        int no_pos = stones_existence[stones[pos] + jump];
        if(no_pos) ans |= dfs(stones, no_pos, jump);

        int neg_pos = stones_existence[stones[pos] + jump - 1];
        if(neg_pos) ans |= dfs(stones, neg_pos, jump - 1);

        return stone_memo[pos][jump] = ans;  
    }
    bool canCross(std::vector<int> stones) 
    {
        STONES_SIZE = stones.size();
        for(int i = 0; i < STONES_SIZE; i++)
          stones_existence.insert({stones[i], i});
        return dfs(stones, 1, 1);
    }
}
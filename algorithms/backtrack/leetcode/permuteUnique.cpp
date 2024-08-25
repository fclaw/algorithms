#include <vector>
#include <set>

namespace algorithms::backtrack::leetcode::unique_permutation
{

using nums = std::vector<int>;
using permutations = std::vector<std::vector<int>>;
using set = std::set<std::vector<int>>;

    /**
     * https://leetcode.com/problems/permutations-ii
     * given a collection of numbers, nums, that might contain duplicates, 
     * return all possible unique permutations in any order.
     */
    int N;
    set s;
    void backtrack(nums& xs, int idx) 
    {
        if(idx == N)
        {
            s.insert(xs);
            return;
        }         

        for(int i = idx; i < N; i++)
        {
            std::swap(xs[idx], xs[i]);
            backtrack(xs, idx + 1);
            std::swap(xs[idx], xs[i]);
        }
    }
    permutations permuteUnique(nums xs)
    {
        N = xs.size();
        backtrack(xs, 0);
        return std::vector<std::vector<int>>(s.begin(), s.end());
    }
}
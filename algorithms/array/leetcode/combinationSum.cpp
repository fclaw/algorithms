#include <vector>

namespace algorithms::array::leetcode
{
    // https://leetcode.com/problems/combination-sum
    /*
    Step-by-Step Approach
    Sort the Array (Optional):

    1 (optional) Sorting the array can help in pruning branches early if you decide to skip further exploration when the current sum exceeds the target.

    2 Define the Backtracking Function:
    Create a recursive function that takes the current combination, 
    the remaining target, the start index, and the original array as arguments.

    - Base Cases:
        If the remaining target is zero, add the current combination to the list of results.
        If the remaining target is less than zero or if the start index is out of bounds, return without adding the combination.

    - Recursive Exploration:
        Iterate over the array starting from the current index.
        Include the current element in the combination and recursively call the function with the updated combination and target.
        Exclude the current element and move to the next index.

    3 Backtracking: After exploring with the current element, remove it from the combination to explore other possibilities.
    */
    void combinationSumHelper(size_t idx, std::vector<int> xs, int& target, std::vector<int>& ys, std::vector<std::vector<int>>& acc)
    {
        auto n = xs.size();
        if(target == 0)
        acc.push_back(ys);
        else if(target < 0)
        return;
        else if (idx == n)
        return;
        else
        { 
            // Include the current element in the combination and 
            // recursively call the function with the updated combination and target.
            ys.push_back(xs[idx]);
            target -= xs[idx];
            combinationSumHelper(idx, xs, target, ys, acc);
            // Exclude the current element and move to the next index.
            ys.pop_back();
            target += xs[idx];
            combinationSumHelper(idx + 1, xs, target, ys, acc);
        }
    }

    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target)
    {
        std::sort(candidates.begin(), candidates.end());
        std::vector<std::vector<int>> combinationXs = {};
        for (size_t i = 0; i < candidates.size(); i++)
        {
            std::vector<int> ys = {candidates[i]};
            int val = target - candidates[i];
            combinationSumHelper(i, candidates, val, ys, combinationXs);
        }
        return combinationXs;
    }
}
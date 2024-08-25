#include <vector>


namespace algorithms::backtrack::leetcode::combination_sum
{

using nums = std::vector<int>;
using storage = std::vector<int>;
using combinations = std::vector<std::vector<int>>;

   // https://leetcode.com/problems/combination-sum-ii
   /**
    * Given a collection of candidate numbers (candidates) and a target number (target), 
    * find all unique combinations in candidates where the candidate numbers sum to target.
    * Each number in candidates may only be used once in the combination.
    * Note: The solution set must not contain duplicate combinations.
   */
   int N;
   int T;
   combinations ans;
   void backtrack(const nums& xs, int idx, storage& st)
   {
       if(idx > N)
         return;

       auto sum = std::reduce(st.begin(), st.end());
       if(sum > T)
         return;
       if(sum == T)
       {
           auto tmp = st;
           ans.push_back(tmp);
           return;
       }
       for(int i = idx; i < N; i++)
       {
            if(i > idx && xs[i] == xs[i - 1])
              continue;
            st.push_back(xs[i]);
            backtrack(xs, i + 1, st);
            st.pop_back();
       }
   }
   combinations combinationSum2(nums& candidates, int target) 
   {
       T = target;
       N = candidates.size();
       std::sort(candidates.begin(), candidates.end());
       storage st;
       backtrack(candidates, 0, st);
       return ans;   
   }
}
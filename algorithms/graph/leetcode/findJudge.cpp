#include <vector>

namespace algorithms::graph::leetcode::town_judge
{

using relation = std::vector<std::vector<int>>;

    /** 
     * https://leetcode.com/problems/find-the-town-judge
     * In a town, there are n people labeled from 1 to n. There is a rumor that one of these people is secretly the town judge.
     * If the town judge exists, then the following conditions ought to be met:
     *  - The town judge trusts nobody.
     *  - Everybody (except for the town judge) trusts the town judge.
     * There is exactly one person that satisfies properties 1 and 2.
     * You are given an array trust where trust[i] = [a(i), b(i)] representing 
     * that the person labeled a(i) trusts the person labeled b(i). 
     * If a trust relationship does not exist in trust array, then such a trust relationship does not exist.
     * Return the label of the town judge if the town judge exists and can be identified, or return -1 otherwise. */
    int findJudge(int n, const relation& trust)
    {
        std::vector<int> xs(n + 1, 0);
        for(auto t : trust)
        {
            xs[t[0]] -= 1;
            xs[t[1]] += 1;
        }
        int ans = -1;
        for(int i = 1; i <= n; i++)
          if(xs[i] == n - 1)
          {
              ans = i;
              break;
          }
        return ans;
    }
}
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

typedef std::vector<int> vi;

namespace algorithms::backtrack::leetcode::jobs
{

    void backtrack(const vi& jobs, int assignees, int idx, vi& times, int& ans)
    {
        if(idx == jobs.size())
        {
            int local_max = *std::max_element(times.begin(), times.end()); 
            ans = std::min(ans, local_max);
            return;
        }

        for(int i = 0; i < assignees; i++)
        {
            times[i] += jobs[idx];
            // Recurse to assign the rest of the jobs to k-1 workers
            if (times[i] < ans) backtrack(jobs, assignees, idx + 1, times, ans);
            // Backtrack, remove the current job from the worker
            times[i] -= jobs[idx];
            if (times[i] == 0) break;
        }
    }
    int minimumTimeRequired(vi jobs, int assignees)
    {
        int ans = INT32_MAX;
        vi times(assignees);
        backtrack(jobs, assignees, 0, times, ans);
        return ans;
    }
}
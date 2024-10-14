#include <vector>
#include <numeric>
#include <unordered_map>

namespace algorithms::dp::leetcode::jobs
{

#define loop(x, s, n) for(int x = s; x < n; x++)
typedef std::vector<int> vi;
typedef std::pair<double, int> pi;
typedef std::unordered_map<int, std::unordered_map<int, pi>> table;

const double inf = std::numeric_limits<double>::max();


    /** https://leetcode.com/problems/find-minimum-time-to-finish-all-jobs
     * You are given an integer array jobs, where jobs[i] is the amount of time it takes to complete the ith job.
     * There are k workers that you can assign jobs to. Each job should be assigned to exactly one worker. 
     * The working time of a worker is the sum of the time it takes to complete all jobs assigned to them. 
     * Your goal is to devise an optimal assignment such that the maximum working time of any worker is minimized.
     * Return the minimum possible maximum working time of any assignment.
     * Constraints:
     *   1 <= k <= jobs.length <= 12
     *   1 <= jobs[i] <= 107
     * hint: We can select a subset of tasks and assign it to a worker then solve the subproblem on the remaining tasks
     * convert into DAG, state: pos, assignee left */
    int K, T;
    pi dfs(const vi& jobs, int pos, vi assignees_times, int avg_time)
    {
        if(pos == jobs.size())
        {
            double cmp = 0;
            for(int t : assignees_times)
              cmp += std::abs(t - avg_time) / (double)avg_time;
            int max_time = *std::max_element(assignees_times.begin(), assignees_times.end());
            cmp = std::ceil(cmp * 100.0) / 100.0;
            return {cmp, max_time};
        }

        pi res = {inf, 0};
        loop(i, 0, K)
        {
            vi local = assignees_times;
            local[i] += jobs[pos];
            pi next = dfs(jobs, pos + 1, local, avg_time);
            if(next.first < res.first) res = next;
        }

        return res;
    }
    int minimumTimeRequired(const vi& jobs, int assignees) 
    {
        K = assignees;
        T = std::reduce(jobs.begin(), jobs.end());
        int avg_job_time = std::floor(T / assignees);
        vi assignees_times = vi(K, 0);
        table memo;
        return dfs(jobs, 0, assignees_times, avg_job_time).second;
    }
}
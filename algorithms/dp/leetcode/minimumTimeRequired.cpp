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
    int cnt = 0;
    pi backtrack(const vi& jobs, int pos, int mask, vi& assignees_times, int avg_time, table& memo)
    {
        if(pos == jobs.size())
        {
            int all = std::reduce(assignees_times.begin(), assignees_times.end());
            if(all != T) return {inf, 0};
            cnt++;
            double res = 0;
            for(int t : assignees_times)
              res += std::abs(t - avg_time) / (double)avg_time;
            int max_time = *std::max_element(assignees_times.begin(), assignees_times.end());
            return {res, max_time};
        }

        if(auto it_pos = memo.find(pos);
           it_pos != memo.end())
        {
            auto it_m = (*it_pos).second.find(mask);
            if(it_m != (*it_pos).second.end())
              return (*it_m).second;
        }

        pi res = {inf, 0};
        loop(i, 0, K)
        {
            vi local = assignees_times;
            local[i] += jobs[pos];
            pi assign_job = backtrack(jobs, pos + 1, mask, local, avg_time, memo);
            local[i] -= jobs[pos];
            pi skip_job = backtrack(jobs, pos + 1, mask, local, avg_time, memo);
            pi min = assign_job.first < skip_job.first ? assign_job : skip_job;
            if(min.first < res.first) res = min;
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
        return backtrack(jobs, 0, 0, assignees_times, avg_job_time, memo).second;
    }
}
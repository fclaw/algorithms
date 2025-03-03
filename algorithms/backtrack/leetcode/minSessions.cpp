#include <vector>



typedef std::vector<int> vi;
typedef std::vector<vi> vvi;


namespace algorithms::backtrack::leetcode::min_sessions
{
    /** https://leetcode.com/problems/minimum-number-of-work-sessions-to-finish-the-tasks
     * There are n tasks assigned to you. 
     * The task times are represented as an integer array tasks of length n, 
     * where the ith task takes tasks[i] hours to finish. 
     * A work session is when you work for at most sessionTime consecutive hours and then take a break.
     * You should finish the given tasks in a way that satisfies the following conditions:
     * If you start a task in a work session, you must complete it in the same work session.
     * You can start a new task immediately after finishing the previous one.
     * You may complete the tasks in any order.
     * Given tasks and sessionTime, return the minimum number of work sessions 
     * needed to finish all the tasks following the conditions above.
     * The tests are generated such that sessionTime is greater than or equal to the maximum element in tasks[i].
     * Constraints:
     *   n == tasks.length
     *   1 <= n <= 14
     *   1 <= tasks[i] <= 10
     *   max(tasks[i]) <= sessionTime <= 15
     * Hint: judging n we can conclude that time complexity is polynomial (2 ^ n ...)
     * */
    
    // all tasks are assigned but session is greater then 0 [3, 9], 10
    // all tasks are assigned and session is 0

    int ans = INT32_MAX;
    int N;
    int S;
    int MAX_STATE = (1 << 14) - 1;
    int MAX_SESSION = 16;
    vvi dp(MAX_STATE, vi(MAX_SESSION, -1));
    void backtrack(const vi& tasks, int mask, int session, int cnt)
    {
        if(mask == (1 << N) - 1)
        { ans = std::min(ans, session > 0 ? ++cnt : cnt); return; }

        if (~dp[mask][session] && 
            dp[mask][session] <= cnt) 
          return;
    
        dp[mask][session] = cnt; // Store the best so far 


        for(int i = 0; i < N; i++)
        {
            if((mask & (1 << i)))
              continue;
            
            if(session - tasks[i] == 0 && (mask | (1 << i)) == ((1 << N) - 1))
              backtrack(tasks, mask | (1 << i), 0, cnt + 1);
            if(session - tasks[i] == 0)  
              backtrack(tasks, mask | (1 << i), S, cnt + 1);
            else if(session - tasks[i] > 0)
              backtrack(tasks, mask | (1 << i), session - tasks[i], cnt);
            else if( S - tasks[i] == 0) 
              backtrack(tasks, mask | (1 << i), 0, cnt + 2);
            else backtrack(tasks, mask | (1 << i), S - tasks[i], cnt + 1);  
        }
    }
    int minSessions(vi tasks, int session) 
    { N = tasks.size(); S = session; backtrack(tasks, 0, session, 0); return ans; }
}
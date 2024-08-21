#include <vector>

namespace algorithms::backtrack::leetcode
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
    int minSessions(std::vector<int> tasks, int session) 
    {
        return 0;
    }
}
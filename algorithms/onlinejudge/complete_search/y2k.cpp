#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>





typedef std::vector<int> vi;


namespace algorithms::onlinejudge::complete_search::y2k
{
    /** https://onlinejudge.org/external/105/10576.pdf, 
     * generate all, prune, take max
     * Let's list all 8 periods:
     * 1. Starting month 1: [1, 1+4] = [1, 5]
     * 2. Starting month 2: [2, 2+4] = [2, 6]
     * 3. Starting month 3: [3, 3+4] = [3, 7]
     * 4. Starting month 4: [4, 4+4] = [4, 8]
     * 5. Starting month 5: [5, 5+4] = [5, 9]
     * 6. Starting month 6: [6, 6+4] = [6, 10]
     * 7. Starting month 7: [7, 7+4] = [7, 11]
     * 8. Starting month 8: [8, 8+4] = [8, 12]
     * - The problem can be solved optimally using exhaustive search due to small constraints (2^12 possibilities).
     * */
    int deficit;
    int surplus;
    int ans;
    int YEAR = 12;
    int validation(const vi& balances) 
    {
        int profit = 0;       // Total surplus (positive balances)
        int expenses = 0;     // Total deficit (negative balances)
        int acc = 0;          // Accumulated balance over the year
    
        for (int i = 0; i < YEAR; i++)
        {
            if(balances[i] > 0)
              profit += balances[i];  // Accumulate surpluses
            else expenses += balances[i];  // Accumulate deficits
              acc += balances[i];
        }
    
        // To maximize the surplus, subtract the total deficit from total surplus
        int net = profit + expenses;  // Total net (profit + expenses)
    
        // Ensure that there were at least 8 5-month periods with deficit
        bool isDeficit = true;  // Assume there's a deficit
        for (int i = 0; i <= YEAR - 5; i++) 
        {
            int windowAcc = 0;
            for (int j = 0; j < 5; j++)
              windowAcc += balances[i + j];

            // If the window has a surplus, it's invalid
            if (windowAcc > 0) 
            { isDeficit = false; break; }
        }
    
        return isDeficit ? net : -1;
    }
    void backtrack(int months, vi& balances)
    {
        if(months > YEAR)
        { 
            int profit = validation(balances);
            if(profit > 0) ans = std::max(ans, profit);
            return; 
        }

        // month ends up with deficit
        balances.push_back((-1) * deficit);
        backtrack(months + 1, balances);
        balances.pop_back();

        // month ends up with profit
        balances.push_back(surplus);
        backtrack(months + 1, balances);
        balances.pop_back();
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        while(scanf("%d %d",&surplus,&deficit) != EOF)
        {
            ans = INT32_MIN;
            vi balances;
            backtrack(1, balances);
            std::cout << (ans != INT32_MIN ? std::to_string(ans) : "Deficit") << std::endl;
        }
    }
}
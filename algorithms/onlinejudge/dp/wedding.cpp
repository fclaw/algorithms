#include <cstdio>
#include <vector>
#include <iostream>
#include <iomanip>

using Garments = std::vector<std::vector<int>>;

void printGarmentsDp(std::vector<std::vector<bool>> dp)
{
    for ( const auto &row : dp )
    {
        for ( const auto &s : row ) 
          std::cout << std::setw(5) << s << ' ';
        std::cout << std::endl;
    }
}

namespace algorithms::onlinejudge::dp
{

    /*
        We are offered different models for each class of garment 
        (for example, three shirts, two belts, four shoes, ...).
        We have to buy one model of each class of garment, and just one.
        As our budget is limited, we cannot spend more money than it, 
        but we want to spend the maximum possible. 
        It’s possible that we cannot buy one model of each class 
        of garment due to the short amount of money we have.

        notes about time complexity:
        This solution works correctly, but it is very slow! Let’s analyze the worst case time complexity. 
        In the largest test case, garment g = 0 has up to 20 models; 
        garment g = 1 also has up to 20 models and all garments 
        including the last garment g = 19 also have up to 20 models. 
        Therefore, this Complete Search runs in 20 × 20 × . . . × 20 operations in the worst case, 
        i.e. 20 ^ 20 = a very large number. 
        If we can only come up with this Complete Search solution, we cannot solve this problem.

        This problem has overlapping sub-problems
        This is the key characteristic of DP! 
        The search space of this problem is not as big as the rough 2020 bound 
        obtained earlier because many sub-problems are overlapping!


    */
    int doShopping(Garments xxs, int i, int money, std::vector<std::vector<int>>& memo)
    {
        int n = xxs.size();
       
        if(i == n)
          return 0;

        if(memo[money][i] != -1)
          return memo[money][i];

        int m = xxs[i].size();
        int expenditure = INT_MIN;
        for (int j = 0; j < m; j++)
        {
            if(money - xxs[i][j] < 0)
              continue;
            expenditure = std::max(expenditure, xxs[i][j] + doShopping(xxs, i + 1, money - xxs[i][j], memo));
        }
        
        return memo[money][i] = expenditure;
    } 

    int doShoppingDp(Garments xxs, int money)
    {
        int C = xxs.size();
        std::vector<std::vector<bool>> dp(C, std::vector<bool>(money + 1, false));

        for(int i = 0; i < xxs[0].size(); i++)
          if(money - xxs[0][i] >= 0)
            dp[0][money - xxs[0][i]] = true;

        for(int g = 1; g < C; g++)
          for (int m = 0; m <= money; m++)
            if(dp[g - 1][m])
              for (int i = 0; i < xxs[g].size(); i++)
                if(m - xxs[g][i] > 0)
                  dp[g][m - xxs[g][i]] = true;

        // Finally, the answer can be found in the last row when g = C-1. 
        // Find the state in that row that is both nearest to index 0 and reachable.
        int ans;
        for (ans = 0; ans <= money && !dp[C - 1][ans]; ans++);
        return money - ans;
    }

    /*
        The first line of the input contains an integer,N, 
        indicating the number of test cases. For each test case, some lines appear, 
        the first one contains two integers, M and C, separated by blanks (1 ≤ M ≤ 200, and 1 ≤ C ≤ 20), 
        where M is the available amount of money and C is the number of garments you have to buy. 
        Following this line, there are C lines, each one with some integers separated by blanks; 
        in each of these lines the first integer, K (1 ≤ K ≤ 20), 
        indicates the number of different models for each garment and it is followed by K integers 
        indicating the price of each model of that garment
    */
    void submit()
    {
        int TC;
        scanf("%d", &TC);
        while(--TC >= 0)
        {
            int money, c;
            scanf("%d %d\n", &money, &c);
            
            Garments garments;
            for(int i = 0; i < c; i++)
            {
                int m;
                scanf("%d", &m);
                std::vector<int> xs(m);
                for (int j = 0; j < m; j++)
                  scanf("%d", &xs[j]);
                garments.push_back(xs);
            }

            std::vector<std::vector<int>> memo(money + 1, std::vector<int>(c + 1, -1));

            // auto score = doShopping(garments, 0, money, memo);
            auto score = doShoppingDp(garments, money);

            if(score == money)
              printf("%s\n", "no solution");
            else printf("%d\n", money - score);
        }
    }
}
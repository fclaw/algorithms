#include <cstdio>
#include <vector>

namespace algorithms::codeforces
{

    int solve_1355_b(std::vector<int> exp)
    {
        std::sort(exp.begin(), exp.end());
        int ans = 0;
        int i = 0;
        int j = exp.size() - 1;
        while(i < j)
        {
            int cnt = exp[j] - 1;
            while(i < j && exp[i] <= exp[j] && --cnt > 0) i++;
            ans++;
            j--;
        }
        return ans;
    }

    // https://codeforces.com/problemset/problem/1355/B
    /*
        Young wilderness explorers set off to their first expedition led by senior explorer Russell. 
        Explorers went into a forest, set up a camp and decided to split into groups 
        to explore as much interesting locations as possible. 
        Russell was trying to form groups, but ran into some difficulties...

        Most of the young explorers are inexperienced, and sending them alone would be a mistake. 
        Even Russell himself became senior explorer not long ago. 
        Each of young explorers has a positive integer parameter e(i) — his inexperience. 
        Russell decided that an explorer with inexperience 𝑒 can only join the group of 𝑒 or more people.
        Now Russell needs to figure out how many groups he can organize. 
        It's not necessary to include every explorer in one of the groups: some can stay in the camp. 
        Russell is worried about this expedition, so he asked you to help him.

        1, 2, 2, 2, 3

    */
    void submit_1355_b()
    {
        int TC;
        scanf("%d", &TC);
        while(TC-- > 0)
        {
            int n;
            scanf("%d", &n);
            std::vector<int> exp(n);
            for (int i = 0; i < n; i++)
              scanf("%d", &exp[i]);

            printf("%d\n", solve_1355_b(exp));
        }
    }
}
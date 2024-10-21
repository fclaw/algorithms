#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>


namespace algorithms::maths::onlinejudge::brick_game
{

#define loop(x, s, n) for(int x = s; x < n; x++)
typedef std::vector<int> vi;

    /** https://onlinejudge.org/external/118/11875.pdf, get median of a sorted input */
    int ageOfTheCaptain(const vi& team) 
    {
        return 1;
    }

    void submit(std::optional<char*> file)
    {
        if(file.has_value()) assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int tc, c = 0;
        std::cin >> tc;
        while(--tc >= 0)
        {
            int n;
            std::cin >> n;
            vi team;
            int m;
            loop(i, 0, n) 
            { std::cin >> m; team.push_back(m); }
            int ans = ageOfTheCaptain(team);
            printf("Case %d: %s\n", ++c, std::to_string(ans).c_str());
        }
    }
}
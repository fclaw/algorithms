#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <string>


namespace algorithms::onlinejudge::easy::event_planning
{
    // https://onlinejudge.org/external/115/11559.pdf, one linear pass
    const int inf = 5 * (int)1e+05;
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int guests, budget, hotels, weeks, ans;
        while(std::cin >> guests >> budget >> hotels >> weeks)
        {
            ans = inf;
            while(hotels--)
            {
                int night, beds, expenses = inf;
                std::cin >> night;
                for(int i = 0; i < weeks; i++)
                {
                  std::cin >> beds;
                  if(beds >= guests) 
                    expenses = std::min(expenses, night * std::min(beds, guests));
                }

                ans = std::min(ans, expenses);
            }

            std::cout << (ans == inf || ans > budget ? "stay home" : std::to_string(ans)) << std::endl;
        }
    }
}
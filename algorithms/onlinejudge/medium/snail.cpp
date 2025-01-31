#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <string>


namespace algorithms::onlinejudge::easy::snail
{
    // https://onlinejudge.org/external/5/573.pdf
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) assert(std::freopen(file.value(), "r", stdin) != nullptr);
        int length, climb, slide, fatigue;
        while(std::cin >> length >> climb >> slide >> fatigue)
        {
            if(length == 0) break;
            double dist = 0, fclimb = (double)climb; 
            int days = 0;
            double diff = fclimb * ((double)fatigue / 100);
            while(dist >= 0 && dist < (double)length)
            {
                days++;
                // after a day journey
                if(fclimb > 0) dist += fclimb; // day
                if(dist > (double)length) break;
                dist -= (double)slide; // night
                fclimb -= diff;  // apply fatigue factor
            }
            auto ans = (dist > length ? "success on day " : "failure on day ") + std::to_string(days);
            std::cout << ans << std::endl;
        }
    }
}
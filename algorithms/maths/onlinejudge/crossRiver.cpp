#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>


namespace algorithms::maths::onlinejudge::cross_river
{
    /** https://onlinejudge.org/external/107/10773.pdf, several tricky cases 
     * You are trying to cross a river of width d meters. You are given that, the river flows at v m/s and
     * you know that you can speed up the boat in u m/s. There may be two goals how to cross the river:
     * One goal (called fastest path) is to cross it in fastest time, and it does not matter how far the flow of
     * the river takes the boat. The other goal (called shortest path) is to steer the boat in a direction so that
     * the flow of the river doesn’t take the boat away, and the boat passes the river in a line perpendicular to
     * the boarder of the river. Is it always possible to have two different paths, one to pass at shortest time
     * and the other at shortest path? If possible then, what is the difference (Let P s) between the times
     * needed to cross the river in the different ways? */
    int diffOf2Ways(int width, int river_flow, int boat_speed) { return 1; }

    void submit(std::optional<char*> file)
    {
        if(file.has_value()) assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int tc, c = 0;
        std::cin >> tc;
        while(--tc >= 0)
        {
            int width, flow, boat;
            std::cin >> width >> flow >> boat;
            int ans = diffOf2Ways(width, flow, boat);
            printf("Case %d: %s\n", ++c, std::to_string(ans).c_str());
        }
    }
}
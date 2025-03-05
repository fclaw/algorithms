#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <limits>
#include <algorithm>
#include <tuple>



typedef std::vector<std::tuple<int, int, int>> vtiii;
typedef std::vector<int> vi;


namespace algorithms::onlinejudge::complete_search::transportation
{
    /** https://onlinejudge.org/external/3/301.pdf, 2^22 with pruning is possible */
    int ans;
    int capacity;
    void backtrack(const vtiii& tickets, int idx, int total, vi& stations)
    {
        if(idx == tickets.size())
        { ans = std::max(ans, total); return; }

        int start = std::get<0>(tickets[idx]);
        int end = std::get<1>(tickets[idx]);
        int fares = std::get<2>(tickets[idx]);

        // check whether all seats are available all along the route
        bool isLoad = false;
        for(int i = start + 1; i <= end; i++)
          if(stations[i] + fares > capacity)
          { isLoad = true; break; }

        if(!isLoad)
        {
            for(int i = start + 1; i <= end; i++) 
              stations[i] += fares;
            total += (end - start) * fares;
            backtrack(tickets, idx + 1, total, stations);
            for(int i = start + 1; i <= end; i++) 
              stations[i] -= fares;
            total -= (end - start) * fares;
        }
        
        backtrack(tickets, idx + 1, total, stations);

    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        while(true)
        {
            // passenger capacity of the train
            // N - the number of the city B station
            // M - the number of ticket orders from all stations
            int N, terminus;
            scanf("%d %d %d\n", &capacity, &terminus, &N);
            if(!capacity && !terminus && !N) break;
            
            // Passenger queue: (drop_station, passenger_count)
            vtiii tickets(N);
            for(int i = 0; i < N; i++)
            {
                int start, end, fares;
                scanf("%d %d %d\n", &start, &end, &fares);
                tickets[i] = {start, end, fares};
            }
            std::sort(tickets.begin(), tickets.end());
            ans = std::numeric_limits<int>::min();
            vi stations(terminus + 1);
            backtrack(tickets, 0, 0, stations);
            std::cout << ans << std::endl;
        }
    }
}
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>



struct Traffic_light
{
    double d;
    int green;
    int yellow;
    int red;
};

typedef std::vector<std::pair<int, int>> vpii;
typedef std::vector<Traffic_light> vtl;

namespace algorithms::onlinejudge::complete_search::nonstop_travel
{
    /** https://onlinejudge.org/external/6/617.pdf, 
     * try all integer speeds from 30 to 60 mph */
    const int Lower = 30, Upper = 60;
    const double epsilon = 1e-12; // a small tolerance
    void getSpeeds(const vtl& xs, vpii& speeds) 
    {
        int prev;
        for(int s = Lower; s <= Upper; s++)
        {
            bool isValid = true;
            for(auto& t : xs)
            {
                double arrival_tm = (t.d / s) * 3600.0; // seconds
                double l = t.green + t.red + t.yellow;
                double st = std::fmod(arrival_tm, l);
                if(st > t.green + t.yellow && st < l - epsilon) 
                { isValid = false; break; }
            }

            if(speeds.empty() && isValid)
            { speeds.push_back({s, s});  prev = s; }
            else if(isValid)
            {
                if(prev + 1 != s)
                  speeds[speeds.size() - 1].second = prev,
                  speeds.push_back({s, s});
                prev = s;
            }
        }

        if(!speeds.empty()) 
          speeds[speeds.size() - 1].second = prev;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
          
        int traffic_lights_cnt, c = 1;
        while(std::cin >> traffic_lights_cnt && 
              traffic_lights_cnt != -1)
        {
            vtl traffic_lights;
            Traffic_light tl;
            for(int i = 0; i < traffic_lights_cnt; i++)
            {
                scanf("%lf %d %d %d\n", &tl.d, &tl.green, &tl.yellow, &tl.red);
                traffic_lights.push_back(tl);
            }

            vpii speeds;
            getSpeeds(traffic_lights, speeds);
            if(speeds.empty()) printf("Case %d: No acceptable speeds.\n", c++);
            else
            {
                std::string s;
                for(auto& p : speeds)
                  s += ((p.first == p.second) ? 
                       std::to_string(p.first) : 
                       std::to_string(p.first) + 
                       "-" + 
                       std::to_string(p.second)) + ", ";
                s.pop_back();
                s.pop_back();
                printf("Case %d: %s\n", c++, s.c_str()); 
            }
        }
    }
}
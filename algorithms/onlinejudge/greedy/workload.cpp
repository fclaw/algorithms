#include "../debug.h"
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <tuple>






struct Agency 
{
    std::string name;
    // the price for reduction workload by one unit.
    int by_uint;
    // the price for reduction workload by half
    int by_half;
};

std::ostream& operator << 
  (std::ostream& out, const Agency& a) 
  { return out << "{" << a.name << ", " << a.by_uint << ", "  << a.by_half << "}"; }


typedef std::vector<Agency> va;
typedef std::vector<std::pair<int, std::string>> vpsi;

namespace algorithms::onlinejudge::greedy::workload
{
    /** https://onlinejudge.org/external/106/10670.pdf */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        
        int tc, c = 1;
        std::cin >> tc;
        while(tc--)
        {
            // starting workload, target workload, the number of work reduction agencies available
            int init_w, target_w, N;
            scanf("%d %d %d\n", &init_w, &target_w, &N);

            va agencies(N);
            std::string s;
            for(int i = 0; i < N; i++) {
              std::cin >> s;
              size_t colon_pos = s.find(':');
              std::string name = s.substr(0, colon_pos); // "ABC"
              std::string rest = s.substr(colon_pos + 1); // "10,1"
              // Then split by the comma ","
              size_t comma_pos = rest.find(',');
              int by_unit = std::stoi(rest.substr(0, comma_pos)); // 10
              int by_half = std::stoi(rest.substr(comma_pos + 1)); // 1
              agencies[i] = {name, by_unit, by_half};
            }

            vpsi costs;
            for(const Agency& a : agencies)
            {
                int curr_w = init_w;
                int rem_w = init_w - target_w;
                int total = 0;
                while(rem_w > 0)
                {
                    // The greedy property is based on two key ingredients:
                    // 2 * rem_w >= curr_w: This ensures that halving the current workload (curr_w) 
                    // will actually reduce the workload significantly enough. 
                    // In other words, halving is only worth it if the remaining work is at least as large as half the current workload (or more). 
                    // If this condition is not met, it’s better to reduce by 1 unit instead.
                    // 2 * a.by_half <= curr_w * a.by_uint: This checks the cost-effectiveness of halving the workload. 
                    // It ensures that the cost of halving is less than or equal 
                    // to the cost of reducing the workload by 1 unit multiplied by the number of units you’re about to reduce. 
                    // Essentially, if the cost of halving is smaller (or equal) to the cost of reducing by 1 unit multiple times, 
                    // then halving becomes the preferred option.
                    if(2 * rem_w >= curr_w &&
                       2 * a.by_half <=
                       curr_w * a.by_uint)
                    {
                        curr_w /= 2;
                        total += a.by_half;
                    } else { --curr_w; total += a.by_uint; }
                    rem_w = curr_w - target_w;
                }
                costs.push_back({total, a.name});
            }

            auto cmp = 
              [](const auto& x, const auto& y) 
              { return x.first < y.first || 
                       (x.first == y.first && 
                        x.second < y.second); };
            std::sort(costs.begin(), costs.end(), cmp);

            std::string ans;

            for(const auto& c : costs) 
              ans += c.second + " " + std::to_string(c.first) + "\n";
            printf("Case %d\n%s", c++, ans.c_str());
        }
    }
}
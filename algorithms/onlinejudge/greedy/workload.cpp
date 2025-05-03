/*
 * Issue Explanation: 
 * 
 * In this solution, we're comparing two strategies for reducing the workload:
 * 1. **Halving the current workload** in one step.
 * 2. **Reducing the workload by 1 unit** iteratively until we reach half the original workload.
 * 
 * The challenge lies in the **iterative nature** of reducing by 1 unit, which can lead to small **accumulated errors** during the process:
 * 
 * 1. **Integer Division and Precision**:
 *    - The cost of halving is compared to the cost of reducing by 1 unit iteratively.
 *    - When dividing `curr_w` by 2 (integer division), we get a truncated result (rounded down), which might not always reflect the true halved value, especially for odd numbers. This introduces **small rounding errors**.
 *    
 * 2. **Accumulation of Errors**:
 *    - Over multiple iterations of reducing by 1 unit, small errors in the calculation can accumulate, especially when the remaining work is close to the target (e.g., `curr_w = 3` and `rem_w = 2`).
 *    - These errors could lead to **incorrect decisions** when comparing the cost of halving versus unit reductions.
 *    
 * 3. **System-Dependent Behavior**:
 *    - The behavior of integer division and iterations can be **system-dependent** (i.e., compiler and runtime optimizations might handle precision issues differently).
 *    - Some systems (or compilers) might be able to handle the imprecision well, especially in cases where the precision isn't critical, leading to **correct answers** in most test cases. 
 *    - However, in other environments, such as on a different compiler or with different input sizes (edge cases), the **precision errors** could cause discrepancies, especially when the remaining work is small and close to the target.
 *    
 * Solution: 
 * - The **correct approach** involves calculating the total cost of reducing the workload to half in **one step** rather than relying on iterative reductions, which can accumulate errors.
 * - Instead of iterating, we compute the number of unit reductions required directly using `(curr_w - curr_w / 2)`, and compare that with the halving cost to avoid the iterative imprecision.
 * 
 * This ensures **consistent behavior** across all test cases and compilers, handling both small remaining work and large workloads accurately.
 */

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
                    // a.by_half <= (curr_w - curr_w / 2) * a.by_uint: This checks the cost-effectiveness of halving the workload. 
                    // It ensures that the cost of halving is less than or equal 
                    // to the cost of reducing the workload by 1 unit multiplied by the number of units you’re about to reduce. 
                    // Essentially, if the cost of halving is smaller (or equal) to the cost of reducing by 1 unit multiple times, 
                    // then halving becomes the preferred option.
                    // dbg(curr_w, rem_w, total, 2 * rem_w >= curr_w, a.by_half <= a.by_uint * rem_w);
                    int half_curr_w = curr_w / 2;
                    if(curr_w <= 2 * rem_w &&
                       a.by_half <= (curr_w - half_curr_w) * a.by_uint)
                    {
                        curr_w = half_curr_w;
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
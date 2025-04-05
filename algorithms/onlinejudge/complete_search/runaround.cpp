#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>




typedef std::vector<int> vi;
typedef std::vector<bool> vb;
typedef std::unordered_set<int> si;

namespace algorithms::onlinejudge::complete_search::runaround
{
    /** https://onlinejudge.org/external/3/347.pdf,  simulate the process  */
    int maxVal = static_cast<int>(1e8);
    vb badNumbers(maxVal, false);
    vi getDigits(int n)
    {
        vi digits;
        while(n != 0)
        {
            int d = n % 10;
            n /= 10;
            digits.push_back(d);
        }
        std::reverse(digits.begin(), digits.end());
        return digits;
    }
    
    bool isRunaround(const vi& digits)
    {
        /** next_idx = (curr_idx + digit_value) % total_digits
         * For example, consider the number 81362. 
         * To verify that this is a runaround number, we use the steps shown below:
         * 1. Start with the leftmost digit, 8: 8 1 3 6 2
         * 2. Count 8 digits to the right, ending on 6 (note the wraparound): 8 1 3 6 2
         * 3. Count 6 digits to the right, ending on 2: 8 1 3 6 2
         * 4. Count 2 digits to the right, ending on 1: 8 1 3 6 2
         * 5. Count 1 digit to the right, ending on 3: 8 1 3 6 2
         * 6. Count 3 digits to the right, ending on 8 (where we began): 8 1 3 6 2
         * */
        int S = digits.size();
        int cnt = S;
        int idx = 0;
        si unique;
        unique.insert(digits[idx]);
        bool noUnique = false;
        int mask = 0;
        while(cnt--)
        {
            int next_idx = idx + digits[idx] == S ? 0 : (idx + digits[idx]) % S;
            if((mask & (1 << next_idx))) break;
            if(unique.count(digits[next_idx]) && next_idx != 0)
            { noUnique = true; break; }
            unique.insert(digits[next_idx]);
            idx = next_idx;
            mask |= (1 << idx);
        }
        return unique.size() == S && !noUnique && idx == 0;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int c = 1;  
        std::string num;
        while(std::cin >> num &&
              std::atoi(num.c_str()) != 0)
        {
            int ans = std::atoi(num.c_str());
            while(true)
            {
                if(badNumbers[ans]) { ans++; continue; }
                bool isValid = isRunaround(getDigits(ans));
                if(isValid) break;
                badNumbers[ans] = true;
                ans++;
            }
            printf("Case %d: %d\n", c++, ans);
        }
    }
}
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <numeric>
#include <cmath>

typedef std::vector<int> vi;

namespace algorithms::onlinejudge::skiena::primary
{
    /** https://onlinejudge.org/external/100/10035.pdf */
    const int MAX = 9;
    vi extractDigits(int n)
    {
        int i = MAX; // the array index
        vi digits = vi(MAX, 0); // the array
        // loop till there's nothing left
        while (n) 
        {
            digits[--i] = n % 10; // assign the last digit
            n /= 10; // "right shift" the number
        }
        return digits;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int first_d, second_d;
        while(true)
        {
            std::cin >> first_d >> second_d;
            if(first_d == 0 && 
               second_d == 0)
              break;

            vi xs = extractDigits(first_d);
            vi ys = extractDigits(second_d);
            int l = MAX;

            int ans = 0;
            int carry = 0;
            while(--l >= 0)
            {
                int res = xs[l] + ys[l] + carry;
                if(res >= 10) { carry = 1; ++ans; }
                else carry = 0;
            }

            if(ans == 0) printf("No carry operation.\n");
            else if(ans == 1) printf("1 carry operation.\n");
            else printf("%d carry operations.\n", ans);
        }     
    }
}
#include <cassert>
#include <optional>
#include <iostream>
#include <vector>


namespace algorithms::maths::onlinejudge::digit_counting
{

typedef std::vector<int> vi;

    /** https://onlinejudge.org/external/12/1225.pdf, constraint is that small */
    const int MAX_DIGIT = 10;
    vi fetchDigits(int n) 
    {
        vi ds;
        while (n > 0)
        {
            int d = n % 10;
            n /= 10;
            ds.push_back(d);
        }
        return ds; 
    }
    vi count(int n) 
    {
        vi ans = vi(MAX_DIGIT, 0);
        for(int i = 1; i <= n; i++)
        {
            vi ds = fetchDigits(i);
            for(int d : ds) ++ans[d];
        }
        return ans;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) assert(std::freopen(file.value(), "r", stdin) != nullptr);
        int tc;
        std::cin >> tc;
        while(--tc >= 0)
        {
            int num;
            std::cin >> num;
            vi digit_counter = count(num);
            for(int i = 0; i < MAX_DIGIT; i++) 
              if(i == 9) printf("%d", digit_counter[i]);
              else printf("%d ", digit_counter[i]);
            std::cout << std::endl;  
        }
    }
}
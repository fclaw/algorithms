#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>



typedef std::vector<int> vi;


namespace algorithms::onlinejudge::complete_search::sales
{
    /** https://onlinejudge.org/external/12/1260.pdf, 
     * LA 4843, Daejeon10, check all  */
    int sum(const vi& sales)
    {
        int acc = 0;
        for(int i = 1; i < sales.size(); i++)
        {
            int cnt = 0;
            for(int j = 0; j < i; j ++)
              if(sales[j] <= sales[i]) cnt++;
            acc += cnt;  
        }
        return acc;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            int N;
            std::cin >> N;
            vi sales(N);
            for(int i = 0; i < N; i++)
              std::cin >> sales[i];
        std::cout << sum(sales) << std::endl;  
        }  
    }
}
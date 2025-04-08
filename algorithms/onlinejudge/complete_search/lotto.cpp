#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>




typedef std::vector<int> vi;


namespace algorithms::onlinejudge::complete_search::lotto
{
    /** https://onlinejudge.org/external/4/441.pdf, 6 nested loops  */
    void print(const vi& numbers, int i, int j, int k, int l, int m, int n)
    {
        std::cout << numbers[i] << " " << numbers[j] << " " << 
        numbers[k] << " " << numbers[l] << " " << numbers[m] << " " << 
        numbers[n] << std::endl;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        
        int N;
        bool first = true;
        while(std::cin >> N && N)
        {
            if(!first) std::cout << std::endl;
            first = false;
            const int K = 6;
            vi numbers(N);
            for(int i = 0; i < N; i++)
              std::cin >> numbers[i];

            for(int i = 0; i < N - K + 1; i++)
              for(int j = i + 1; j < N - K + 2; j++)
                for(int k = j + 1; k < N - K + 3; k++)
                  for(int l = k + 1; l < N - K + 4; l++)
                    for(int m = l + 1; m < N - K + 5; m++)
                      for(int n = m + 1; n < N - K + 6; n++)
                        print(numbers, i, j, k, l, m, n);
        }
    }
}
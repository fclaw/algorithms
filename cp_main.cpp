#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <sstream>
#include <numeric>
#include <unordered_set>


typedef std::vector<int> vi;
typedef std::vector<vi> vvi;


const int MOD = 1e9;  // 10^9

int findMissingElement(const vi& perm) {
    std::unordered_set<int> elements(perm.begin(), perm.end());
    for (int i = 1; i < perm.size() + 1; ++i) {
        if (elements.find(i) == elements.end()) {
            return i;  // The missing element
        }
    }
    return -1;  // In case no element is missing, which shouldn't happen in this case
}

int main(int argc, char* argv[])
{
    int tc;
    std::cin >> tc;
    while(tc--)
    {
        int n;
        std::cin >> n;
        vi numbers(n);
        for(int i = 0; i < n; i++)
          std::cin >> numbers[i];
        
        int sum = std::accumulate(numbers.begin(), numbers.end(), 0);

        int ans = 0;
        int max  = INT32_MIN;
        int el;
        for(int i = 0; i < n; i++)
          if((numbers[i] ^ (sum - numbers[i])) > max)
          { 
            el = numbers[i];
            std::cout << "el: " <<  el << ", max: " << ((sum) ^ numbers[i]) << "\n";
            max = (numbers[i] ^ (sum - numbers[i])); 
          }


        for(int i = 0; i < n; i++)
          ans += (el ^ numbers[i]);
          
        std::cout << ans << std::endl;  
    }
   
}
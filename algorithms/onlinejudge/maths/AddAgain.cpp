/*
───────────────────────────────────────────────────────────────
🧳 UVa 11076 Add Again, https://onlinejudge.org/external/110/11076.pdf, 
       do not use next permutation for 12!, TLE;
       observe the digits in all permutations; 
       hint: the solution involves factorial  rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>


namespace arith = algorithms::onlinejudge::maths::utility::arithmetics;


constexpr int MAX_FAC = 11;
using ll = long long;
using vi = std::vector<int>;


ll do_factorial(ll n) {
  ll fac = 1;
  for(ll i = 1; i <= n; ++i)
    fac *= i;
  return fac;  
}


namespace algorithms::onlinejudge::maths::add_again
{
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value()) {
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        }

        std::array<ll, 12> factorials;
        factorials[0] = 0;
        for(int f = 1; f <= MAX_FAC; ++f)
          factorials[f] = do_factorial(f);

        int size;
        while(scanf("%d", &size) == 1 && size) {
          vi nums(size);
          for(int i = 0; i < size; ++i) 
            scanf("%d", &nums[i]);
          
          if(size == 1) {
             printf("%d\n", nums.front());
             continue;
          }  

          ll factor = factorials[size - 1] / (size -  1);
          
          std::unordered_map<int, ll> products;
          for(int i = 0; i < size; ++i)
            for(int j = 0; j < size; ++j)
              if(auto it = products.find(nums[i]); i != j) {  
                if(it == products.end())
                  products[nums[i]] = nums[j];  
                else products[nums[i]] += nums[j];
              }
  
          for(auto& p : products) p.second *= factor;
 
          ll sum = 0;
          for(auto& p : products) {
            ll carry = 0, exp = 0, y = 0, rem = 0;
            while(exp < size - 1) {  
              rem = (p.second + carry) % 10;
              carry = (p.second + carry) / 10;
              y += arith::power((ll)10, exp) * rem;
              exp++;
            }
            ll x = (p.first * factorials[size - 1] + carry);
            ll x_digits = arith::power((ll)10, (ll)size - 1);
            sum += x * x_digits + y;
          }
          printf("%lld\n", sum);
        }
    }
}
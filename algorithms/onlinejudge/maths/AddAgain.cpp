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
#include "utility/big_integer.cpp"
#include <bits/stdc++.h>


namespace arith = algorithms::onlinejudge::maths::utility::arithmetics;
namespace bi = algorithms::onlinejudge::maths::utility::big_integer;


using ull = unsigned long long;
using vi = std::vector<ull>;
using map_ll = std::unordered_map<ull, ull>;

constexpr ull MAX_FAC = 12;


ull do_factorial(ull n) {
  ull fac = 1;
  for(ull i = 1; i <= n; ++i)
    fac *= i;
  return fac;  
}

struct Summation_Unit
{
    int lead;
    map_ll els; // element with its freq
};


using v_sum_unit = std::vector<Summation_Unit>;

v_sum_unit split_into_summation_units(const vi& nums) {
  v_sum_unit units;
  std::unordered_set<int> used;
  for(int n : nums) {
    if(used.count(n)) continue;
    used.insert(n);
    vi tmp = nums;
    auto it = std::find(tmp.begin(), tmp.end(), n);
    tmp.erase(it);
    map_ll els;
    for(int el : tmp) els[el]++;
    units.push_back({n, els});
  }
  return units;
}


ull do_summation(int s, const Summation_Unit& unit, const std::array<ull, 13>& factorials) {
  int lead = unit.lead;
  map_ll els = unit.els;
  int s_tail = s - 1;
  // calculate the depth of factorial for a lead in unit
  int depth = factorials[s_tail];
  for(auto& p : els) 
    depth /= factorials[p.second];
  
  if(depth == 1 || els.empty()) { // in the form of lead x x x ..
    std::string sum_s = std::to_string(lead); 
    for(auto& p : els)
      for(int i = 1; i <= (int)p.second; ++i)
        sum_s += std::to_string(p.first);    
    return std::atoll(sum_s.c_str()); 
  }

  // multiplication factor: depth / count of elements
  int cnt = 0;
  for(auto& p : els) cnt += p.second;
  int multiplication_factor = depth / cnt;

  ull els_sum = 0;
  for(auto& p : els) 
    els_sum += p.first * p.second;
  els_sum *= multiplication_factor;

  // special case 3 [1 1 2 2], where 4 elements and the depth is 6
  if((depth % cnt)) {
    for(auto& p : els) {
      ull factor = p.second / (depth % cnt);
      els_sum += p.first * factor;
    }   
  }

  ull sum = lead * depth * arith::power<ull>((ull)10, (ull)s_tail);
  ull exp = 0, carry = 0, curr_el = els_sum;
  while(exp < (ull)s_tail) {
    ull rem = curr_el % 10;
    carry = curr_el / 10;
    sum += arith::power<ull>((ull)10, exp++) * rem;
    curr_el = els_sum + carry;
  }
  sum += arith::power<ull>((ull)10, exp) * carry;
  return sum;
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

        std::array<ull, 13> factorials;
        factorials[0] = 0;
        for(ull f = 1; f <= MAX_FAC; ++f)
          factorials[f] = do_factorial(f);

        int size;
        while(scanf("%d", &size) == 1 && size) {
          vi nums(size);
          for(int i = 0; i < size; ++i)
            scanf("%llu", &nums[i]);
         
          ull sum = 0;
          v_sum_unit units = split_into_summation_units(nums);
          for(auto& unit : units)
            sum += do_summation(size, unit, factorials);
          printf("%llu\n", sum);
        }
    }
}
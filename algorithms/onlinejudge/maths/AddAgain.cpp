/*
───────────────────────────────────────────────────────────────
🧳 UVa 11076 Add Again, https://onlinejudge.org/external/110/11076.pdf, 
       do not use next permutation for 12!, TLE;
       observe the digits in all permutations; 
       hint: the solution involves factorial  rt: s
───────────────────────────────────────────────────────────────
 *
 * --- Analysis: A Combinatorial Summation ---
 *
 * The problem asks for the sum of all unique numbers formed by permuting a given
 * set of N digits. A naive approach of generating every permutation and summing them
 * would be too slow (up to 12! permutations).
 *
 * The key insight is to calculate the sum column by column, exploiting the symmetry
 * of the permutations.
 *
 *
 * ### Step 1: The Column Sum Insight ###
 *
 * Due to the nature of permutations, each of the N digit positions (ones, tens, etc.)
 * is statistically identical. If we can calculate the sum of all digits in one column
 * (e.g., the ones column), the total sum can be found by multiplying this column
 * sum by the "repunit" 11...1 (N times).
 *
 *   Total Sum = (Sum of Ones Column) * (11...1)
 *
 *
 * ### Step 2: The Formula for the Column Sum ###
 *
 * The sum of a single column is the sum of each digit multiplied by the number of
 * times it appears in that column.
 *
 * - Total number of unique permutations: `NumPerms = N! / (c₁! * c₂! * ...)`
 *   (where cᵢ is the frequency of the i-th distinct digit).
 * - Number of times ANY digit appears in a given position is `NumPerms / N`.
 * - The sum of all digits in a column is therefore:
 *   `ColumnSum = (NumPerms / N) * (Sum of the original N digits)`
 *
 *
 * ### Step 3: The Overflow-Safe Calculation ###
 *
 * A direct calculation `(Sum * N! * Repunit) / (N * Denom)` risks overflowing
 * 64-bit integers. The key is to rearrange the terms to keep intermediate
 * values as small as possible. The `N` in the denominator cancels with `N!` in
 * the numerator, leaving `(N-1)!`.
 *
 *   `ColumnSum = (Sum_of_Digits * (N-1)!) / (c₁! * c₂! * ...)`
 *
 * By calculating this `ColumnSum` first, all intermediate products are guaranteed
 * to fit within an `unsigned long long`. The final multiplication `ColumnSum * Repunit`
 * also fits, as per the problem's guarantee on the final answer's size.
 *
 *
 * ### Final Algorithm ###
 *
 * 1. Pre-compute factorials up to 12.
 * 2. For each test case, read the N digits.
 * 3. Calculate the sum of the digits (`Sum_D`) and their frequencies (`cᵢ`).
 * 4. Calculate `ColumnSum` using the safe formula above.
 * 5. Calculate the Repunit for N.
 * 6. The final answer is `ColumnSum * Repunit`.
 *
 * This O(N) approach is efficient and numerically stable for the given constraints.
 *
 * =====================================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>


namespace arith = algorithms::onlinejudge::maths::utility::arithmetics;


using ll = long long;
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

ull do_summation_ull(int s, const Summation_Unit& unit, const std::array<ull, 13>& factorials) {
  // 1. Get properties
  int lead = unit.lead;
  map_ll tail_freqs = unit.els;
  int s_tail = s - 1;

  if(tail_freqs.empty()) return lead;

  // 2. Calculate depth (permutations of tail)
  ull depth = factorials[s_tail];
  for(auto const& [digit, freq] : tail_freqs) {
    depth /= factorials[freq];
  }

  // 3. Calculate lead contribution
  // This is the FIRST major overflow point.
  // lead * depth can be up to 9 * 11!/k! which is large.
  // power(10, s-1) can be up to 10^11.
  // Their product is ~10^19 or more.
  ull lead_sum = static_cast<ull>(lead) * depth;
  lead_sum *= arith::power<ull>(10, s_tail);

  // 4. Calculate tail sum
  ull tail_sum = 0;
  if(s_tail > 0) {
    // a. Sum of tail digits
    ll sum_d_tail = 0;
    for(auto const& [digit, freq] : tail_freqs) {
      sum_d_tail += digit * freq;
    }

    // b. Column Sum of the tail permutations
    // Numerator can overflow. depth * sum_d_tail might exceed ull max.
    ull col_sum_num = depth * sum_d_tail;
    ull col_sum_tail = col_sum_num / s_tail;
        
    // c. Repunit for the tail
    ull repunit_tail = 0;
    for(int i = 0; i < s_tail; ++i) {
      repunit_tail = repunit_tail * 10 + 1;
    }

    // d. Calculate full tail sum
    tail_sum = col_sum_tail * repunit_tail; // <-- POTENTIAL OVERFLOW
  }

  // 5. Final Sum
  // The addition can also overflow.
  ull total_sum = lead_sum + tail_sum; // <-- POTENTIAL OVERFLOW

  return total_sum;
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
            sum += do_summation_ull(size, unit, factorials);
          printf("%llu\n", sum);
        }
    }
}
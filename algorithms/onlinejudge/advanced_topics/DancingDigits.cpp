/*
───────────────────────────────────────────────────────────────
🧳 UVa 11198 Dancing Digits, https://onlinejudge.org/external/111/11198.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../maths/utility/permutations.cpp"
#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


namespace perm = algorithms::onlinejudge::maths::utility::permutations;


constexpr int SIZE = 8;
constexpr int FAC_8 = 40320;

using vi = std::vector<int>;
using vb = std::vector<bool>;
using vvb = std::vector<vb>;


vvb is_sum_i_j_prime(SIZE + 1, vb(SIZE + 1, false));


void init_is_sum_i_j_prime() {
  const bool is_prime[17] = { 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0 };
  for(int i = 1; i <= SIZE; ++i) {
    for(int j = 1; j <= SIZE; ++j) {
      is_sum_i_j_prime[i][j] = is_prime[i + j];
    }
  }
}

/**
 * 1. Gender / Polarity Classification
 * -----------------------------------
 * Problem Rule: 
 *   - Positive integers represent MALE digits (e.g., +3)
 *   - Negative integers represent FEMALE digits (e.g., -3)
 * 
 * Invariant: The gender of each digit NEVER changes during any dance move.
 */
enum Kind { FEMALE, MALE };

struct Digit
{
    /**
     * 2. val (Magnitude / Rank)
     * -------------------------
     * The absolute numerical value of the digit (1 to 8).
     * 
     * Target Condition:
     *   At the end, all digits must be arranged in strictly ascending order:
     *   val: 1, 2, 3, 4, 5, 6, 7, 8 (ignoring signs).
     */
    int val;

    /**
     * 3. kind (Gender)
     * ----------------
     * MALE if original input was positive, FEMALE if negative.
     * 
     * Dance Constraint:
     *   Two digits can ONLY dance if:
     *   (d1.kind != d2.kind) && is_prime(d1.val + d2.val)
     */
    Kind kind;

    // Helper to construct from signed integer: +3 -> (3, MALE), -3 -> (3, FEMALE)
    static Digit from_int(int signed_val) {
      return { std::abs(signed_val), signed_val > 0 ? MALE : FEMALE };
    }

    // Helper to convert back to signed integer
    int to_int() const {
      return kind == MALE ? val : -val;
    }

    /**
     * Strict Weak Ordering Comparator (<)
     * ------------------------------------
     * 1. Primary: Compare by absolute value 'val' (1 to 8).
     * 2. Secondary: Compare by 'kind' (MALE vs FEMALE) for deterministic behavior.
     * 
     * Defining this allows `std::vector<Digit>` to be used directly as a key 
     * in `std::set`, `std::map`, or sorted with `std::sort()`.
     */
    bool operator < (const Digit& other) const {
      return std::abs(val) < std::abs(other.val);
    }

    /**
     * Equality Operator (==)
     */
    bool operator == (const Digit& other) const {
        return val == other.val && kind == other.kind;
    }    
};

struct State
{
    std::vector<Digit> perm;
    int dances;
};

int get_perm_idx(const std::vector<Digit>& digits) {
  vi nums;
  for(auto d : digits) {
    nums.push_back(std::abs(d.to_int()));
  }
  return perm::getPermutationIndex(nums);
}


int get_min_dances(const std::vector<Digit>& digits) {

    std::vector<Digit> target = digits;
    std::sort(target.begin(), target.end());
  
    std::queue<State> queue;
    vb visited(FAC_8 + 1, false);
    // init
    queue.push({digits, 0});
    visited[get_perm_idx(digits)] = true;
    int target_perm_idx = get_perm_idx(target);
   
    int min_dances = -1;

    while(!queue.empty()) {
      State state = queue.front(); queue.pop();
      std::vector<Digit> curr_perm = state.perm;
      int dances_so_far = state.dances;

      if(get_perm_idx(curr_perm) == 
         target_perm_idx) {
        min_dances = dances_so_far;
        break;
      }

      for(int i = 0; i < SIZE; ++i) {
        Digit digit = curr_perm[i];
        int digit_val = std::abs(digit.to_int());


        for(int j = (i + 1) % SIZE; j != i; j = (j + 1) % SIZE) {
          Digit partner = curr_perm[j];
          int partner_val = std::abs(partner.to_int());
          if(digit.kind != partner.kind && 
             is_sum_i_j_prime[digit_val][partner_val]) {
            std::vector<Digit> base = curr_perm;
            base.erase(base.begin() + i);

            // ==========================================
            // CHOICE A: Move curr_digit to RIGHT of partner
            // ==========================================
            std::vector<Digit> right_perm = base;
            auto r_it = std::find(right_perm.begin(), right_perm.end(), partner);
            right_perm.insert(r_it + 1, digit);
            int right_perm_idx = get_perm_idx(right_perm);
            if(!visited[right_perm_idx]) {
              visited[right_perm_idx] = true;
              queue.push({right_perm, 1 + dances_so_far});
            }
            // ==========================================
            // CHOICE B: Move curr_digit to LEFT of partner
            // ==========================================
            std::vector<Digit> left_perm = base;
            auto l_it = std::find(left_perm.begin(), left_perm.end(), partner);
            left_perm.insert(l_it, digit);
            int left_perm_idx = get_perm_idx(left_perm);
            if(!visited[left_perm_idx]) {
              visited[left_perm_idx] = true;
              queue.push({left_perm, 1 + dances_so_far});
            }
          }
        }
      }
    }

    return min_dances;

}


namespace algorithms::onlinejudge::advanced_topics::dancing_digits
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

        //  init
        init_is_sum_i_j_prime();

        int t_case = 1;
        int first_val;
        // Read the 1st number; if it is 0 or EOF, terminate!
        while (std::cin >> first_val && first_val != 0) {
          std::vector<Digit> digits;
          digits.reserve(SIZE);
          digits.push_back(Digit::from_int(first_val));
          // Read the remaining 7 numbers
          for (int i = 1; i < SIZE; ++i) {
            int val;
            std::cin >> val;
            digits.push_back(Digit::from_int(val));
          }
          std::cout << "Case " << t_case++ << ": " << get_min_dances(digits) << "\n";
        }
    }
}
/**
 * Rabin-Karp String Matching Algorithm
 * 
 * T: The target Text string
 * P: The Pattern string we are searching for
 * d: The alphabet size (radix). Use 256 for standard ASCII.
 * q: A large prime number to act as the modulus (prevents overflow and collisions)
 */

#include <iostream>
#include <string>
#include <vector>


namespace algorithms::onlinejudge::strings::tools::Rabin_Karp
{
    void match(const std::string& T, const std::string& P, long long d, long long q, std::function<void(int)> func) {
      int n = T.length();
      int m = P.length();
        
      // Edge case: If the pattern is longer than the text, no match is possible
      if (m > n) return; 

      // h = d^(m-1) mod q
      // This is the weight of the highest-order digit in our window.
      // PREPROCESSING OPTIMIZATION NOTE:
      // ------------------------------------------------------------------------
      // We calculate h = d^(m-1) mod q in O(m) time using the simple loop below.
      //
      // For extremely large pattern lengths (m), you can optimize this to O(log m)
      // by using a Binary Exponentiation helper function:
      //     long long h = power(d, m - 1, q);
      //
      // Note: While the logarithmic power function is mathematically superior, 
      // the overall preprocessing stage of Rabin-Karp remains O(m) because we 
      // must still loop m times to calculate the initial hashes for P and T. 
      // However, the O(log m) version significantly reduces constant-factor overhead.
      // ========================================================================
      long long h = 1;
      for (int i = 0; i < m - 1; ++i) {
        h = (h * d) % q;
      }

      long long p = 0; // Hash of the pattern P
      long long t = 0; // Hash of the current window of Text T (t_s)

      // PREPROCESSING PHASE (Lines 6-8 in pseudocode)
      // Calculate the initial hashes for P and the first window of T (t_0)
      for (int i = 0; i < m; ++i) {
        p = (d * p + (unsigned char)P[i]) % q;
        t = (d * t + (unsigned char)T[i]) % q;
      }

      // MATCHING PHASE (Lines 9-14 in pseudocode)
      for (int s = 0; s <= n - m; ++s) {
        // Line 10: Check if hashes match
        if (p == t) {
          // Line 11: Spurious hit check (actual string comparison)
          // T.compare(start_pos, length, comparison_str) is highly optimized in C++
          if (T.compare(s, m, P) == 0) {
            func(s);
          }
        }

        // Line 13-14: Calculate hash for the next window (t_{s+1})
        if (s < n - m) {
          // --- THE NEGATIVE MODULO GUARD ---
          // In C++, the % operator on negative numbers remains negative (e.g. -5 % 3 = -2).
          // We add 'q' to the subtraction block to guarantee the result stays positive.
          long long high_order_digit_val = (T[s] * h) % q;
          long long remaining_window_hash = (t - high_order_digit_val + q) % q;
                
          // Slide the window: Multiply by d (shift left) and add the new character
          t = (d * remaining_window_hash + (unsigned char)T[s + m]) % q;
        }
      }
    }
}

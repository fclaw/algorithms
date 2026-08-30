#include <bits/stdc++.h>

using ll = long long;
using vi = std::vector<int>;;
using vll = std::vector<ll>;



namespace algorithms::onlinejudge::maths::utility::permutations
{
    using ll = long long;
    using vi = std::vector<int>;

    constexpr int MAX_N = 21;

    // 1. FACTORED-OUT COMPILE-TIME FACTORIAL TABLE (0 Runtime Cost!)
    // Precomputed factorials 0! to 20! (C++11 compatible)
    const ll fact[21] = {
        1LL,                        // 0!
        1LL,                        // 1!
        2LL,                        // 2!
        6LL,                        // 3!
        24LL,                       // 4!
        120LL,                      // 5!
        720LL,                      // 6!
        5040LL,                     // 7!
        40320LL,                    // 8!
        362880LL,                   // 9!
        3628800LL,                  // 10!
        39916800LL,                 // 11!
        479001600LL,                // 12!
        6227020800LL,               // 13!
        87178291200LL,              // 14!
        1307674368000LL,            // 15!
        20922789888000LL,           // 16!
        355687428096000LL,          // 17!
        6402373705728000LL,         // 18!
        121645100408832000LL,       // 19!
        2432902008176640000LL       // 20!
    };


    /**
     * Computes the 0-based lexicographical index of a permutation vector.
     * Complexity: O(N^2) time, O(1) memory (Zero heap allocations!).
     */
    inline ll getPermutationIndex(const vi& perm) {
        int n = perm.size();
        if (n == 0) return 0;

        ll index = 0;

        for (int i = 0; i < n; ++i) {
            int smaller = 0;
            // Count remaining elements to the right that are smaller
            for (int j = i + 1; j < n; ++j) {
                if (perm[j] < perm[i]) {
                    smaller++;
                }
            }
            // Use factored-out compile-time factorial array
            index += smaller * fact[n - 1 - i];
        }

        return index;
    }

    /**
     * (BONUS) Inverse Cantor Expansion: Converts integer ID -> Permutation Vector
     */
    inline vi getPermutationFromIndex(ll index, int n) {
        std::vector<int> candidates(n);
        for (int i = 0; i < n; ++i) candidates[i] = i + 1; // [1, 2, ..., n]

        vi perm(n);
        for (int i = 0; i < n; ++i) {
            ll f = fact[n - 1 - i];
            int pos = index / f;
            index %= f;

            perm[i] = candidates[pos];
            candidates.erase(candidates.begin() + pos);
        }
        return perm;
    }
}
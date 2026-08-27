#include <bits/stdc++.h>

using ll = long long;
using vi = std::vector<int>;;
using vll = std::vector<ll>;


namespace algorithms::onlinejudge::maths::utility::permutations
{
  // Computes the 0-based lexicographical index of a permutation vector
  ll getPermutationIndex(const vi& perm) {
    int n = perm.size();
    if (n == 0) return 0;

    // Precompute factorials up to N-1
    vll fact(n, 1);
    for (int i = 1; i < n; ++i) {
        fact[i] = fact[i - 1] * i;
    }

    ll index = 0;
    
    // Loop through each element in the vector
    for (int i = 0; i < n; ++i) {
      int smaller = 0;
      // Count how many remaining elements to the right are smaller
      for (int j = i + 1; j < n; ++j) {
        if(perm[j] < perm[i]) {
          smaller++;
        }
      }
      // Multiply by the factorial of the remaining positions
      index += smaller * fact[n - 1 - i];
    }

    return index;
  }
}

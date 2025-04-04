#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <numeric>
#include <algorithm>




typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<vvi> vvvi;
typedef std::unordered_set<std::string> ss;
typedef std::vector<std::vector<std::vector<int>>> mi;


std::pair<int, int> getLR(const vi& queue) 
{
    int maxSeen = 0;
    int l = 0;
    for (int h : queue)
      if (h > maxSeen)
      { l++; maxSeen = h; }

    maxSeen = 0;
    int r = 0;
    for(auto it = queue.rbegin(); it != queue.rend(); ++it)
      if (*it > maxSeen)
      { r++; maxSeen = *it; }

    return {l, r};
}


bool isValidQueue(const vi& queue, int T, int L) 
{
    int N = queue.size();

    // Step 1: Locate the tallest element
    auto it = std::find(queue.begin(), queue.end(), T);

    // Case 1: Tallest not yet placed
    if (it == queue.end()) {
        if (N < L) return true; // Defer validation, we're still building the ascending part
        return false;           // Too many elements, but tallest not placed — invalid
    }

    // Step 2: Check if tallest is at position L - 1 (0-based index)
    int pos = distance(queue.begin(), it);
    if (pos != L - 1 || queue[pos] != T) return false;

    // Step 3: Ensure ascending order up to pos
    for (int i = 1; i < pos; i++)
      if(queue[i] <= queue[i - 1]) return false;

    // Step 4: Ensure descending order after pos
    for (int i = pos + 1; i < N; i++)
      if (queue[i] >= queue[i - 1]) return false;

    return true;
}

bool prune(const vi& queue, int N, int l, int r, int L, int R)
{
    if(L + R == N + 1)
      return !isValidQueue(queue, N, L);
    return true;
}


namespace algorithms::onlinejudge::complete_search::queue
{
    /** https://onlinejudge.org/external/101/10128.pdf, 
     * backtracking with pruning; try up to all N! (13!)
     * permutations that satisfy the requirement; 
     * then pre-calculate the results */
    int tc, N, L, R;
    int backtrack(int mask, ss& used, vi& queue, const std::string& s, int l, int r)
    {
        // ll key = encodeKey(mask, l, r);
        if(prune(queue, N, l, r, L, R)) return 0;
        if(queue.size() == N)
        { return l == L && r == R ? 1 : 0; }

        int cnt = 0;
        for(int i = 1; i <= N; i++)
        {
            if((mask & (1 << i)))
              continue;

            std::string front = std::to_string(i) + s;
            std::string back = s + std::to_string(i);

            queue.emplace(queue.begin(), i);
            auto [front_l, front_r] = getLR(queue);
            if (!used.count(front))
              used.insert(front),
              cnt += backtrack(mask | (1 << i), used, queue, front, front_l, front_r);
            queue.erase(queue.begin());

            queue.push_back(i);
            auto [back_l, back_r] = getLR(queue);
            if (!used.count(back))
              used.insert(back),
              cnt += backtrack(mask | (1 << i), used, queue, back, back_l, back_r);
            queue.pop_back();
        }
        return cnt;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        scanf("%d\n", &tc);
        while(tc--)
        {
            scanf("%d %d %d\n", &N, &L, &R);
            vi queue;
            ss used;
            std::string s = {};
            printf("%d\n", backtrack(0, used, queue, s, 0, 0));
        }
    }
}
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <numeric>




typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<vvi> vvvi;
typedef std::unordered_set<std::string> ss;
typedef std::unordered_map<ll, int> mi;

inline ll encodeKey(int a, int b, int c) {
    return (1LL * a << 20) | (b << 10) | c;
}

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

bool prune(const vi& queue, int N, int l, int r, int L, int R)
{
    return false;
}


namespace algorithms::onlinejudge::complete_search::queue
{
    /** https://onlinejudge.org/external/101/10128.pdf, 
     * backtracking with pruning; try up to all N! (13!)
     * permutations that satisfy the requirement; 
     * then pre-calculate the results */
    int tc, N, L, R;
    ss invalid;
    int backtrack(int mask, ss& used, vi& queue, mi& memo, const std::string& s, int l, int r)
    {
        if(prune(queue, N, l, r, L, R)) return 0;
        int perm = std::atoi(s.c_str());
        ll key = encodeKey(perm, l, r);
        if(queue.size() == N)
        { return l == L && r == R ? 1 : 0; }
  
        if(memo.count(key)) return memo[key];

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
              cnt += backtrack(mask | (1 << i), used, queue, memo, front, front_l, front_r);
            queue.erase(queue.begin());

            queue.push_back(i);
            auto [back_l, back_r] = getLR(queue);
            if (!used.count(back))
              used.insert(back),
              cnt += backtrack(mask | (1 << i), used, queue, memo, back, back_l, back_r);
            queue.pop_back();
        }
        return memo[key] = cnt;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        scanf("%d\n", &tc);
        while(tc--)
        {
            invalid.clear();
            scanf("%d %d %d\n", &N, &L, &R);
            vi queue;
            ss used;
            mi memo;
            std::string s = {};
            printf("%d\n", backtrack(0, used, queue, memo, s, 0, 0));
        }
    }
}
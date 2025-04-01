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
typedef std::unordered_set<std::string> ss;
typedef std::unordered_map<std::string, ll> mll;


bool leftPrune(const vi& queue, int L) {
    int maxSeen = 0, visible = 0;
    for (int h : queue) {
        if (h > maxSeen) {
            visible++;
            maxSeen = h;
        }
    }
    return visible <= L;  // prune if already exceeds L
}

bool rightPrune(const vi& queue, int R) {
    int maxSeen = 0, visible = 0;
    for (auto it = queue.rbegin(); it != queue.rend(); ++it) {
        if (*it > maxSeen) {
            visible++;
            maxSeen = *it;
        }
    }
    return visible <= R;
}

int countVisible(const vi& queue) {
    int maxSeen = 0, visible = 0;
    for (int h : queue) {
        if (h > maxSeen) {
            visible++;
            maxSeen = h;
        }
    }
    return visible;
}

int countVisibleReversed(const vi& queue) {
    int maxSeen = 0, visible = 0;
    for (auto it = queue.rbegin(); it != queue.rend(); ++it) {
        if (*it > maxSeen) {
            visible++;
            maxSeen = *it;
        }
    }
    return visible;
}

bool finalCheck(const vi& queue, int L, int R) 
{ return countVisible(queue) == L && countVisibleReversed(queue) == R; }

bool bothTallest(int L, int R) { return L == 1 && R == 1; }

bool severalFromLeft(const vi& queue, int N, int L)
{
    return L > 1 && !queue.empty() && queue.front() == N ? false : true;
}

bool severalFromRight(const vi& queue, int N, int R)
{
    return R > 1 && !queue.empty() && queue.back() == N ? false : true;
}


namespace algorithms::onlinejudge::complete_search::queue
{
    /** https://onlinejudge.org/external/101/10128.pdf, 
     * backtracking with pruning; try up to all N! (13!)
     * permutations that satisfy the requirement; 
     * then pre-calculate the results */
    int tc, N, L, R;
    ss invalid;
    ll backtrack(int mask, ss& used, vi& queue, mll& memo, const std::string& s)
    {
        if(bothTallest(L, R) ||
           (!severalFromLeft(queue, N, L) &&
           !severalFromRight(queue, N, R)))
          return 0;

        if(queue.size() == N)
        { return memo[s] = finalCheck(queue, L, R) ? 1 : 0; }
        
        bool is_right = rightPrune(queue, R);
        bool is_left = leftPrune(queue, L);

        if(!is_right && !is_left) { return 0; }

        if(memo.count(s)) return memo[s];

        ll cnt = 0;
        for(int i = 1; i <= N; i++)
        {
            if((mask & (1 << i)))
              continue;

            std::string front = std::to_string(i) + s;
            std::string back = s + std::to_string(i);

            queue.emplace(queue.begin(), i);
            if (!used.count(front))
              used.insert(front),
              cnt += backtrack(mask | (1 << i), used, queue, memo, front);
            queue.erase(queue.begin());

            queue.push_back(i);
            if (!used.count(back))
              used.insert(back),
              cnt += backtrack(mask | (1 << i), used, queue, memo, back);
            queue.pop_back();
        }
        return memo[s] = cnt;
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
            mll memo;
            std::string s = {};
            printf("%llu\n", backtrack(0, used, queue, memo, s));
        }
    }
}
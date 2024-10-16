#include <vector>
#include <unordered_map>
#include <algorithm>

namespace algorithms::dp::leetcode::boxes
{

#define loop(x, s, n) for(int x = s; x < n; x++)
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<std::vector<int>> table;


    // https://leetcode.com/problems/remove-boxes
    /** You are given several boxes with different colors represented by different positive numbers.
     *  You may experience several rounds to remove boxes until there is no box left. 
     *  Each time you can choose some continuous boxes with the same color (i.e., composed of k boxes, k >= 1), 
     *  remove them and get k * k points. Return the maximum points you can get. 
     *  objective function: f(i, j) = n */

    std::tuple<int, int, int> getCount(const vi& boxes, int p, int l, int r)
    {
        int cnt = 1, cnt_l = 0, cnt_r = 0;
        int i = p - 1;
        // left
        while(i >= l && boxes[i] == boxes[p]) { ++cnt_l; --i; }
        // right
        int j = p + 1;
        while(j < r && boxes[j] == boxes[p]) { ++cnt_r; ++j; }
        i = cnt_l == 0 ? p - 1 : i;
        j = cnt_r == 0 ? p + 1 : j;
        return {cnt + cnt_r + cnt_l, i, j};
    }

    std::optional<std::tuple<int, int, int>> getCountBind(const vi& boxes, int v, int s, int l) 
    {
        int low = l, upper = s;
        while(s >= low && boxes[s] != v) --s;
        while(l < upper && boxes[l] != v) ++l;
        if(l > s) return std::nullopt;

        int cnt = std::count(boxes.begin() + l, boxes.begin() + ++s, v);
        return std::make_tuple(cnt, l, s);
    }

    int getMax(const vi& boxes, int l, int r, table& memo)
    {
        if(l > r) return 0;

        int &res = memo[l][r];
        if(~res) return memo[l][r];
 

        res = 0;
        loop(i, l, r)
        {
            int cnt, nl, nr;
            auto t = getCount(boxes, i, l, r);
            std::tie(cnt, nl, nr) = t;;
            // two segments left to handle: left (l, nr), right (nl, r) 
            int left = getMax(boxes, l, nl, memo);
            int right = getMax(boxes, nr, r, memo);

            auto obl = getCountBind(boxes, boxes[i], nl, l);
            int rl = nl + 1, lb_cnt = 0;
            if(obl.has_value())
            {
                auto tpl = obl.value();
                int c = (cnt + std::get<0>(tpl));
                lb_cnt = c * c + getMax(boxes, std::get<2>(tpl), nl + 1, memo);
                rl = std::get<1>(tpl);
            }

            auto obr = getCountBind(boxes, boxes[i], r, nr);
            int rr = nr, rb_cnt = 0;
            if(obr.has_value()) 
            {
                auto tpl = obr.value();
                int c = (cnt + std::get<0>(tpl));
                rb_cnt = c * c + getMax(boxes, nr, std::get<1>(tpl), memo);
                rr = std::get<2>(tpl);
            }

            int bind = lb_cnt + rb_cnt + std::max(getMax(boxes, rr, r, memo), getMax(boxes, l, rl, memo));
            int separate = cnt * cnt + std::max(left, right);
            res = std::max(res, std::max(separate, bind));
        }
        return res;
    }
    int removeBoxes(const vi& boxes) 
    { table memo = vvi(boxes.size() + 1, vi(boxes.size() + 1, -1)); return getMax(boxes, 0, boxes.size(), memo); }
}
#include <vector>
#include <unordered_map>
#include <algorithm>

namespace algorithms::dp::leetcode::boxes
{

#define loop(x, s, n) for(int x = s; x < n; x++)
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<std::pair<int, int>> vp;
typedef std::vector<std::vector<int>> table;


    // https://leetcode.com/problems/remove-boxes
    /** You are given several boxes with different colors represented by different positive numbers.
     *  You may experience several rounds to remove boxes until there is no box left. 
     *  Each time you can choose some continuous boxes with the same color (i.e., composed of k boxes, k >= 1), 
     *  remove them and get k * k points. Return the maximum points you can get. 
     *  objective function: f(i, j) = n */

    std::tuple<int, int, int> getCount(const vi& boxes, int p, int l, int r)
    {
        int cnt_l = 0, cnt_r = 0;
        int i = p - 1;
        // left
        while(i >= l && boxes[i] == boxes[p]) { ++cnt_l; --i; }
        // right
        int j = p + 1;
        while(j < r && boxes[j] == boxes[p]) { ++cnt_r; ++j; }
        i = cnt_l == 0 ? p : ++i;
        j = cnt_r == 0 ? p + 1 : j;
        return std::make_tuple(cnt_r + cnt_l, i, j);
    }

    std::tuple<int, int, vp> getBindLeft(const vi& boxes, int target, int s, int e) 
    {
        int i = s;
        vp segs = {};
        while(i < e && boxes[i] != target) ++i;
        int cnt = std::count(boxes.begin() + i, boxes.begin() + e, target);
        if(cnt == 0) return std::make_tuple(0, e, segs); 
        
        int start = i;
        while(start < e)
        {
            while(boxes[start] == target) ++start;
            int end = start;
            while(boxes[end] != target) ++end;
            segs.push_back({start, end});
            start = end;
        }
 
       return std::make_tuple(cnt, i, segs);
    }

    std::tuple<int, int, vp> getBindRight(const vi& boxes, int target, int s, int e)
    {
        int i = s;
        vp segs = {};
        while(--i >= e && boxes[i] != target);
        int cnt = std::count(boxes.begin() + e, boxes.begin() + i + 1, target);
        if(cnt == 0) return std::make_tuple(0, e, segs);

        int end = i;
        while(end >= e)
        {
            while(boxes[end] == target) --end;
            int start = end;
            while(boxes[start] != target) --start;
            segs.push_back({start + 1, end + 1});
            end = start;
        }
        
        return std::make_tuple(cnt, i + 1, segs);
    }

    int getMax(const vi& boxes, int l, int r, table& memo)
    {
        if(l > r) return 0;

        int &res = memo[l][r];
        if(~res) return memo[l][r];

        res = 0;
        loop(i, l, r)
        {
            int cnt_p = 0, nl, nr;
            auto t = getCount(boxes, i, l, r);
            std::tie(cnt_p, nl, nr) = t;
            // two segments left to handle: left (l, nr), right (nl, r) 
            int left = getMax(boxes, l, nl, memo);
            int right = getMax(boxes, nr, r, memo);
            
            auto left_bind = getBindLeft(boxes, boxes[i], l, nl); 
            auto right_bind = getBindRight(boxes, boxes[i], r, nr);

            int cnt = ++cnt_p + std::get<0>(left_bind) + std::get<0>(right_bind);

            vp segs = std::get<2>(left_bind);
            segs.insert(segs.end(), (std::get<2>(right_bind)).begin(), (std::get<2>(right_bind)).end());
            int seg_max = 0;
            for(auto t : segs) seg_max += getMax(boxes, t.first, t.second, memo);
            int bindsMax = std::max(getMax(boxes, std::get<1>(right_bind), r, memo), getMax(boxes, l, std::get<1>(left_bind), memo));
            int separate = cnt_p * cnt_p + std::max(left, right);
            int bind = cnt * cnt + seg_max + bindsMax;
            // cout << "--------- start -------\n";
            // cout << "i: " << i << ", val: " << boxes[i] << "\n";
            // cout << "cnt * cnt: " << cnt * cnt << "\n";
            // cout << "left: l: " << l << ", r: " << std::get<1>(left_bind) << ", val: " << getMax(boxes, l, std::get<1>(left_bind), memo) << "\n";
            // cout << "right: l: " << std::get<1>(right_bind) << ", r: " << r << ", val: " << getMax(boxes, std::get<1>(right_bind), r, memo) << "\n";
            // cout << "seg: " << seg_max << "\n";
            // cout << "left: " << left << "\n";
            // cout << "right: " << right << "\n";
            // cout << "separate: " << separate << "\n";
            // cout << "bind: " << bind << "\n";
            // cout << "--------- end -------\n";

            res = std::max(res, std::max(separate, bind));
        }
        return memo[r][l] = res;
    }
    int removeBoxes(const vi& boxes) 
    { table memo = vvi(boxes.size() + 1, vi(boxes.size() + 1, -1)); return getMax(boxes, 0, boxes.size(), memo); }
}
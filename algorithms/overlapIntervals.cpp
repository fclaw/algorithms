#include <vector>
#include <iostream>

namespace leetcode 
{
    // https://leetcode.com/problems/non-overlapping-intervals
    int eraseOverlapIntervals(std::vector<std::vector<int>>& intervals) 
    {
        if(intervals.size() <= 1)
          return 0;

        std::sort(
          intervals.begin(), 
          intervals.end(), 
          [](auto x, auto y) 
          { 
              return x[0] == y[0] ? x[1] < y[1] : x[0] < y[0]; 
          } );

        int counter = 0;
        auto curr_interval = intervals[0];
        int i = 0;
        while(++i < intervals.size())
        { 
            if(curr_interval[1] < intervals[i][1] &&
               curr_interval[1] > intervals[i][0] || 
               curr_interval[0] >= intervals[i][0] &&
               curr_interval[1] >= intervals[i][1])
                counter++;

            if (intervals[i][0] > curr_interval[1])
              curr_interval = intervals[i];
        };

        return counter;
    }
}
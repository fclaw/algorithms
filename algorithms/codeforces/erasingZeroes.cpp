#include <string>

namespace algorithms::codeforces
{
    // https://codeforces.com/problemset/problem/1303/A
    /*
       You are given a string s.
       Each character is either 0 or 1.
       You want all 1's in the string to form a contiguous subsegment. 
       For example, if the string is 0, 1, 00111 or 01111100, then all 1's form a contiguous subsegment, 
       and if the string is 0101, 100001 or 11111111111101, then this condition is not met.
       You may erase some (possibly none) 0's from the string. What is the minimum number of 0's that you have to erase?
    */
    int eraseZero(std::string s)
    {
        int first = 0;
        while(s[first] - '0' == 0)
          first++;
        
        int last = s.size() - 1;
        while(s[last] - '0' == 0)
          last--;

        int minZeros = 0;
        while(first < last)
        {
            if(s[first] - '0' == 0)
            {
                int second = first;
                while(second < last && 
                      s[second] - '0' == 0)
                {
                    second++;
                    minZeros++;
                }
                first = second;   
            } else first++;
        }

        return minZeros;
    }
}
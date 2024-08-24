#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>

namespace algorithms::backtrack::leetcode::ip
{

using ips = std::vector<std::string>;
using st = std::vector<std::string>;

    /**
     *  https://leetcode.com/problems/restore-ip-addresses
     *  A valid IP address consists of exactly four integers separated by single dots. 
     *  Each integer is between 0 and 255 (inclusive) and cannot have leading zeros.
     *  For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses, 
     *  but "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses.
     *  Given a string s containing only digits, return all possible valid IP addresses 
     *  that can be formed by inserting dots into s. 
     *  You are not allowed to reorder or remove any digits in s. 
     *  You may return the valid IP addresses in any order.
     */
     const std::string point = ".";
     const int N = 4;
     ips ans;
     bool checkIp(const st& xs)
     {
          if(xs.size() != N)
            return false;
          bool res = true;
          for(auto x : xs)
            if((x.size() > 1 && 
                std::stoi(std::string(1, x[0])) == 0) || 
               std::stoi(x) > 255)
            {
                 res = false;
                 break;
            }
          return res;  
     }
     std::string join(const st& xs)
     {
        std::string s;
        for(auto x : xs)
          s += x + ".";
        s.pop_back();
        return s;  
     }
     void backtrack(const std::string& s, int idx, st& xs, ips& ans)
     {
        if(idx == s.size())
        {
            if(checkIp(xs)) 
              ans.push_back(join(xs));
            return;
        }
        xs.push_back(s.substr(idx, 1));
        backtrack(s, idx + 1, xs, ans);
        if(!xs.empty())
        {
            xs.pop_back();
            if(xs.size() >= 1)
            {
                auto p = xs.back();
                xs[xs.size() - 1] = p + s.substr(idx, 1);
                backtrack(s, idx + 1, xs, ans);
            }
        }
     }     
     ips restoreIpAddresses(std::string s)
     {
        ips ans;
        std::vector<std::string> tmp;
        backtrack(s, 0, tmp, ans);
        return ans;
     }
}
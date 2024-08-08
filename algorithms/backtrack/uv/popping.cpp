#include <cstdio>
#include <string>
#include <iostream>

namespace algorithms::backtrack::uv
{
    // https://onlinejudge.org/external/12/1261.pdf
    /**
     * We are given a string s of two characters ‘a’ and ‘b’. Let a group be a maximal consecutive substring
     * of the same character. Any group g of s of length at least two can be removed (or popped) and a new
     * string is constructed by concatenating the remaining left and right substrings of s. We repeat this
     * process until either the string becomes the empty string or there is no more group of length at least two.
     * For example, string s = babbbaaabb has 5 groups b, a, bbb, aaa, and bb. The string s can be turned
     * into the empty string by popping groups in the following sequence (the underlined group is to be popped in the sequence):
     * babbbaaabb → baaaabb → bbb → empty string
     * But the group may not turn to an empty string by a different sequence of pop operations:
     * babbbaaabb → babbbaaa → baaaa → b
     * Given a string, write a program to decide whether the string can be turned into the empty string 
     * by some sequence of popping operations.
     */
      bool solve_uv_1261(std::string s) { return false; }
      void submit_uv_1261()
      {
           int TC;
           scanf("%d", &TC);
           while(--TC >= 0)
           {
               std::string s;
               std::cin >> s;
               printf("%d\n", solve_uv_1261(s));
           }
      }
}
#include <vector>
#include <iostream>

namespace algorithms::codeforces
{
    /*
      https://codeforces.com/problemset/problem/996/A
      Allen has a LOT of money. He has 𝑛 dollars in the bank. 
      For security reasons, he wants to withdraw it in cash (we will not disclose the reasons here). 
      The denominations for dollar bills are 1, 5, 10, 20, 100. 
      What is the minimum number of bills Allen could receive after withdrawing his entire balance?
    */
    int minNotesRec(int sum, std::vector<int> notes)
    {
        if(sum == 0)
          return 0;

        int localMin;
        for (int i = 0; i < notes.size(); i++)
        {
            if(sum - notes[i] < 0)
              continue;
            localMin = 1 + std::min(localMin, minNotesRec(sum - notes[i], notes));
        }

        return localMin;
    } 

    int minNotesDp(int sum, std::vector<int> notes)
    {
        int n = notes.size();
        std::vector<int> dp(sum + 1, 0);

        for (int s = 1; s <= sum ; s++)
          for (int i = 0; i < n; i++)
          {
              if(s - notes[i] < 0)
                continue;
              dp[s] = 1 + dp[s - notes[i]];
          }

        return dp[sum];
    }

    /*
       The problem is to minimize 𝑥1+𝑥2+𝑥3+𝑥4+𝑥5
       given that 𝑥1+5𝑥2+10𝑥3+20𝑥4+100𝑥5=𝑛.
       It is pretty simple to see that we can operate greedily: take as many 100 as we can, then 20, then 10, etc.
       The solutions works because each number in the sequence 1, 5, 10, 20, 100 is a divisor of the number after it.
    */
     int minNotesGreedy(int sum, std::vector<int> notes)
     {
          int res = 0;
          int s = sum;
          int n = notes.size();
          for (int i = n - 1; i >= 1; i--)
          {
            while(s >= notes[i])
            {  
                res += (s / notes[i]);
                s %= notes[i];
            };
          }
          
          return res + s;
     }

    int minNotes(int sum, std::vector<int> notes) { return minNotesGreedy(sum, notes); }
}
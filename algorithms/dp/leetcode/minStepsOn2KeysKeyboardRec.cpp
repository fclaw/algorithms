

namespace algorithms::dp::leetcode
{

    /*
      The following function prime checks if a given integer n is prime. The function
      attempts to divide n by all integers between 2 and ⌊√n⌋, and if none of them divides
      n, then n is prime.
    */
    bool isPrime(int n)
    {
        if(n < 2)
          return true;
        for (int x = 2; x * x <= n; x++)
          if(n % x == 0)
            return false;
        return true;
    }

    int leastDivisorForOdd(int n)
    {
       int ld;
       int init = (n / 2) % 2 == 0 ? n / 2 - 1 : n / 2;
       // iterate from 3 to sqrt(n)
       for (int i = init; i >= 1; i -= 2)
          if (n % i == 0)
          {
            ld = i;
            break;
          }
       return ld;
    }

    // https://leetcode.com/problems/2-keys-keyboard
    // There is only one character 'A' on the screen of a notepad. You can perform one of two operations on this notepad for each step:
    // Copy All: You can copy all the characters present on the screen (a partial copy is not allowed).
    // Paste: You can paste the characters which are copied last time.
    // Given an integer n, return the minimum number of operations to get the character 'A' exactly n times on the screen.
    int minStepsOn2KeysKeyboardRec(int n)
    {
        if(n == 1)
          return 0;

        if(isPrime(n))
          return n;

        if(n & 1 == 0)
           return minStepsOn2KeysKeyboardRec(n / 2) + 2;
        else
        {
            int d = leastDivisorForOdd(n);
            int steps = n / d;
            return minStepsOn2KeysKeyboardRec(d) + steps;
        }  
    } 

    int minStepsOn2KeysKeyboard(int n) { return minStepsOn2KeysKeyboardRec(n); }
}
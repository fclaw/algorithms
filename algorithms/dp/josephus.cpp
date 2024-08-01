

/**
 *   Legend has it that Josephus wouldn't have lived to become famous 
 *   without his mathematical talents. During the Jewish{Roman war, 
 *   he was among a band of 41 Jewish rebels trapped in a cave by the Romans. 
 *   Preferring suicide to capture, the rebels decided to form a circle and, 
 *   proceeding around it, to kill every third remaining person until no one was left. 
 *   But Josephus, along with an unindicted co-conspirator, wanted none of this suicide nonsense; 
 *   so he quickly calculated where he and his friend should stand in the vicious circle
*/
namespace algorithms::dp
{
    int josephus(int n)
    {
        // J(1) = 1;
        if(n == 1)
          return 1;
        
        return !(n % 2) ? 2 * josephus(n/2) - 1 : 2 * josephus(n/2) + 1;
    }
}

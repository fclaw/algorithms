#include <vector>


namespace algorithms::backtrack::framework
{

typedef std::vector<int> vi;

struct Input
{
};


// global flag allows for premature termination
bool finished = false;
int N;

 
  /** This Boolean function tests whether the first k
   *  elements of vector a from a complete solution for the given problem. The last
   *  argument, input, allows us to pass general information into the routine. We
   *  can use it to specify n—the size of a target solution. This makes sense when
   *  constructing permutations or subsets of n elements, but other data may be
   *  relevant when constructing variable-sized objects such as sequences of moves in a game. */
  bool is_a_solution(const vi& vs, int k, const Input& input) 
  { return false; }
  /** This routine prints, counts, or however processes a complete solution once it is constructed */
  void process_solution(const vi& vs, int k, Input& input) {}
  /** This routine fills in an array c with the complete set of possible candidates for the kth position of
   *  a, given the contents of the first k− 1 positions. The number of candidates
   *  returned in this array is denoted by N. Again, input may be used to pass auxiliary information */
  void construct_candidates() {}
  void make_move() {}
  void reverse_move() {}
  void backtrack(const vi& vs, int k, Input& input) 
  {
       if (is_a_solution(vs, k, input))
         process_solution(vs, k, input);
       else 
       {
          ++k;
          construct_candidates();
          for (int i = 0; i < N; i++)
          {
             // a[k] = c[i];
             make_move();
             backtrack(vs, k, input);
             reverse_move();
             /* terminate early */
             if (finished) return;
          }
       }
  }

}
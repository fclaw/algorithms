#pragma once
#include <vector>


namespace algorithms::backtrack::framework
{


#define loop(x, s, n) for(int x = s; x < n; x++)
typedef std::vector<int> vi;

struct Aux {};


// global flag allows for premature termination
bool finished = false;
int N;

 
  /** This Boolean function tests whether the first k
   *  elements of vector a from a complete solution for the given problem. The last
   *  argument, input, allows us to pass general information into the routine. We
   *  can use it to specify n—the size of a target solution. This makes sense when
   *  constructing permutations or subsets of n elements, but other data may be
   *  relevant when constructing variable-sized objects such as sequences of moves in a game. */
  bool is_a_solution(const vi& vs, int k, const Aux& aux) 
  { return false; }
  /** This routine prints, counts, or however processes a complete solution once it is constructed */
  void process_solution(const vi& vs, int k, Aux& aux) {}
  /** This routine fills in an array c with the complete set of possible candidates for the kth position of
   *  a, given the contents of the first k− 1 positions. The number of candidates
   *  returned in this array is denoted by N. Again, input may be used to pass auxiliary information */
  void construct_candidates(const vi& vs, int k, const Aux& aux, vi& candidates) {}
  void make_move(vi& vs, int k, const Aux& aux) {}
  void reverse_move() {}
  void backtrack(vi& vs, int k, Aux& aux) 
  {
      vi candidates; /* candidates for next position */
      int n_candidates = 0; /* next position candidate count */ 
       if (is_a_solution(vs, k, aux)) 
         process_solution(vs, k, aux);
       else 
       {
          k += 1;
          construct_candidates(vs, k, aux, candidates);
          loop(i, 0, candidates.size())
          {
             vs.push_back(candidates[i]);
             make_move(vs, k, aux);
             backtrack(vs, k, aux);
             reverse_move();
             /* terminate early */
             if (finished) return;
          }
       }
  }

}
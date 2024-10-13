#include <vector>


namespace algorithms::backtrack::framework::subset
{

#define loop(x, s, n) for(int x = s; x < n; x++)
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

// global flag allows for premature termination
// bool finished = false;

int N;
vvi subsets;

 
  /** This Boolean function tests whether the first k
   *  elements of vector a from a complete solution for the given problem. The last
   *  argument, input, allows us to pass general information into the routine. We
   *  can use it to specify n—the size of a target solution. This makes sense when
   *  constructing permutations or subsets of n elements, but other data may be
   *  relevant when constructing variable-sized objects such as sequences of moves in a game. */
  bool is_a_solution(const vi& vs, int k) { return k == N; }
  /** This routine prints, counts, or however processes a complete solution once it is constructed */
  void process_solution(const vi& in, const vi& vs) 
  {
      vi tmp;
      loop(i, 0, vs.size())
        if((bool)vs[i]) 
          tmp.push_back(in[i]); 
      subsets.push_back(tmp); 
  }
  /** This routine fills in an array c with the complete set of possible candidates for the kth position of
   *  a, given the contents of the first k− 1 positions. The number of candidates
   *  returned in this array is denoted by N. Again, input may be used to pass auxiliary information */
  void construct_candidates(vi& candidates) 
  {
       candidates.push_back(1);
       candidates.push_back(0);
  }

  void backtrack(const vi& in, vi& vs, int k) 
  {
       vi candidates; /* candidates for next position */
       if (is_a_solution(vs, k)) 
         process_solution(in, vs);
       else 
       {
          construct_candidates(candidates);
          loop(i, 0, candidates.size())
            vs[k] = candidates[i],
            backtrack(in, vs, k + 1);
       }
  }
}
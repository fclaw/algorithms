// #include "algorithms/onlinejudge/complete_search/dna.cpp"
#include "algorithms/backtrack/leetcode/jobs.cpp"
#include <iostream>

int main(int argc, char* argv[])
{
  
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- ... ---\n";
    
    // std::optional<char*> file = std::nullopt;
    // if(argc > 1) file = std::make_optional(argv[1]);

    // algorithms::onlinejudge::complete_search::dna::submit(file);
    std::cout << algorithms::backtrack::leetcode::jobs::minimumTimeRequired({1,2,4,7,8}, 2);
}
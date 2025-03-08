#include "algorithms/onlinejudge/complete_search/hamiltonianCycle.cpp"



int main(int argc, char* argv[])
{
  
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- ... ---\n";
    
    std::optional<char*> file = std::nullopt;
    if(argc > 1) file = std::make_optional(argv[1]);

    algorithms::onlinejudge::complete_search::hamiltonian_cycle::submit(file);
}
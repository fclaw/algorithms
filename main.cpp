#include "algorithms/onlinejudge/complete_search/runaround.cpp"
#include <chrono>
#include <iomanip>


int main(int argc, char* argv[])
{  
    std::optional<char*> file = std::nullopt;
    if(argc > 1) file = std::make_optional(argv[1]);

    auto start = std::chrono::system_clock::now();
    // algorithm starts
    algorithms::onlinejudge::complete_search::runaround::submit(file);
    
    // std::cout << algorithms::onlinejudge::complete_search::runaround::isRunaround(xs);
    // std::cout << "\n";
    // algorithm ends
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << std::endl << "time: " <<  std::fixed << std::setprecision(1) << (double)elapsed.count() / 1000 << "s\n";

}
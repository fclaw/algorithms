#include "algorithms/onlinejudge/complete_search/firetruck.cpp"
#include <chrono>


int main(int argc, char* argv[])
{
  
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "--- ... ---\n";
    
    std::optional<char*> file = std::nullopt;
    if(argc > 1) file = std::make_optional(argv[1]);

    auto start = std::chrono::system_clock::now();
    // algorithm starts
    algorithms::onlinejudge::complete_search::firetruck::submit(file);
    // algorithm ends
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cout << "time: " << elapsed.count() << "s\n";
}
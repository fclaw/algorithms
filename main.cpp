#include "algorithms/onlinejudge/complete_search/bishop.cpp"
#include <chrono>


int main(int argc, char* argv[])
{  
    std::optional<char*> file = std::nullopt;
    if(argc > 1) file = std::make_optional(argv[1]);

    auto start = std::chrono::system_clock::now();
    // algorithm starts
    algorithms::onlinejudge::complete_search::bishop::submit(file);
    // algorithm ends
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cout << std::endl << "time: " << elapsed.count() << "s\n";

}
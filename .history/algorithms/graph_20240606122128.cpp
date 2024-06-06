#include <iostream>
#include <vector>

class Graph {
private:
    std::vector<std::vector<int>> adjList;
public:
    Graph(int vertices) 
    {
        adjList.resize(vertices);
    }

    Graph* addEdge(int vertex1, int vertex2) 
    {
        adjList[vertex1].push_back(vertex2);
        // adjList[vertex2].push_back(vertex1);  // For undirected graph
        return this;
    }

    void display() const 
    {
        for (size_t i = 0; i < adjList.size(); ++i) {
            std::cout << i << " : ";
            for (const auto& neighbor : adjList[i]) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }
    }
};
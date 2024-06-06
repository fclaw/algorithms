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

class WeightedGraph {
private:
// Adjacency list: each vertex has a list of pairs (neighbor, weight)
    std::vector<std::vector<std::pair<int, int>>> adjList;
public:
    WeightedGraph(int vertices) 
    {
        adjList.resize(vertices);
    }

    void addEdge(int vertex1, int vertex2, int weight) 
    {
        adjList[vertex1].emplace_back(vertex2, weight);
        adjList[vertex2].emplace_back(vertex1, weight);  // For undirected graph
    }

    void display() const 
    {
        for (size_t i = 0; i < adjList.size(); ++i) {
            std::cout << "Vertex " << i << ":\n";
            for (const auto& neighbor : adjList[i]) {
                std::cout << " -> (Vertex: " << neighbor.first << ", Weight: " << neighbor.second << ")\n";
            }
            std::cout << std::endl;
        }
    }
};
#include <iostream>
#include <vector>
#include <queue>
#include <set>

class Graph {
private:
    std::vector<std::vector<int>> adjList;
public:
    Graph(int vertices) 
    {
        adjList.resize(vertices);
    }

    Graph* addEdge(int source, int dest) 
    {
        adjList[source - 1].push_back(dest);
        // adjList[vertex2].push_back(vertex1);  // For undirected graph
        return this;
    }

    void display() const 
    {
        for (size_t i = 1; i < adjList.size(); ++i) {
            std::cout << i << " : ";
            for (const auto& neighbor : adjList[i - 1]) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }
    }

    int getVertices() { return adjList.size(); }

    std::vector<int> getAdjacentNodes(int node) { return adjList[node]; }
};

class WeightedGraph {
private:
    // Adjacency list: each vertex has a list of pairs (neighbor, weight)
    std::vector<std::vector<std::pair<int, int>>> adjList;
    std::set<int> vertexes;
public:
    WeightedGraph(int vertices) 
    {
        adjList.resize(vertices);
    }

    WeightedGraph* addEdge(int source, int dest, int weight) 
    {
        adjList[source - 1].emplace_back(dest, weight);
        vertexes.insert(source);
        vertexes.insert(dest);
        // adjList[vertex2].emplace_back(vertex1, weight);  // For undirected graph
        return this;
    }

    void display() const 
    {
        for (auto v : vertexes) {
            std::cout << "Vertex " << v << ":\n";
            for (const auto& neighbor : adjList[v]) {
                std::cout << " -> (Vertex: " << neighbor.first << ", Weight: " << neighbor.second << ")\n";
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::tuple<int, int, int>> getEdges() const
    {
        std::vector<std::tuple<int, int, int>> xs;
        for (auto v : vertexes)
          for (const auto& neighbor : adjList[v])
            xs.push_back({v, neighbor.first, neighbor.second});
        return xs;
    }

    std::vector<std::pair<int, int>> getAdjacentVertices(int v) const { return adjList[v - 1]; }

    int getVertices() const { return vertexes.size(); }
    std::set<int> getNodes() const { return vertexes; }
};

using Edge = std::tuple<int, int, int>;

class WeightedEdgedGraph
{
private:
    // Adjacency list: each vertex has a list of pairs (neighbor, weight)
    std::vector<Edge> adjList;
    std::set<int> vertexes;
public:
    WeightedEdgedGraph(int vertices) { adjList.resize(vertices); }
    WeightedEdgedGraph* addEdge(int source, int dest, int weight) 
    {
        adjList.push_back({source, dest, weight});
        vertexes.insert(source);
        vertexes.insert(dest);
        return this;
    }

    void display() const 
    {
        for (auto x : adjList) 
        {
            int s, d, w;
            std::tie(s, d, w) = x;
            std::cout << "from: " << s << ", to: " << d << ", weight: " << w << "\n";
        }
    }

    std::set<int> getVertexes() const { return vertexes; }
    std::vector<Edge> getEdges() const { return adjList; }
};



/*
Depth-first search (DFS) is a straightforward graph traversal technique. 
The algorithm begins at a starting node and proceeds to all other nodes that are reachable from the starting node using the edges of the graph.
Depth-first search always follows a single path in the graph as long as it finds new nodes. 
After this, it returns to previous nodes and begins to explore other parts of the graph. 
The algorithm keeps track of visited nodes, so that it processes each node only once.

The time complexity of depth-first search is O(n + m) 
where n is the number of nodes and m is the number of edges, 
because the algorithm processes each node and edge once.
*/
void dfsHelper(Graph graph, int node, void (*process)(int), std::vector<bool>& xs)
{
    if(xs[node])
      return;
    xs[node] = true;  
    process(node);
    for (auto n : graph.getAdjacentNodes(node))
      dfsHelper(graph, n, process, xs);
}

void dfs(Graph graph, int start, void (*process)(int))
{
    std::vector<bool> visited = std::vector<bool>(graph.getVertices(), false);
    dfsHelper(graph, start, process, visited);
}

/*
Breadth-first search (BFS) visits the nodes of a graph in increasing order of their distance from the starting node. 
Thus, we can calculate the distance from the starting node to all other nodes using breadth-first search. 
However, breadth-first search is more difficult to implement than depth-first search.
Breadth-first search goes through the nodes one level after another. 
First the search explores the nodes whose distance from the starting node is 1, 
then the nodes whose distance is 2, and so on. This process continues until all nodes have been visited
*/
void bfs(Graph graph, int start, void (*process)(int, size_t))
{
      /*
         Breadth-first search is more difficult to implement than depth-first search, 
         because the algorithm visits nodes in different parts of the graph. 
         A typical implementation is based on a queue that contains nodes. 
         At each step, the next node in the queue will be processed.
      */
    std::vector<bool> visited = std::vector<bool>(graph.getVertices(), false);
    std::vector<size_t> distance = std::vector<size_t>(graph.getVertices(), -1);
    std::queue<int> queue;
    queue.push({start});
    distance[start]= 0;
    while(!queue.empty())
    {
        auto el = queue.front();
        queue.pop();
        process(el, distance[el]);
        for (auto n : graph.getAdjacentNodes(el))
        {
           if (visited[n])
             continue;
           visited[n] = true;
           distance[n] = distance[el] + 1; 
           queue.push(n);
        }
    };
}

/*
the algorithm keeps track of distances from the starting node to all nodes of the graph. 
Initially, the distance to the starting node is 0 and the distance to any other node is infinite. 
The algorithm then reduces the distances by finding edges that shorten the paths until it is not possible to reduce any distance.

For each node vv in the graph, define the subproblem as finding the shortest path from the source node s to node v using at most k edges, 
where k ranges from 0 to n - 1 (the number of nodes in the graph minus one).
*/
std::tuple<std::vector<int>, bool> bellman_ford(WeightedEdgedGraph graph, int start) 
{
      // Initialize distances to all vertices as infinity, and to the start vertex as 0
    std::vector<int> distance(graph.getVertexes().size(), INT32_MAX);
    distance[start - 1] = 0;

    // Relaxation step: Repeat V-1 times
    for (int i = 1; i <= graph.getVertexes().size() - 1; ++i) {
        for (const auto& edge : graph.getEdges()) {
            int u, v, w;
            std::tie(u, v, w) = edge;
            distance[v - 1] = std::min(distance[v - 1], distance[u - 1] + w);
        }
    }

    bool negative_cycle = false;

   // Check for negative weight cycles
   /*
     A negative cycle can be detected using the Bellman–Ford algorithm by running the algorithm for n rounds. 
     If the last round reduces any distance, the graph contains a negative cycle
   */
    for (const auto& edge : graph.getEdges()) {
        int u, v, w;
        std::tie(u, v, w) = edge;
        if (distance[u - 1] != INT32_MAX && 
            distance[u - 1] + w < distance[v - 1]) {
            negative_cycle = true;
            break;
        }
    }

    return {distance, negative_cycle};
}

/*
An efficient implementation of Dijkstra’s algorithm requires that we can efficiently find the minimum-distance node that has not been processed. 
An appropriate data structure for this is a priority queue that contains the remaining nodes ordered by their distances. 
Using a priority queue, the next node to be processed can be retrieved in logarithmic time
*/
std::vector<int> dijkstra(WeightedGraph graph, int start)
{
    // Initialize distances to all vertices as infinity, and to the start vertex as 0
    std::vector<int> distance = std::vector<int>(graph.getVertices(), INT32_MAX);
    std::vector<bool> processed = std::vector<bool>(graph.getVertices(), false);
    distance[start] = 0;
    std::priority_queue<std::pair<int, int>> queue;

    queue.push({0, start});

    while(!queue.empty())
    {
        int source = queue.top().second;
        queue.pop();
        if(processed[source])
          continue;
        processed[source] = true;
        for(auto v : graph.getAdjacentVertices(source))
        {
            int dest, w;
            std::tie(dest, w) = v;
            if (distance[source] + w < distance[dest])
            {
                distance[dest] = distance[source] + w;
                queue.push({-distance[dest], dest});
            }
        }
    }

    return distance;
}

using Distance = std::vector<std::vector<int>>;

/*
The Floyd–Warshall algorithm provides an alternative way to approach the problem of finding shortest paths. 
Unlike the other algorithms in this chapter, it finds shortest paths between all node pairs of the graph in a single run.
The algorithm maintains a matrix that contains distances between the nodes. 
The initial matrix is directly constructed based on the adjacency matrix of the graph. 
Then, the algorithm consists of consecutive rounds, and on each round, 
it selects a new node that can act as an intermediate node in paths from now on, and reduces distances using this node
*/
 Distance floyd_warshall(WeightedGraph graph)
 {
      Distance distance(graph.getVertices(), std::vector<int>(graph.getVertices(), 0));
      for(int i = 1; i < graph.getVertices(); i++)
      { 
          auto xs = graph.getAdjacentVertices(i - 1);
          for(int j = 1; j < graph.getVertices(); j++)
          {
              auto iter = 
                std::find_if(
                  xs.begin(), 
                  xs.end(), 
                  [&j](std::pair<int, int> p) 
                  { return j == p.first; }
                );
              if(i == j)
                continue;
              else if(iter != xs.end()) 
              {distance[i - 1][j] = iter->second; }
              else distance[i - 1][j] = INT32_MAX;  
        }
      }
      return distance;
 }


/*
Topological sorting is a fundamental concept in computer science, particularly in the context of directed acyclic graphs (DAGs). 
It provides a linear ordering of vertices such that for any directed edge (𝑢,𝑣) (u,v), vertex 𝑢 comes before 𝑣 in the ordering. 
This is useful in scenarios like scheduling tasks, resolving symbol dependencies in linkers, and more

Depth-First Search (DFS) Based Algorithm:

Uses recursive depth-first traversal.
Nodes are added to the ordering in reverse post-order (when all descendants of a node are visited).
*/

enum NodeState { NotProcessed, BeingProcessed, Processed };

void topologicalSortBfs(WeightedGraph* graph, int node, std::vector<std::tuple<int, NodeState>>& xs, std::deque<int>& queue)
{
    bool is_processed = 
      std::any_of(
        xs.begin(),
        xs.end(), 
        [&node](std::tuple<int, NodeState> t) 
        {
            int x;
            NodeState s;
            std::tie(x, s) = t;
            return x == node && s == Processed;
         } );
    if(is_processed)
      return;
    std::for_each(
      xs.begin(), 
      xs.end(), 
      [&node](std::tuple<int, NodeState> t)
      {
           int x;
           NodeState s;
           std::tie(x, s) = t;
           if(x == node)
             return make_tuple(x, Processed);
           else
             return t;
      });
    queue.push_back(node);
    std::cout << node << std::endl;
    for(auto n : graph->getAdjacentVertices(node))
    {
        xs.push_back({n.first, BeingProcessed});
        topologicalSortBfs(graph, n.first, xs, queue);
    }
}

void dfs(int node, vector<vector<int>>& adjList, vector<bool>& visited, stack<int>& topoStack) 
{
    visited[node] = true;
    // Explore all adjacent nodes
    for (int neighbor : adjList[node])
      if (!visited[neighbor])
        dfs(neighbor, adjList, visited, topoStack);
    // Push the node onto the stack after all its neighbors are processed
    topoStack.push(node);
}

std::vector<int> topologicalSortBfs(int vertices, std::vector<std::vector<int>> graph)
{    
    std::vector<vector<int>> adjList(vertices);
    
    // Build the adjacency list
    for (const auto& edge : graph) 
    {
        int u = edge[0];
        int v = edge[1];
        adjList[u].push_back(v);
    }
    
    vector<bool> visited(vertices, false);
    stack<int> topoStack;
    
    // Perform DFS from each unvisited node
    for (int i = 0; i < vertices; i++)
      if (!visited[i])
        dfs(i, adjList, visited, topoStack);
    
    // Pop all elements from the stack to get the topological order
    vector<int> topoOrder;
    while (!topoStack.empty()) 
    {
        topoOrder.push_back(topoStack.top());
        topoStack.pop();
    }
    return topoOrder;
}
#include <vector>
#include <queue>

namespace algorithms::graph::leetcode::can_finish
{

using graph = std::vector<std::vector<int>>;

    // https://leetcode.com/problems/course-schedule
    /**
     * There are a total of numCourses courses you have to take, 
     * labeled from 0 to numCourses - 1. You are given an array prerequisites 
     * where prerequisites[i] = [ai, bi] 
     * indicates that you must take course bi first if you want to take course ai.
     * For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
     * Return true if you can finish all courses. Otherwise, return false.
     * tag: topological sort
     * The idea is to go through the nodes of the graph and 
     * always begin a depth-first search at the current node if it has not been processed yet. 
     * During the searches, the nodes have three possible states:
     * 0 : the node has not been processed (white) 
     * 1 : the node is under processing (light gray) 
     * 2 : the node has been processed (dark gray)
     * Initially, the state of each node is 0. 
     * When a search reaches a node for the first time, its state becomes 1. 
     * Finally, after all edges from the node have been processed, its state becomes 2.
     * If the graph contains a cycle, we will discover this during the search, 
     * because sooner or later we will arrive at a node whose state is 1. 
     * In this case, it is not possible to construct a topological sort. 
     * If the graph does not contain a cycle, we can construct a topological sort 
     * by adding each node to a list when its state becomes 2. 
     * Finally, we reverse the list and get a topological sort for the graph.
     */
    std::vector<int> topologicalKahn(int v, const graph& g)
    {
        int l = g.size();
        std::vector<int> in_degree(v);
        for(int i = 0; i < v; i++)
          for(auto u : g[i])
            ++in_degree[u];

        std::queue<int> q;
        for(int i = 0; i < v; i++)
          if(in_degree[i] == 0)
            q.push(i);

        std::vector<int> topological;
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            topological.push_back(u);
            for(auto v : g[u])
              if(--in_degree[v] == 0)
                q.push(v);
        }
        return topological;
    }
    bool canFinish(int numCourses, const graph& prerequisites) 
    {
        int l = prerequisites.size();
        graph adjList(numCourses);
        // convert into adjacent list O(l)
        for(auto p : prerequisites)
          adjList[p[1]].push_back(p[0]);
        auto s = topologicalKahn(numCourses, adjList);
        return s.size() == numCourses;
    }
}
#include <string>
#include <vector>
#include <map>
#include <queue>


namespace algorithms::graph::leetcode::doublets
{

using dist = std::unordered_map<std::string, int>;
using graph = std::map<std::string, std::vector<std::string>>;
using words = std::vector<std::string>;


    /**
     * https://leetcode.com/problems/word-ladder
     * https://onlinejudge.org/external/101/10150.pdf
     * A Doublet is a pair of words that differ in exactly one letter; 
     * for example, “booster” and “rooster” or “rooster” and “roaster” or “roaster” and “roasted”
     * A transformation sequence from word beginWord to word endWord using a dictionary wordList 
     * is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
     * Every adjacent pair of words differs by a single letter.
     * Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
     * sk == endWord
     * Given two words, beginWord and endWord, and a dictionary wordList, 
     * return the number of words in the shortest transformation sequence from beginWord to endWord, 
     * or 0 if no such sequence exists. 
     * Hint: BFS state is string */
    const int start = 97;
    const int end = 122;
    bool finished = false;
    void bfs(graph& g, const std::string& sink, std::queue<std::string>& q, dist& distance)
    {
        while(!q.empty() && !finished)
        {
            std::string s = q.front();
            q.pop();
            if(s == sink)
            {
                finished = true;
                break;
            }
            for(auto w : g[s])
            {
                if(distance.find(w) != distance.end())
                  continue;
                distance[w] = distance[s] + 1;
                q.push(w);
            }
        }
    }
    int ladderLength(std::string beginWord, std::string endWord, const words& wordList) 
    {
        graph g;
        for(auto word : wordList)
        {
            std::vector<std::string> vs;
            for(int i = 0; i < word.size(); i++)
              for(int j = start; j <= end; j++)
                if((char)j != word[i])
                {
                    std::string s = word;
                    vs.push_back(s.replace(i, 1, std::string(1, (char)j)));
                }
            g.insert({word, vs});
        }

        dist distance;
        std::queue<std::string> q;

        distance[endWord] = 1;
        q.push(endWord);
        bfs(g, beginWord, q, distance);
        return finished ? distance[beginWord] : 0;
    }   
    
}
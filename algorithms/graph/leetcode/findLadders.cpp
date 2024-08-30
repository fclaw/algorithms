#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <map>

namespace algorithms::graph::leetcode::find_ladders
{


using graph = std::map<std::string, std::vector<std::string>>;
using words = std::unordered_set<std::string>;
using ladders = std::vector<std::vector<std::string>>;
using vi = std::unordered_map<std::string, int>;

    /**
     * https://leetcode.com/problems/word-ladder-ii
     * A transformation sequence from word beginWord to word endWord using a dictionary wordList 
     * is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
     * Every adjacent pair of words differs by a single letter.
     * Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList. sk == endWord
     * Given two words, beginWord and endWord, and a dictionary wordList, 
     * return all the shortest transformation sequences from beginWord to endWord, 
     * or an empty list if no such sequence exists. Each sequence should be returned as a list of the words 
     * [beginWord, s1, s2, ..., sk] */
    const int start = 97;
    const int end = 122;
    bool finished = false;
    std::string tmp;
    graph g;
    std::string T;
    vi visited;
    void bfs(words& ws, const std::string& sink, std::queue<std::pair<std::string, int>>& q)
    {
        while(!q.empty() && 
              !finished)
        {
            auto v = q.front();
            q.pop();
            std::string word = v.first;
            int dist = v.second;
            if(word == sink)
              finished = true;
           auto it = ws.find(word);  
           if(it != ws.end() && !finished)
            {
                for(int i = 0; i < word.size(); i++)
                  for(int j = start; j <= end; j++)
                    if((char)j != word[i])
                    {
                      tmp = word;
                      tmp[i] = (char)j;
                      q.push({tmp, dist + 1});
                      g[word].push_back(tmp);
                    }
            }
            ws.erase(word);
        }
    }
    void restore_ladders(ladders& ans, const std::string& s, std::vector<std::string>& acc)
    {
    }
    ladders findLadders(std::string beginWord, std::string endWord, const std::vector<std::string>& wordList)
    {
        std::queue<std::pair<std::string, int>> q;
        words ws(wordList.begin(), wordList.end());
        q.push({endWord, 1});
        bfs(ws, beginWord, q);
        ladders ans;
        T = beginWord;
        std::vector<std::string> acc;
        restore_ladders(ans, endWord, acc);
        return ans;
    }
}
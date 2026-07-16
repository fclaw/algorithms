/*
───────────────────────────────────────────────────────────────
🧳 Page Layout, https://open.kattis.com/contests/yks7mq/problems/pagelayout, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../../onlinejudge/debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


#define LSOne(S) (S) & (-S)

struct Story
{
    int idx;
    int x;
    int y;
    int w;
    int h;
};

using v_stories = std::vector<Story>;
using vi = std::vector<int>;

bool is_overlap(const Story& s1, const Story& s2) {
  // Check horizontal overlap
  int x_overlap = std::max(0, std::min(s1.x + s1.w, s2.x + s2.w) - std::max(s1.x, s2.x));
  // Check vertical overlap
  int y_overlap = std::max(0, std::min(s1.y + s1.h, s2.y + s2.h) - std::max(s1.y, s2.y));
    
  // They only overlap if both overlaps are strictly greater than 0
  return (x_overlap > 0 && y_overlap > 0);
}

void backtrack(const v_stories& stories, int i, int curr_stories, const vi& overlap_table, vi& solutions) {

    int S = (int)stories.size();
    if(i == S) {
      solutions.push_back(curr_stories);
      return;
    }
  
    // take
    int bit = 1 << i;
    int overlap_stories = overlap_table[i];
    bool is_overlapped = (overlap_stories & curr_stories) > 0;
    if(!is_overlapped) {
      backtrack(stories, i + 1, curr_stories | bit, overlap_table, solutions);
    }
    // skip 
    backtrack(stories, i + 1, curr_stories, overlap_table, solutions);

}

int calculate_area(const Story& story) {
  return story.w * story.h;
}

int calculate_total_area(const v_stories& stories, int sol) {

   int area = 0;
   while(sol) {
     int bit = LSOne(sol);
     int idx = __builtin_ctz(bit);
     auto story = stories[idx];
     area += calculate_area(story);
     sol -= bit;
   }

   return area;
}


namespace algorithms::kattis::complete_search::page_layout
{
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value()) {
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        }

        int n;
        while(std::cin >> n && n) {
          v_stories stories(n);
          for(int i = 0; i < n; ++i) {
            Story story;
            story.idx = i;
            std::cin >> story.w >> story.h >> story.x >> story.y;
            stories[i] = story;
          }
             
          vi overlap_table(n, 0);
          for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
              if(is_overlap(stories[i], stories[j])) {
                overlap_table[i] |= (1 << j);
                overlap_table[j] |= (1 << i);
              }
            }
          }

          vi solutions;
          backtrack(stories, 0, 0, overlap_table, solutions);

          int max_area = 0;
          for(int sol : solutions) {
            int area = calculate_total_area(stories, sol);
            max_area = std::max(max_area, area);
          }
          std::cout << max_area << std::endl;
        }
    }
}
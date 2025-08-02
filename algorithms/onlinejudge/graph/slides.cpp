
 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 663 Sorting Slides, try disallowing an edge to see if MCBM changes;
    which implies that the edge has to be used  rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include "tools/mcbm.cpp"
#include <bits/stdc++.h>


namespace mcmb = algorithms::onlinejudge::graph::tools::mcmb;

const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

using ii = std::pair<int, int>;
using v_ii = std::vector<ii>;
using Point = std::pair<int, int>;
using Graph = mcmb::container<std::set<int>>;

struct Slide
{
    Point bl, tr; // bottom-left, top-right
    int id;      // Original index
};

struct Number
{
    Point p; // Position of the number
    int id;  // Original index
};


bool in_slide(const Number& num, const Slide& slide) {

    // Get the canonical min/max coordinates of the slide
    int x_slide_min = slide.bl.first;
    int x_slide_max = slide.tr.first;
    int y_slide_min = slide.bl.second;
    int y_slide_max = slide.tr.second;

    int x_num = num.p.first;
    int y_num = num.p.second;

    // Check if the point's coordinates are within the rectangle's bounds
    bool within_x = (x_num >= x_slide_min && x_num <= x_slide_max);
    bool within_y = (y_num >= y_slide_min && y_num <= y_slide_max);

    return within_x && within_y;
}

int test_edges(int slide, const Graph& graph, int L_SIZE, int R_SIZE) {

  for(int num : graph[slide]) {
    Graph tmp = graph;
    tmp[slide].erase(num);

    mcmb::kuhn kuhn_s(R_SIZE);
    for(int slide = 0; slide < L_SIZE; ++slide) {
      kuhn_s.visited.assign(L_SIZE, false);
      mcmb::try_kuhn(slide, tmp, kuhn_s);
    }

    bool is_critical_edge = false;
    for(int slide = 0; slide < L_SIZE; ++slide) {
      if(!(~kuhn_s.match[slide])) {
        is_critical_edge = true;
        break;
      }
    }

    if(is_critical_edge) return num;
  }
  return mcmb::sentinel;
}


namespace algorithms::onlinejudge::graph::slides
{
    /** https://onlinejudge.org/external/6/663.pdf */
    int heap_size, t_case = 1;
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        
        while(while_read(heap_size) && heap_size) {
          std::vector<Slide> slides(heap_size);
          for(int slide_id = 0; slide_id < heap_size; ++slide_id) {
            Slide slide;
            while_read(slide.bl.first, slide.tr.first);
            while_read(slide.bl.second, slide.tr.second);
            slide.id = slide_id;
            slides[slide_id] = slide;
          }

          std::vector<Number> numbers(heap_size);
          for(int num_id = 0; num_id < heap_size; ++num_id) {
            Number num;
            num.id = num_id;
            while_read(num.p);
            numbers[num_id] = num;
          }

          int L_SIZE = heap_size;
          int R_SIZE = heap_size;

          Graph graph(R_SIZE);
          for(const auto& slide : slides) {
            for(const auto& num : numbers) {
              if(in_slide(num, slide)) {
                graph[slide.id].insert(num.id);
              }
            }
          }

          v_ii slides_with_numbers;
          for(int slide_id = 0; slide_id < L_SIZE; ++slide_id) {
            int num = test_edges(slide_id, graph, L_SIZE, R_SIZE);
            if(num != mcmb::sentinel) 
              slides_with_numbers.emplace_back(slide_id, num + 1);
          }

          std::string slides_str;
          if(slides_with_numbers.empty()) 
            slides_str = "none";
          else {
            for(const auto& slide : slides_with_numbers) {
              auto letter = std::string(1, std::toupper(alphabet[slide.first]));
              auto number = std::to_string(slide.second);
              slides_str += "(" + letter + "," + number + ") ";
            }
            slides_str.pop_back(); // remove last space
          }
          printf("Heap %d\n%s\n", t_case++, slides_str.c_str());
          if(t_case) std::cout << std::endl;
        }
    }
}
/*
───────────────────────────────────────────────────────────────
🧳 UVa 10171 Meeting Prof. Miguel ..., rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



constexpr int inf = 1e5;
constexpr int MAX_CITIES = 26;
constexpr char BI = 'B';
constexpr char YA = 'Y';


using vi = std::vector<int>;
using vvi = std::vector<vi>;


void calculate_energy(
  int city_id, 
  int student, 
  int professor, 
  int& min_energy, 
  const vvi& student_matrix, 
  const vvi& professor_matrix, 
  std::set<int>& points) {
  
  int s_e = student_matrix[student][city_id];
  int p_e = professor_matrix[professor][city_id];
  if(s_e == inf || p_e == inf) return;
  int energy = s_e + p_e;
  if(energy < min_energy) {
    min_energy = energy;
    points.clear();
    points.insert(city_id);
  } else if(energy == min_energy) {
    points.insert(city_id);
  }
}


namespace algorithms::onlinejudge::graph::professor_Miguel
{
    /** https://onlinejudge.org/external/101/10171.pdf */
    int roads_n;
    int char_to_int(char c) { return c - 'A'; }
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
       
        while(while_read(roads_n) && roads_n) {
          vvi student_matrix(MAX_CITIES, vi(MAX_CITIES, inf));
          vvi professor_matrix(MAX_CITIES, vi(MAX_CITIES, inf));
          for(int city_id = 0; city_id < MAX_CITIES; ++city_id) {
            student_matrix[city_id][city_id] = 0;
            professor_matrix[city_id][city_id] = 0;
          }

          for(int road_id = 0; road_id < roads_n; ++road_id) {
            char age, type, from_s, to_s;
            int energy;
            while_read(age, type, from_s, to_s, energy);
            int from = char_to_int(from_s);
            int to = char_to_int(to_s);
            if(age == YA) {
              student_matrix[from][to] = std::min(student_matrix[from][to], energy);
              if(type == BI) student_matrix[to][from] = std::min(student_matrix[to][from], energy);
            }
            else {
              professor_matrix[from][to] = std::min(professor_matrix[from][to], energy);
              if(type == BI) professor_matrix[to][from] = std::min(professor_matrix[to][from], energy);
            }
          }

          for(int k = 0; k < MAX_CITIES; ++k) {
            for(int i = 0; i < MAX_CITIES; ++i) {
              for(int j = 0; j < MAX_CITIES; ++j) {
                int& e_ij = student_matrix[i][j];
                int e_ik = student_matrix[i][k];
                int e_kj = student_matrix[k][j];
                if(e_ik == inf || e_kj == inf) continue;
                e_ij = std::min(e_ij, e_ik + e_kj);
              }
            }
          }

          for(int k = 0; k < MAX_CITIES; ++k) {
            for(int i = 0; i < MAX_CITIES; ++i) {
              for(int j = 0; j < MAX_CITIES; ++j) {
                int& e_ij = professor_matrix[i][j];
                int e_ik = professor_matrix[i][k];
                int e_kj = professor_matrix[k][j];
                if(e_ik == inf || e_kj == inf) continue;
                e_ij = std::min(e_ij, e_ik + e_kj);
              }
            }
          }

          char student_loc_s, professor_loc_s;
          while_read(student_loc_s, professor_loc_s);
          int student = char_to_int(student_loc_s);
          int professor = char_to_int(professor_loc_s);

          int min_energy = inf;
          std::set<int> points;
          for(int city_id = 0; city_id < MAX_CITIES; ++city_id) {
            calculate_energy(city_id, student, professor, min_energy, student_matrix, professor_matrix, points);
          }

          if(min_energy == inf) 
            printf("You will never meet.\n");
          else {
            std::string ans;
            for(int p : points)
              ans += std::string(1, char(p + 'A')) + " ";
            ans.pop_back();
            printf("%d %s\n", min_energy, ans.c_str());
          }
        }
    }
}
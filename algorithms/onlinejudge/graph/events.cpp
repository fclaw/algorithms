/*
───────────────────────────────────────────────────────────────
🧳 UVa 334 Identifying Concurrent Events, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


constexpr int inf = 1e5;

using map_si = std::unordered_map<std::string, int>;
using map_is = std::unordered_map<int, std::string>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using ii = std::pair<int, int>;
using vii = std::vector<ii>;



namespace algorithms::onlinejudge::graph::events
{
    /** https://onlinejudge.org/external/3/334.pdf */
    int seq, par, t_cases = 1;
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
        
        while(while_read(seq) && seq) {
          int event_idx = 0;
          map_si event_to_index;
          map_is index_to_event;
          vvi seq_events;
          vii par_events;
          for(int i = 0; i < seq; ++i) {
            int n;
            vi events;
            while_read(n);
            for (int j = 0; j < n; ++j) {
              std::string event;
              while_read(event);
              auto it = event_to_index.find(event);
              if(it == event_to_index.end()) {
                event_to_index[event] = event_idx++;
                index_to_event[event_idx - 1] = event;
              }
              events.push_back(event_to_index[event]);
            }
            seq_events.push_back(events);
          }
          while_read(par);
          for(int i = 0; i < par; ++i) {
            std::string from_event;
            std::string to_event;
            while_read(from_event, to_event);
            int from = event_to_index.at(from_event);
            int to = event_to_index.at(to_event);
            par_events.push_back({from, to});
          }

          int events_n = event_idx;
          vvi precedes_graph(events_n, vi(events_n, 0));

          for(int i = 0; i < (int)seq_events.size(); ++i)
            for(int j = 1; j < (int)seq_events[i].size(); ++j) {
              int ev1 = seq_events[i][j - 1];
              int ev2 = seq_events[i][j];
              precedes_graph[ev1][ev2] = 1;
            }
           
          for(int i = 0; i < (int)par_events.size(); ++i) {
            int ev1 = par_events[i].first;
            int ev2 = par_events[i].second;
            precedes_graph[ev1][ev2] = 1;
          }

          for(int k = 0; k < events_n; ++k)
            for(int i = 0; i < events_n; ++i)
              for(int j = 0; j < events_n; ++j)
                precedes_graph[i][j] |= (precedes_graph[i][k] & precedes_graph[k][j]);


          int concurrent_pairs_count = 0;
          vii concurrent_pairs;

          // Iterate through all unique pairs of events
          for(int i = 0; i < events_n; ++i) {
            for(int j = i + 1; j < events_n; ++j) {
              // Check the concurrency condition
              if(!precedes_graph[i][j] && 
                 !precedes_graph[j][i]) {
                concurrent_pairs_count++;
                if(concurrent_pairs.size() < 2) { // Store up to two examples
                  concurrent_pairs.push_back({i, j});
                }
              }
            }
          }

          if(!concurrent_pairs_count) {
            printf("Case %d, no concurrent events.\n", t_cases++);
          } else {
            printf("Case %d, %d concurrent events:\n", t_cases++, concurrent_pairs_count);
            for(int i = 0; i < (int)concurrent_pairs.size(); ++i) {
              int ev1 = concurrent_pairs[i].first;
              int ev2 = concurrent_pairs[i].second;
              printf("(%s,%s) ", index_to_event[ev1].c_str(), index_to_event[ev2].c_str());
            }
            printf("\n");
          }
        }
    }
}
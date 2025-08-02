
 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 753 A Plug for UNIX, initially a non standard matching problem
    but this problem can be reduced to a simple MCBM problem, rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include "tools/mcbm.cpp"
#include <bits/stdc++.h>


namespace mcmb = algorithms::onlinejudge::graph::tools::mcmb;


struct Outlet
{
    int id;
    int type_id;
};

struct Device
{
    int id;
    int type_id;
};

struct Adapter
{
    int id;
    int from_type_id;
    int to_type_id;
};


using vi = std::vector<int>;
using vvi = std::vector<vi>;
using v_adapter = std::vector<Adapter>;
using v_outlet = std::vector<Outlet>;
using v_device = std::vector<Device>;


namespace algorithms::onlinejudge::graph::plug_for_UNIX
{
    /** https://onlinejudge.org/external/7/753.pdf */
    int t_cases, outlets_n, devices_n, adapters_n;
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
        
        while_read(t_cases);
        while(t_cases--) {

          int outlet_id = 0;
          std::unordered_map<std::string, int> outlet_type_id;

          std::string type;
          while_read(outlets_n);
          std::vector<Outlet> outlets(outlets_n);
          for(int o = 0; o < outlets_n; ++o) {
            Outlet outlet;
            outlet.id = o;
            while_read(type);
            if(!outlet_type_id.count(type)) {
              outlet.type_id = outlet_id++;
              outlet_type_id[type] = outlet.type_id;
            } else { outlet.type_id = outlet_type_id[type]; }
            outlets[o] = outlet;
          }
          while_read(devices_n);
          std::vector<Device> devices(devices_n);
          for(int d = 0; d < devices_n; ++d) {
            Device device;
            device.id = d;
            std::string name;
            while_read(name);
            while_read(type);
            if(!outlet_type_id.count(type)) {
              outlet_type_id[type] = outlet_id++;
              device.type_id = outlet_type_id[type];
            } else { device.type_id = outlet_type_id[type]; }
            devices[d] = device;
          }

          while_read(adapters_n);
          std::vector<Adapter> adapters(adapters_n);
          for(int a = 0; a < adapters_n; ++a) {
            Adapter adapter;
            adapter.id = a;
            std::string from, to;
            while_read(from);
            while_read(to);
            if(!outlet_type_id.count(from)) {
              outlet_type_id[from] = outlet_id++;
              adapter.from_type_id = outlet_type_id[from];
            } else { adapter.from_type_id = outlet_type_id[from]; }
            if(!outlet_type_id.count(to)) {
              outlet_type_id[to] = outlet_id++;
              adapter.to_type_id = outlet_type_id[to];
            } else { adapter.to_type_id = outlet_type_id[to]; }
            adapters[a] = adapter;
          }

          // make connectivity map between adapters (100 adapters)
          vvi adapters_map(outlet_id, vi(outlet_id, false));
          for(int o = 0; o < outlet_id; ++o) {
            adapters_map[o][o] = true;
          }
          
          // *** ADD THIS MISSING STEP ***
          // Populate with direct adapter connections
          for (const auto& adapter : adapters) {
            adapters_map[adapter.from_type_id][adapter.to_type_id] = true;
          }


          // Floyd-Warshall
          for(int i = 0; i < adapters_n; ++i) {
            for(int j = 0; j < adapters_n; ++j) {
              for(int k = 0; k < adapters_n; ++k) {
                int from_id = adapters[i].from_type_id;
                int to_id = adapters[j].to_type_id;
                int k_from_id = adapters[k].from_type_id;
                int k_to_id = adapters[k].to_type_id;
                adapters_map[from_id][to_id] = 
                  adapters_map[from_id][to_id] || 
                  (adapters_map[from_id][k_from_id] &&
                   adapters_map[k_to_id][to_id]);
              }
            }
          }

          int L_SIZE = devices_n;
          int R_SIZE = outlets_n;
          
          mcmb::vvi graph(L_SIZE);
          for(int dev_id = 0; dev_id < L_SIZE; ++dev_id) {
            for(int outlet_id = 0; outlet_id < R_SIZE; ++outlet_id) {
              int dev_type_id = devices[dev_id].type_id;
              int outlet_type_id = outlets[outlet_id].type_id;
              if(adapters_map[dev_type_id][outlet_type_id]) {
                 graph[dev_id].push_back(outlet_id);
              }
            }
          }

          int coupled_device = 0;
          mcmb::kuhn kuhn_s(R_SIZE);
          for(int dev_id = 0; dev_id < L_SIZE; ++dev_id) {
            kuhn_s.visited.assign(L_SIZE, false);
            bool is_coupled = mcmb::try_kuhn(dev_id, graph, kuhn_s);
            if(is_coupled) coupled_device++;
          }

          std::cout << (devices_n - coupled_device) << std::endl;
          if(t_cases) std::cout << std::endl;
        }
    }
}
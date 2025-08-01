
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
    std::string type;
};

struct Device
{
    int id;
    std::string name;
    std::string plug;
};

struct Adapter
{
    int id;
    std::string from;
    std::string to;
};


using vb = std::vector<bool>;
using vvb = std::vector<vb>;
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
          while_read(outlets_n);
          std::vector<Outlet> outlets(outlets_n);
          for(int o = 0; o < outlets_n; ++o) {
            Outlet outlet;
            outlet.id = o;
            while_read(outlet.type);
            outlets[o] = outlet;
          }
          while_read(devices_n);
          std::vector<Device> devices(devices_n);
          std::unordered_map<int, std::string> id_device_title;
          for(int d = 0; d < devices_n; ++d) {
            Device device;
            device.id = d;
            while_read(device.name);
            while_read(device.plug);
            devices[d] = device;
            id_device_title[d] = device.name; 
          }

          while_read(adapters_n);
          std::vector<Adapter> adapters(adapters_n);
          for(int a = 0; a < adapters_n; ++a) {
            Adapter adapter;
            adapter.id = a;
            while_read(adapter.from);
            while_read(adapter.to);
            adapters[a] = adapter;
          }

          // make connectivity map between adapters (100 adapters)
          std::unordered_map<std::string, std::unordered_map<std::string, bool>> adapters_map;
          for(const auto& adapter : adapters) {
            adapters_map[adapter.from][adapter.to] = true;
            adapters_map[adapter.from][adapter.from] = true;
            adapters_map[adapter.to][adapter.to] = true;
          }
          
          // Floyd-Warshall
          for(int i = 0; i < adapters_n; ++i) {
            for(int j = 0; j < adapters_n; ++j) {
              for(int k = 0; k < adapters_n; ++k) {
                auto from  = adapters[i].from;
                auto to = adapters[j].to;
                auto k_from = adapters[k].from;
                auto k_to = adapters[k].to;
                adapters_map[from][to] = 
                  adapters_map[from][to] || 
                  (adapters_map[from][k_from] &&
                   adapters_map[k_to][to]);
              }
            }
          }
           
          int R_SIZE = devices_n;
          int L_SIZE = outlets_n;
          
          mcmb::vvi graph(R_SIZE);
          for(int dev_id = 0; dev_id < R_SIZE; ++dev_id) {
            for(int outlet_id = 0; outlet_id < L_SIZE; ++outlet_id) {
              auto dev_type = devices[dev_id].plug;
              auto outlet_type = outlets[outlet_id].type;
              bool can_reach = false;
              if(auto dev_it = adapters_map.find(dev_type); 
                 dev_it != adapters_map.end()) {
                if(auto out_it = dev_it->second.find(outlet_type); 
                   out_it != dev_it->second.end()) {
                  can_reach = out_it->second;
                }
              }
              // either through the chain of adapters or direct compatibility
              if(can_reach || dev_type == outlet_type) {
                graph[dev_id].push_back(outlet_id);
              }
            }
          }

          int coupled_device = 0;
          mcmb::kuhn kuhn_s(L_SIZE);
          for(int dev_id = 0; dev_id < R_SIZE; ++dev_id) {
            kuhn_s.visited.assign(R_SIZE, false);
            bool is_coupled = mcmb::try_kuhn(dev_id, graph, kuhn_s);
            if(is_coupled) coupled_device++;
          }

          std::cout << (devices_n - coupled_device) << std::endl;
          if(t_cases) std::cout << std::endl;
        }
    }
}
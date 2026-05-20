/*
───────────────────────────────────────────────────────────────
🧳 UVa 330 Inventory Maintenance, https://onlinejudge.org/external/3/330.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



std::string trim(const std::string& str) {
  const std::string whitespace = " \t\n\r\f\v";
  const auto strBegin = str.find_first_not_of(whitespace);
    
  if (strBegin == std::string::npos)
    return ""; // Entire string is whitespace

  const auto strEnd = str.find_last_not_of(whitespace);
  const auto strRange = strEnd - strBegin + 1;

  return str.substr(strBegin, strRange);
}

struct Item
{
    double buyAt;
    double sellAt;
    int quantity;
};

using mapsi = std::map<std::string, Item>; 
using vs = std::vector<std::string>;

void printReport(const mapsi& inventory, double profit) {

  // The headers and dashes have very specific gaps between them:
  printf("                  INVENTORY REPORT\n");
  printf("Item Name     Buy At      Sell At      On Hand        Value\n");
  printf("---------     ------      -------      -------        -----\n");

  double total_value = 0.0;
  for(auto[name, item] : inventory) {
    total_value += item.buyAt * item.quantity;
    printf("%-14s%6.2f%13.2f%13d%13.2f\n", name.c_str(), item.buyAt, item.sellAt, item.quantity, item.buyAt * item.quantity);
  }

  printf("------------------------\n");
  printf("%-24s%35.2f\n", "Total value of inventory", total_value);
  printf("%-24s%35.2f\n", "Profit since last report", profit);
}

// Note: I removed totalvalueOfInventory from the parameters. 
// Calculate that locally inside your report generation function!
void processCmds(const vs& cmds, mapsi& inventory, double& profit) {
    
    for(auto& cmd : cmds) {
        std::stringstream ss(cmd);
        std::string command;
        ss >> command;
        
        if (command == "new") {
            std::string name;
            double buyAt, sellAt;
            ss >> name >> buyAt >> sellAt;
            inventory.insert({name, {buyAt, sellAt, 0}});
            
        } else if (command == "buy") {
            std::string name;
            int quantity;
            ss >> name >> quantity;
            
            auto it = inventory.find(name);
            if (it != inventory.end()) {
                // By using '&', we modify the map's memory directly!
                Item& item = it->second; 
                item.quantity += quantity;
            }
            
        } else if (command == "sell") {
            std::string name;
            int quantity;
            ss >> name >> quantity;
            
            auto it = inventory.find(name);
            if (it != inventory.end()) {
                Item& item = it->second;
                
                // 1. Decrease inventory
                item.quantity -= quantity; 
                
                // 2. Add profit: (Selling Price - Buying Price) * Qty
                profit += (item.sellAt - item.buyAt) * quantity;
            }
            
        } else if(command == "delete") { // Better to be explicit than just "else"
            std::string name;
            ss >> name; // MUST read the name from the stream!
            
            auto it = inventory.find(name);
            if (it != inventory.end()) {
                Item& item = it->second;
                
                // Write off the remaining inventory at COST (buyAt)
                profit -= item.buyAt * item.quantity;
                
                // Remove from map
                inventory.erase(it); 
            }
        } else if (command == "report") {
            // If your 'cmds' vector includes the 'report' keyword,
            // call your report generation function here!
            // PrintReport(inventory, profit);
          printReport(inventory, profit);
          profit = 0.0;
          std::cout << std::endl;
        }
    }
}



namespace algorithms::onlinejudge::strings::inventory_maintenance
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

        std::string line;
        vs cmds;
        mapsi inventory;
        double profit = 0.0;
        while(std::getline(std::cin, line) && line != "*") {
          std::string cmd = trim(line);
          cmds.push_back(cmd);
        }
        processCmds(cmds, inventory, profit);
    }
}
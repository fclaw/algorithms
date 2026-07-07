/*
───────────────────────────────────────────────────────────────
🧳 UVa 11385 Da Vinci Code, https://onlinejudge.org/external/113/11385.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;


vi global_fibs;

void generate_fibs() {
  global_fibs.push_back(1); // F_1 = 1
  global_fibs.push_back(1); // F_2 = 1 (Or start at 2, depending on problem mapping)
    
  long long next = 2; // Use long long to prevent overflow during calculations
  int i = 2;
    
  // 2147483647 is the exact value of INT_MAX (2^31 - 1)
  while (next <= 2147483647LL) {
    global_fibs.push_back(static_cast<int>(next));
    next = (long long)global_fibs[i] + global_fibs[i - 1];
    i++;
  }
}

// Returns the 1-based index (serial number) of the Fibonacci value
// Returns -1 if the value is not a valid Fibonacci number
int get_fib_serial_number(int value) {
  // std::lower_bound performs an O(log 46) binary search (approx 5 steps!)
  auto it = std::lower_bound(global_fibs.begin(), global_fibs.end(), value);
    
  if (it != global_fibs.end() 
      && *it == value) {
    // std::distance returns the 0-based index. We add 1 for the 1-based serial number.
    return std::distance(global_fibs.begin(), it) + 1;
  }
    
  return -1; // Error fallback
}


std::string decrypt(int length, const vi& fibs, const std::string& encrypted_msg) {
  
  std::string decrypted_msg(length, ' ');
  for(int i = 0; i < (int)fibs.size(); ++i) {
    int pos = get_fib_serial_number(fibs[i]);
    decrypted_msg[pos - 1] = encrypted_msg[i];
  }
  return decrypted_msg;
}


namespace algorithms::onlinejudge::strings::Da_Vinci_code
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

        // init global fibs series 
        generate_fibs();
        global_fibs.erase(global_fibs.begin());

        int t_cases;
        std::cin >> t_cases;
        while(t_cases--) {
          int N;
          std::cin >> N;
          vi fibs(N);
          int max_fib = 0;
          for(int i = 0; i < N; ++i) {
            std::cin >> fibs[i];
            max_fib = std::max(max_fib, fibs[i]);
          }
          std::string raw_encrypted_msg;
          std::cin.ignore();
          std::getline(std::cin, raw_encrypted_msg);
          std::stringstream ss(raw_encrypted_msg);
          std::string encrypted_msg;
          char c;
          while(ss >> c) {
            if(std::isupper(c)) {
              encrypted_msg += c;
            }
          }

          int msg_length = get_fib_serial_number(max_fib);
          std::cout << decrypt(msg_length, fibs, encrypted_msg) << std::endl;
        }
    }
}
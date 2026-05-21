/*
───────────────────────────────────────────────────────────────
🧳 UVa 645 File Mapping, https://onlinejudge.org/external/6/645.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vs = std::vector<std::string>;


struct Directory
{
    std::string name;
    std::vector<Directory*> subdirectories;
    std::vector<std::string> files;
    Directory* parent;

    Directory(std::string n) : name(n) {}


    void print(int depth) {
        std::string indent = "";
        for (int i = 0; i < depth; ++i) indent += "|     ";
        
        std::cout << indent << name << "\n";
        
        for (auto& sub : subdirectories) {
            sub->print(depth + 1);
        }
        
        std::sort(files.begin(), files.end());
        for (const auto& f : files) {
            std::cout << indent << f << "\n";
        }
    }
};


void fileSystemBuilder(const vs& lines, int i, Directory* dir) {
  if(i >= (int)lines.size()) {
    return;
  }

  /**
   * ============================================================================
   * THE ELEGANCE OF THE "PARENT FALLBACK" (The Cursor Pattern)
   * ============================================================================
   * This specific block is the "engine" of the recursive builder. 
   * 
   * In standard recursion, you typically "go down" a level with a function call 
   * and "come up" by returning from that function. However, this implementation 
   * uses a "Cursor Pattern" where the Directory* acts as a movable pointer (CWD).
   *
   * if (lines[i] == "]") { 
   *     fileSystemBuilder(lines, i + 1, dir->parent); 
   *     return; 
   * }
   *
   * WHY THIS IS SUBTLE AND BRILLIANT:
   * ---------------------------------
   * 1. SYNCHRONIZED STATE: 
   *    The function doesn't just "unwind" the stack; it actively navigates the 
   *    Tree while simultaneously advancing the Input Stream (i + 1). By passing 
   *    `dir->parent`, we are explicitly performing a "cd .." (Change Directory Up).
   *
   * 2. ELIMINATION OF "POST-RECURSION" SYNC:
   *    In most recursive parsers, you have to worry about where the input index 
   *    is AFTER a recursive call returns. Here, because we pass both the new 
   *    index and the new location in the tree to the NEXT recursive call, the 
   *    "Input Cursor" and the "Tree Cursor" are always perfectly in sync.
   *
   * 3. LOGICAL MAPPING:
   *    - Seeing a 'd': We create a child and move the cursor DOWN.
   *    - Seeing an 'f': We stay in the current node and move the cursor FORWARD.
   *    - Seeing a ']': We move the cursor UP to the parent.
   *
   * By treating the parent pointer as a valid destination for the next state, 
   * the code avoids complex return-value management and treats the file system 
   * like a map the parser is walking through.
   * ============================================================================
   */
  if(lines[i] == "]") {
    fileSystemBuilder(lines, i + 1, dir->parent);
    return;
  }

  if(lines[i].front() == 'f') {
    dir->files.push_back(lines[i]);
    fileSystemBuilder(lines, i + 1, dir);
  }

  if(lines[i].front() == 'd') {
    dir->subdirectories.push_back(new Directory(lines[i]));
    dir->subdirectories.back()->parent = dir;
    fileSystemBuilder(lines, i + 1, dir->subdirectories.back());
  }
}



namespace algorithms::onlinejudge::strings::file_mapping
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
        vs lines;
        int t_cases = 1;
        bool is_first = true;
        while(std::getline(std::cin, line) && line != "#") {

          if(line == "*") {

            if(is_first) is_first = false;
            else std::cout << std::endl;

            Directory* root = new Directory("ROOT");
            fileSystemBuilder(lines, 0, root);
            printf("DATA SET %d:\n", t_cases++);
            root->print(0);
            lines.clear();
          } else {
            lines.push_back(line);
          }
        }
    }
}
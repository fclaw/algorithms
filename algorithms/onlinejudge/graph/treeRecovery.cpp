 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 536 Tree Recovery, rt: s
 ───────────────────────────────────────────────────────────────
 * =====================================================================================
 * ALGORITHMIC STRATEGY: UVa 536 - Tree Recovery
 * =====================================================================================
 *
 * This problem requires reconstructing a unique binary tree from its pre-order and
 * in-order traversals, and then printing the post-order traversal. The core of the
 * solution is a recursive algorithm that leverages the complementary properties of
 * the two given traversal strings.
 *
 * The logic is based on the following visual model:
 *
 * --- The Sketch of the Solution ---
 *
 * Pre-order Traversal String:
 * +------+---------------------+----------------------+
 * | Root | Left Subtree Nodes  | Right Subtree Nodes  |
 * +------+---------------------+----------------------+
 * ^      ^                     ^
 * |      |                     |
 * pos    pos + 1               pos + 1 + len(Left Subtree)
 * (Root of Current Tree) (Root of Left Subtree)  (Root of Right Subtree)
 *
 *
 * In-order Traversal String:
 * +---------------------+------+----------------------+
 * | Left Subtree Nodes  | Root | Right Subtree Nodes  |
 * +---------------------+------+----------------------+
 * <------ len ---------->
 * (Size of Left Subtree)
 *
 *
 * --- The Duality of Pre-order and In-order ---
 *
 * 1.  THE ROLE OF PRE-ORDER: [Root | Left Subtree | Right Subtree]
 *     The pre-order traversal's primary role is to IDENTIFY THE ROOT. The very
 *     first element of any given pre-order subsequence is always the root of the
 *     tree (or subtree) that the subsequence represents.
 *
 * 2.  THE ROLE OF IN-ORDER: [Left Subtree | Root | Right Subtree]
 *     The in-order traversal's primary role is to DETERMINE THE STRUCTURE. Once we
 *     identify the root (using the pre-order string), its position in the
 *     in-order string cleanly partitions all other nodes into two sets: everything
 *     to its left belongs to the left subtree, and everything to its right belongs
 *     to the right subtree. This immediately gives us the SIZE of the left subtree.
 *
 * --- The Recursive Step ---
 *
 * The `restore_tree` function solves a subproblem defined by the boundaries of the
 * current pre-order and in-order subsequences.
 *
 * 1.  FIND THE ROOT:
 *     The root of the current subtree is `pre_order[pre_start]`.
 *
 * 2.  FIND THE PARTITION & LEFT SUBTREE SIZE:
 *     We find the position of this root value in the current in-order subsequence.
 *     `left_subtree_size = root_pos_in_order - in_start;`
 *
 * 3.  RECURSE ON THE LEFT SUBTREE:
 *     The subproblem for the left child is defined by:
 *     - Pre-order string: Starts at `pre_start + 1`.
 *     - In-order string: The left partition we found in step 2.
 *
 * 4.  RECURSE ON THE RIGHT SUBTREE:
 *     The starting position for the right subtree's pre-order traversal is calculated
 *     exactly as shown in the sketch: `pre_start + 1 + left_subtree_size`.
 *
 * By following this recursive process, the unique tree is built. The final step is
 * a simple post-order traversal on the recovered tree. For efficiency, the
 * positions of characters in the in-order string are pre-calculated and stored in
 * a hash map for O(1) lookups.
 *
 */

#include "../debug.h"
#include "../../aux.h"
#include "tools/tree.cpp"
#include <bits/stdc++.h>



namespace tree = algorithms::onlinejudge::graph::tools::tree;

namespace algorithms::onlinejudge::graph::tree_recovery
{
    /** https://onlinejudge.org/external/5/536.pdf */
    std::string preorder_s, inorder_s;
    std::unordered_map<char, int> inorder_positions;
    tree::Tree<char>* restore_tree(size_t root_start, size_t l, size_t r) {

      if(l >= r) return nullptr;

      char root_label = preorder_s[root_start];
      tree::Tree<char>* tree = new tree::Tree<char>(root_label, root_start);

      size_t m = inorder_positions.at(root_label);
      size_t left_size = m - l;
      tree->left = restore_tree(root_start + 1, l, m);
      tree->right = restore_tree(root_start + left_size + 1, m + 1, r);
      return tree;
    }
    void do_postorder(tree::Tree<char>* tree, std::string& tree_s) {

       if(tree == nullptr) return;

       do_postorder(tree->left, tree_s);
       do_postorder(tree->right, tree_s);

       char label = tree->val;
       tree_s.push_back(label);
    }
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

        while(while_read(preorder_s, inorder_s)) {

          // Pre-compute inorder positions for O(1) lookups
          inorder_positions.clear();
          for (int i = 0; i < (int)inorder_s.length(); ++i) {
            inorder_positions[inorder_s[i]] = i;
          }

          tree::Tree<char>* tree = restore_tree(0, 0, inorder_s.length());
          std::string tree_s;
          do_postorder(tree, tree_s);
          std::cout << tree_s << std::endl;
        }
    }
}
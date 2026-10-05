# 🌲 The Complete Roadmap to Dynamic Programming on Trees (Tree DP)

**Document Type:** Curriculum, Architecture Guide & Contest Reference
**Target:** From Foundational Post-Order Traversal to Advanced Re-Rooting & DSU on Trees

---

## 🏛️ The Three Universal Invariants of Tree DP

Before writing a single line of code, every Tree DP problem relies on these three mathematical truths:

1. **Subtree Independence (Optimal Substructure):**Removing node $u$ splits the tree into completely disjoint subtrees. Decisions in child branch $A$ have **zero interference** with child branch $B$.
2. **Post-Order DFS (The Execution Engine):**Always dive down to the leaves first. A parent node computes its DP state **only after all its children have finalized their states**.
3. **Data-Oriented Design (DOD):**
   Keep the tree structure minimal (`struct Node { int id; vi children; int parent; }`). Store all weights, subtree sizes, and DP tables in **flat, parallel arrays** for $O(1)$ random access and cache locality.

---

## 🗺️ The 4-Tier Progression Curriculum

```text
========================================================================================
[ LEVEL 1: Single-Pass Foundations ]
  │   ├── Subtree Sizes, Heights, and Depths
  │   ├── Include / Exclude (Max Independent Set, Vertex Cover)
  │   └── Single-Pass Tree Diameter (The "Apex" Model)
  │
[ LEVEL 2: Multi-State & Strict Constraints ]
  │   ├── Dual-Objective States (Lexicographical Comparators)
  │   ├── Directional Coverage (Served from Above vs. Served from Below)
  │   └── Exact-1 Coverage (The "Razor's Edge" Dominating Set)
  │
[ LEVEL 3: Subtree Convolutions & Merging ]
  │   ├── Tree Knapsack DP (The Expanding Bar Model)
  │   ├── The Pairwise LCA Theorem (O(N²) Geometric Proof)
  │   ├── Connected Subtree Combinatorics (Product-Sum Convolutions)
  │   └── The Dummy Root Pattern (Unifying Forests)
  │
[ LEVEL 4: The Advanced Frontiers ]  <-- (Future Horizons)
      ├── 2-Pass Re-Rooting DP (All-Roots in O(N))
      ├── DSU on Tree / "Sack" (Small-to-Large Merging in O(N log N))
      ├── Euler Tour Technique (Flattening Trees into 1D Segments)
      └── Centroid Decomposition (Divide-and-Conquer Path Queries)
========================================================================================
```

---

## 📍 LEVEL 1: Single-Pass Foundations (Conquered ✅)

### Core Concepts:

* **The Include / Exclude Duality:** A 2-state boolean switch per node (`0 = No, 1 = Yes`).
* **The Apex / Peak Model (Tree Diameter):** Every simple path has a unique highest node (LCA). Maintain the **top 2 longest downward branches** to form paths that peak at $u$.

### Mathematical Archetypes:

* **Vertex Cover:** $\text{dp}[u][1] = 1 + \sum \min(\text{dp}[v][0], \text{dp}[v][1])$, $\text{dp}[u][0] = \sum \text{dp}[v][1]$.
* **Tree Diameter:** $\text{peak\_at\_u} = \text{top}_1 + \text{top}_2$. Return $\text{top}_1$ to parent.

### Practice Checklist:

* [X] **UVa 10243** — *Fire! Fire!! Fire!!!* (Classic Vertex Cover)
* [X] **UVa 10308** — *Roads in the North* (Single-Pass Weighted Diameter)
* [ ] **LeetCode 337** — *House Robber III* (Max Independent Set on pointer tree)
* [ ] **LeetCode 124** — *Binary Tree Maximum Path Sum* (Apex branch model)

---

## 📍 LEVEL 2: Multi-State & Strict Constraints (Conquered ✅)

### Core Concepts:

* **Dual-Objective Packaging:** Bundling primary goals (e.g., minimum lampposts) and secondary tie-breakers (e.g., maximum double-lit edges) into a custom `struct State` with overloaded `operator<` and `operator+`.
* **Directional Service Invariant:** Distinguishing *who satisfies the constraint* (Parent above vs. Children below).
* **The Exact-1 Danger Zone:** While $\ge 1$ coverage is forgiving, $= 1$ coverage creates mutual exclusion, making certain states strictly impossible (`INF`).

### The 4-Case Truth Table (UVa 1218 Model):

|   Parent   |   Current   | Who serves current?                                       | Allowed for Children?                   |      Resulting DP State      |
| :---------: | :---------: | :-------------------------------------------------------- | :-------------------------------------- | :--------------------------: |
| **S** | **S** | None ($u$ is Server) | Both$S$ and $C$ in any ratio | `SERVER (0)`                          |                              |
| **C** | **S** | None ($u$ is Server) | Both$S$ and $C$ in any ratio | `SERVER (0)`                          |                              |
| **S** | **C** | Parent above ($S$)                                      | **0 Servers! All must be C!**     | `CLIENT_PARENT_SERVER (1)` |
| **C** | **C** | Must be from below                                        | **Exactly 1 child is S, rest C!** | `CLIENT_PARENT_CLIENT (2)` |

### Practice Checklist:

* [X] **UVa 10859** — *Placing Lampposts* (Dual-Objective Struct DP)
* [X] **UVa 1218** — *Perfect Service* (Exact-1 Coverage, 3-State Dominating Set)
* [ ] **UVa 11307** — *Special Coloring* ($K$-State Tree Chromatic Coloring)

---

## 📍 LEVEL 3: Subtree Convolutions & Merging (Conquered ✅)

### Core Concepts:

* **The Expanding Bar Model:** A parent's state table is iteratively expanded by convolving the left bar (`accumulated_size`) with the right bar (`incoming_child_size`).
* **The Pairwise LCA Proof:** By bounding the double loops strictly by the actual subtree sizes, the overall runtime collapses from $O(N^3)$ to **$O(N^2)$**, because every pair of nodes $(x, y)$ is merged in the convolution loop **exactly once**—at their Lowest Common Ancestor.
* **Algebraic Duality:**
  * Optimization (Knapsack): $\text{next\_dp}[i + j] = \min(\text{next\_dp}[i + j], \; \text{dp}[u][i] + \text{dp}[v][j])$
  * Combinatorics (Counting): $\text{next\_dp}[i + j] = \sum (\text{dp}[u][i] \times \text{dp}[v][j])$

```text
  |<---------------------------- L --------------------------->|
  [==== Accumulated Subtrees (1 to k-1) ====][==== New Child (k) ====]
                  size_so_far                           child_size
```

### Practice Checklist:

* [X] **UVa 1222** — *Bribing FIPA* (Tree Knapsack with Dummy Root)
* [ ] **Codeforces Blog 20935 Problem 3** — *Connected Subtree Counting of Size $\le K$*
* [ ] **Codeforces 461B** — *Appleman and Tree* (Connected component partition DP)
* [ ] **Codeforces 161D** — *Distance in Tree* ($K$-distance pairwise merge)

---

## 🚀 LEVEL 4: The Advanced Frontiers (For Future Mastery)

---

### Frontier 4.1: Two-Pass Re-Rooting DP (All-Roots in $O(N)$)

* **The Problem:** Calculate a tree answer for **every single node $u \in [1, N]$ as the root**, without running $N$ separate DFS passes.
* **The Mechanism:**
  1. **Pass 1 (Bottom-Up):** Compute $f(u)$ representing the answer inside $u$'s own subtree ("Looking Down").
  2. **Pass 2 (Top-Down):** Push $g(v)$ down from parent $u$ to child $v$, representing the answer in the "rest of the tree" outside $v$ ("Looking Up").
  3. **Transition Trick:** Compute $g(v)$ in $O(1)$ by subtracting $v$'s contribution from $u$'s total:
     $$
     g(v) = \text{combine}\big(\text{Parent\_Total} - f(v)\big)
     $$
* **Benchmark Practice:**
  * **Codeforces 219D** — *Choosing Capital for Treeland*
  * **CSES Tree Distances I & II**

---

### Frontier 4.2: DSU on Tree / "Sack" (Small-to-Large Merging)

* **The Problem:** Answer queries about colors/frequencies in every node's subtree (e.g., *"How many distinct values appear $\ge K$ times in $u$'s subtree?"*).
* **The Mechanism:**
  * Naive `std::set` merging takes $O(N^2)$.
  * Instead, identify the **Heavy Child** (child with largest subtree size).
  * Keep the heavy child's data in the global data structure, and only insert elements from the **Light Children**.
  * Elements are moved at most $O(\log N)$ times $\implies$ Total Time: **$O(N \log N)$**!
* **Benchmark Practice:**
  * **Codeforces 600E** — *Lomsat gelhral*
  * **Codeforces 570D** — *Tree Requests*

---

### Frontier 4.3: The Euler Tour Technique (Flattening Trees)

* **The Problem:** Applying range-query data structures (Segment Trees, Fenwick Trees) to subtrees.
* **The Mechanism:**
  * Record entry and exit times during DFS: `in[u]` and `out[u]`.
  * **The Magic Invariant:** The entire subtree of $u$ corresponds to a **contiguous 1D subarray** in the range:
    $$
    [\text{in}[u], \; \text{out}[u]]
    $$
  * A subtree update/query is converted into an ordinary **1D Range Query** on a Segment Tree in $O(\log N)$!
* **Benchmark Practice:**
  * **CSES Subtree Queries**
  * **Codeforces 383C** — *Propagating tree*

---

### Frontier 4.4: Centroid Decomposition (Divide-and-Conquer on Trees)

* **The Problem:** Answer path queries on a tree of length $N \le 200,000$ (e.g., *"Count paths with length $\le K$ or satisfying a property"*).
* **The Mechanism:**
  * Find the **Centroid** of the tree (a node whose removal leaves no component larger than $N / 2$).
  * Count paths passing through the centroid in $O(\text{Size})$.
  * Recursively decompose the remaining subtrees.
  * Tree depth is bounded by $O(\log N) \implies$ Total Time: **$O(N \log N)$**!
* **Benchmark Practice:**
  * **Codeforces 321C** — *Ciel the Commander*
  * **SPOJ QTREE5** — *Query on a tree V*

---

## 🛠️ The Tree DP Battle Checklist (Contest Card)

Before submitting any Tree DP code, verify these 5 checkpoints:

1. **[ ] The $N = 1$ Edge Case:** Does the tree have only 1 node? (corridors = 0, edges = 0, loops don't run). Ensure base cases handle $N = 1$ explicitly!
2. **[ ] The Integer Overflow Guard:** If using `INF`, is it small enough that `INF + INF` fits in 32-bit signed integer? ($10^5$ is safe; $10^9$ will wrap around into negative numbers!).
3. **[ ] The Subtree Bounding Limits:** Are the convolution loops bounded by `subtree_size[u]` and `subtree_size[v]`, rather than a flat $N$?
4. **[ ] Forest Unification:** Is the graph guaranteed to be connected? If it's a forest, did you add a **Dummy Root 0** or run a component loop over `visited[]`?
5. **[ ] Direction of Service:** For client/server or dominating set problems, is the root treated properly? (The root has no parent, so it can never be served from above!).

---

*Save this file as `Tree_DP_Roadmap.md` in your algorithm repository for ongoing study and review.*

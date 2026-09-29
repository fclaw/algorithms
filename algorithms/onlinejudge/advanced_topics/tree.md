
---

# Comprehensive Guide to Dynamic Programming on Trees (Tree DP)

**Author:** Competitive Programming Reference Series
**Topic:** Graph Theory & Advanced Dynamic Programming
**Language:** C++11 / Modern C++

---

## 1. Executive Summary & Core Foundations

### 1.1 Why Trees Make DP Easy

In general graphs, dynamic programming is difficult because cycles create circular dependencies. A tree, however, is a **Directed Acyclic Graph (DAG) with unique structural properties**:

1. **Acyclicity:** There are no loops or cycles.
2. **Subtree Independence (Optimal Substructure):** Removing any node $u$ splits the graph into completely disjoint, independent subtrees. Decisions made in child subtree $A$ have zero interference with child subtree $B$.
3. **Natural Topological Order:** Post-order depth-first search (DFS) naturally resolves all dependencies from the leaves up to the root.

```text
                  u (Parent)
                /   \
              /       \
       Subtree A     Subtree B
       (Disjoint)    (Disjoint)
```

---

## 2. Software Architecture: Data-Oriented Design (DOD)

In C++, avoid deeply nested object trees (e.g., `struct Node { vector<Node> children; }`). Deep nesting causes pointer chasing, heap fragmentation, and expensive recursive copies.

### 2.1 The Decoupled Pattern

* **The Skeleton (Topology):** Stores only connectivity and parentage.
* **The Flesh (State):** Flat, contiguous arrays for costs, weights, and DP state tables.

```cpp
// 1. Pure Topology (The Skeleton)
struct Node {
    int id;          // Unique node ID (1 to N, or 0 for dummy root)
    vi children;     // Subordinate IDs
    int parent = -1; // Dominating parent ID (-1 if root)
};

// 2. Flat Parallel Storage (The Flesh)
std::vector<Node> forest(N + 1);
vi weights(N + 1);
vi subtree_size(N + 1, 0);
vvi dp(N + 1, vi(M + 1, INF));
```

### 2.2 The "Dummy Root" Pattern (Unifying Forests)

If an input consists of multiple disconnected trees (a forest), create a **Dummy Root (Node 0)**:

1. Initialize `forest[0].id = 0`.
2. For any node with `parent == -1`, attach it to Node 0: `forest[0].children.push_back(node.id)`.
3. Set the direct cost of Node 0 to $\infty$ (cannot be bought).
4. Run a single DFS from Node 0: `dfs(0)`. The entire forest is now solved as **one single tree**.

---

## 3. The Three Universal Archetypes of Tree DP

---

### Archetype 1: The "Include / Exclude" Pattern (0/1 State)

* **Classic Problems:** Maximum Independent Set on a Tree, Vertex Cover, House Robber III.
* **Objective:** Select nodes of maximum weight such that no two chosen nodes share an edge.

#### State Definition:

* `dp[u][0]`: Maximum weight in $u$'s subtree **without** choosing node $u$.
* `dp[u][1]`: Maximum weight in $u$'s subtree **while choosing** node $u$.

#### Recurrence Equations:

$$
\text{dp}[u][1] = \text{weight}[u] + \sum_{v \in \text{children}(u)} \text{dp}[v][0]
$$

$$
\text{dp}[u][0] = \sum_{v \in \text{children}(u)} \max(\text{dp}[v][0], \; \text{dp}[v][1])
$$

#### Complexity:

* **Time:** $O(N)$
* **Space:** $O(N)$

---

### Archetype 2: The "Tree Knapsack" Pattern (Capacity / Bounded Votes)

* **Classic Problems:** UVa 1222 (Bribing FIPA), Subtree Selection with Budget, Tree Pruning.
* **Objective:** Select items within a tree hierarchy to satisfy a global capacity/budget $m$.

#### State Definition:

$$
\text{dp}[u][v] = \text{Minimum cost to obtain exactly } v \text{ items from } u\text{'s subtree}
$$

#### The Two-Phase Transition:

##### Phase 1: Knapsack Convolution Across Sibling Subtrees

Because sibling subtrees are disjoint, their DP tables can be merged like items in a 0-1 knapsack:

```cpp
vi next_dp(m + 1, INF);
for (int p_v = 0; p_v <= subtree_size[u]; ++p_v) {
    for (int c_v = 0; c_v <= subtree_size[child] && p_v + c_v <= m; ++c_v) {
        next_dp[p_v + c_v] = std::min(next_dp[p_v + c_v], dp[u][p_v] + dp[child][c_v]);
    }
}
dp[u] = std::move(next_dp);
```

##### Phase 2: Direct Subtree Override (Node $u$'s Choice)

If node $u$ provides a wholesale buyout price (`cost[u]`) that gives all $\text{subtree\_size}[u]$ nodes:

$$
\text{dp}[u][\text{subtree\_size}[u]] = \min(\text{dp}[u][\text{subtree\_size}[u]], \; \text{cost}[u])
$$

---

### Archetype 3: The "Re-Rooting" DP (2-Pass All-Roots)

* **Classic Problems:** Tree Centroid, Sum of Distances to All Other Nodes, Longest Path per Root.
* **Objective:** Compute an answer for every node $u \in [1, N]$ as if $u$ were the root of the tree, in $O(N)$ total time instead of $O(N^2)$.

#### Algorithm:

1. **Pass 1 (Bottom-Up DFS):** Choose an arbitrary root (e.g., Node 1). Compute subtree sizes and local answers for all subtrees.
2. **Pass 2 (Top-Down DFS):** Traverse downward from parent $u$ to child $v$. Re-root the tree at $v$ in $O(1)$ by subtracting $v$'s contribution from $u$, then adding $u$'s adjusted value to $v$.

---

## 4. Complexity Optimization: The Subtree Size Bound

A naive Tree Knapsack loops up to $N$ for every child merge, yielding $O(N \cdot M^2) \to O(N^3)$.

### The Subtree Bounding Theorem:

If the inner loops are strictly bounded by the **actual sizes of the subtrees being merged**:

```cpp
for (int p_v = 0; p_v <= subtree_size[u]; ++p_v)
    for (int c_v = 0; c_v <= subtree_size[child]; ++c_v)
```

**The overall time complexity collapses mathematically to $O(N^2)$ (or $O(N \cdot M)$)!**

#### Proof (The Pairwise Merge Argument):

Every execution of the inner loop body corresponds to pairing one node from the parent's current component with one node from the child's component.

* Any two nodes $x$ and $y$ in the tree are merged **exactly once in the entire algorithm**—at their unique Lowest Common Ancestor (LCA).
* Total pairs of nodes = $\binom{N}{2} = \frac{N(N - 1)}{2} = \mathbf{O(N^2)}$.

---

## 5. Master C++ Implementation Template (Tree Knapsack)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using vi = std::vector<int>;
using vvi = std::vector<vi>;

const int INF = 1e9;

struct Node {
    int id;
    vi children;
    int parent = -1;
};

void dfs(int u, 
         const std::vector<Node>& forest, 
         const vi& cost, 
         vvi& dp, 
         vi& subtree_size, 
         int max_v) 
{
    subtree_size[u] = 1;
    dp[u][0] = 0;

    // Post-Order: Solve children first
    for (int child : forest[u].children) {
        dfs(child, forest, cost, dp, subtree_size, max_v);

        // Knapsack merge of child into parent
        vi next_dp(max_v + 1, INF);

        int max_parent_take = std::min(subtree_size[u], max_v);
        int max_child_take  = std::min(subtree_size[child], max_v);

        for (int p_v = 0; p_v <= max_parent_take; ++p_v) {
            if (dp[u][p_v] == INF) continue;
            for (int c_v = 0; c_v <= max_child_take && p_v + c_v <= max_v; ++c_v) {
                if (dp[child][c_v] == INF) continue;

                next_dp[p_v + c_v] = std::min(next_dp[p_v + c_v], 
                                              dp[u][p_v] + dp[child][c_v]);
            }
        }

        subtree_size[u] += subtree_size[child];
        for (int v = 0; v <= std::min(subtree_size[u], max_v); ++v) {
            dp[u][v] = next_dp[v];
        }
    }

    // Direct wholesale purchase override (for non-dummy nodes)
    if (u != 0 && subtree_size[u] <= max_v) {
        dp[u][subtree_size[u]] = std::min(dp[u][subtree_size[u]], cost[u]);
    }
}

int solve_tree_knapsack(int n, int m, const std::vector<Node>& forest, const vi& cost) {
    vvi dp(n + 1, vi(n + 1, INF));
    vi subtree_size(n + 1, 0);

    // Solve the entire unified tree from dummy root 0
    dfs(0, forest, cost, dp, subtree_size, n);

    // Extract minimum cost for AT LEAST m items
    int ans = INF;
    for (int v = m; v <= n; ++v) {
        ans = std::min(ans, dp[0][v]);
    }
    return ans;
}
```

---

## 6. Contest / Interview Mental Checklist

1. **Hierarchy Check:** Is the graph a tree or forest? (In-degree $\le 1$, no cycles).
2. **Component Unification:** Does the problem have multiple roots? $\to$ Add **Dummy Root 0**.
3. **Subtree Independence:** Can sibling subtrees be merged independently? $\to$ Use a **Knapsack Merge**.
4. **Local Overrides:** Does buying a parent bypass child costs? $\to$ Apply an **Override step** after merging children.
5. **Query Objective:** Does the problem ask for *exactly* $m$ or *at least* $m$? $\to$ Query $\min_{v=m}^{N} \text{dp}[0][v]$ for "at least".

---

*End of Document. Suitable for archiving in competitive programming libraries.*

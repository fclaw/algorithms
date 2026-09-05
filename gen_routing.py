#!/usr/bin/env python3
import random
import sys

def generate_network(N, edge_density="medium", force_type=None):
    """
    Generates a directed network with N nodes.
    force_type:
      - 'solvable_hub': Forces 1 -> hub -> 2 and 2 -> hub -> 1
      - 'solvable_disjoint': Forces 1 -> A -> 2 and 2 -> B -> 1
      - 'impossible': Guarantees no return path from 2 -> 1
      - None: Fully random
    """
    edges = set()
    
    def add_edge(u, v):
        if u != v: # No self-loops
            edges.add((u, v))

    nodes = list(range(1, N + 1))
    
    if force_type == 'solvable_hub' and N >= 3:
        # Create a shared hub H (e.g., node 3)
        hub = 3
        add_edge(1, hub)
        add_edge(hub, 2)
        add_edge(2, hub)
        add_edge(hub, 1)
        
    elif force_type == 'solvable_disjoint' and N >= 4:
        # 1 -> 3 -> 2 and 2 -> 4 -> 1
        add_edge(1, 3)
        add_edge(3, 2)
        add_edge(2, 4)
        add_edge(4, 1)
        
    elif force_type == 'impossible':
        # Node 2 has NO outgoing edges (strictly impossible to return to 1)
        pass

    # Add random extra directed edges
    max_possible_edges = N * (N - 1)
    if edge_density == "sparse":
        target_M = min(max_possible_edges, random.randint(N, N + 5))
    elif edge_density == "dense":
        target_M = min(max_possible_edges, random.randint(N * 2, N * 3))
    else: # medium
        target_M = min(max_possible_edges, random.randint(N, N * 2))

    attempts = 0
    while len(edges) < target_M and attempts < 1000:
        attempts += 1
        u = random.choice(nodes)
        v = random.choice(nodes)
        
        # If impossible case, don't allow edges leaving node 2
        if force_type == 'impossible' and u == 2:
            continue
            
        add_edge(u, v)

    edge_list = list(edges)
    random.shuffle(edge_list)
    return N, len(edge_list), edge_list

def main():
    # Number of networks to generate (default 5)
    NUM_CASES = int(sys.argv[1]) if len(sys.argv) > 1 else 5
    
    types = ['solvable_hub', 'solvable_disjoint', 'impossible', None]

    for _ in range(NUM_CASES):
        # Choose random size N between 3 and 12 (easy to inspect and verify)
        N = random.randint(3, 10)
        t = random.choice(types)
        
        n_nodes, m_edges, edges = generate_network(N, edge_density="medium", force_type=t)
        
        print(f"{n_nodes} {m_edges}")
        for u, v in edges:
            print(f"{u} {v}")
            
    # Terminate with "0 0" as required by UVa 1057
    print("0 0")

if __name__ == "__main__":
    main()
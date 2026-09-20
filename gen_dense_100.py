#!/usr/bin/env python3
import random

def generate_dense_100():
    N = 100
    laser_c = 25
    sensor_r = 75
    
    # Initialize 100x100 grid of empty space '.'
    grid = [['.' for _ in range(N + 1)] for _ in range(N + 1)]
    
    # 1. Place the 7 key active mirrors
    active_mirrors = {
        (20, 25): '/',
        (20, 10): '\\',
        (5, 10): '/',
        (5, 50): '\\',
        (60, 50): '/',
        (30, 30): '/',
        (30, 80): '\\',
        (75, 80): '\\'
    }
    
    for (r, c), m in active_mirrors.items():
        grid[r][c] = m
        
    # 2. Protect the beam corridors so no random decoys block the path
    protected_cells = set()
    protected_cells.add((60, 30)) # The target spot for the new mirror!
    
    # Segment 1: Col 25 from row 1 to 20
    for r in range(1, 20): protected_cells.add((r, 25))
    # Segment 2: Row 20 from col 10 to 25
    for c in range(11, 25): protected_cells.add((20, c))
    # Segment 3: Col 10 from row 5 to 20
    for r in range(6, 20): protected_cells.add((r, 10))
    # Segment 4: Row 5 from col 10 to 50
    for c in range(11, 50): protected_cells.add((5, c))
    # Segment 5: Col 50 from row 5 to 60
    for r in range(6, 60): protected_cells.add((r, 50))
    # Segment 6: Row 60 from col 30 to 50
    for c in range(31, 50): protected_cells.add((60, c))
    # Segment 7: Col 30 from row 30 to 60
    for r in range(31, 60): protected_cells.add((r, 30))
    # Segment 8: Row 30 from col 30 to 80
    for c in range(31, 80): protected_cells.add((30, c))
    # Segment 9: Col 80 from row 30 to 75
    for r in range(31, 75): protected_cells.add((r, 80))
    # Segment 10: Row 75 from col 80 to 100
    for c in range(81, 101): protected_cells.add((75, c))
    
    # 3. Add ~1,500 random decoy mirrors across the remaining space
    random.seed(42) # Deterministic random
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if (r, c) not in active_mirrors and (r, c) not in protected_cells:
                if random.random() < 0.16: # ~16% mirror density
                    grid[r][c] = random.choice(['/', '\\'])
                    
    # 4. Print in Kattis format
    print(f"{N} {laser_c} {sensor_r}")
    for r in range(1, N + 1):
        row_chars = [grid[r][c] for c in range(1, N + 1)]
        print(" ".join(row_chars))

if __name__ == "__main__":
    generate_dense_100()
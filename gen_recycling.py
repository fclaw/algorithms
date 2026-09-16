#!/usr/bin/env python3
import random
import sys

# Pools of materials
RECYCLABLE = [
    "paper", "glass", "plastic", "metal", "textiles", 
    "cardboard", "aluminum", "wood", "rubber", "copper"
]

NON_RECYCLABLE = [
    "Aerosol", "Battery", "Chemical", "Paint", 
    "Hazardous", "Toxic", "Medical", "Lightbulb"
]

def make_palindrome_case(depth=4):
    """Generates a nested palindrome structure like: A B C D D C B A"""
    chosen = random.sample(RECYCLABLE, min(depth, len(RECYCLABLE)))
    # Create symmetric reflection
    items = chosen + chosen[::-1]
    return items

def make_greedy_trap_case():
    """Generates the classic greedy trap: A B B C B B A"""
    a, b, c = random.sample(RECYCLABLE, 3)
    return [a, b, b, c, b, b, a]

def make_barrier_case():
    """Generates independent recyclable islands separated by non-recyclables"""
    items = []
    num_islands = random.randint(2, 4)
    for i in range(num_islands):
        island_len = random.randint(3, 6)
        items.extend(random.choices(RECYCLABLE[:4], k=island_len))
        if i + 1 < num_islands:
            # 1 or 2 barriers between islands
            items.extend(random.sample(NON_RECYCLABLE, random.randint(1, 2)))
    return items

def make_edge_cases():
    """Returns classic boundary/edge cases"""
    return [
        # Case A: Only non-recyclables
        ["Aerosol", "Battery", "Paint"],
        # Case B: All identical recyclables
        ["glass"] * 6,
        # Case C: Non-recyclables on the extreme boundaries
        ["Chemical", "paper", "glass", "paper", "Toxic"],
        # Case D: Single item
        ["plastic"]
    ]

def make_random_large_case(N=40):
    """Generates a large mixed line of recyclables and non-recyclables"""
    items = []
    for _ in range(N):
        if random.random() < 0.15:  # 15% chance of non-recyclable wall
            items.append(random.choice(NON_RECYCLABLE))
        else:
            items.append(random.choice(RECYCLABLE[:5]))
    return items

def main():
    NUM_CASES = int(sys.argv[1]) if len(sys.argv) > 1 else 8
    
    test_cases = []
    
    # 1. Add edge cases
    test_cases.extend(make_edge_cases())
    
    # 2. Add structural puzzle cases
    test_cases.append(make_greedy_trap_case())
    test_cases.append(make_palindrome_case(depth=5))
    test_cases.append(make_barrier_case())
    
    # 3. Add random large stress cases
    while len(test_cases) < NUM_CASES:
        test_cases.append(make_random_large_case(random.randint(15, 60)))
        
    # Trim to NUM_CASES
    test_cases = test_cases[:NUM_CASES]
    
    # Print in UVa 11523 format:
    # First line: Number of test cases
    print(len(test_cases))
    
    for case in test_cases:
        # N: number of items
        print(len(case))
        for item in case:
            print(item)

if __name__ == "__main__":
    main()
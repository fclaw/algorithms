#!/usr/bin/env python3
import random

# Generate 3 large testcases with N = 1000, S = 1000
T = 3
print(T)

os_list = ["Linux", "Mac", "Windows", "OS/2", "Solaris"]

for _ in range(T):
    N = 1000
    print(N)
    for i in range(N):
        city = f"N{i}"
        os = random.choice(os_list)
        val = random.randint(1, 1000)
        print(f"{city} {os} {val}")
        
    S = 1000
    print(S)
    for i in range(S):
        city = f"S{i}"
        os = random.choice(os_list)
        val = random.randint(1, 1000)
        print(f"{city} {os} {val}")
import random

def generate_test_cases(num_cases):
    for _ in range(num_cases):
        # Generate random dimensions between 2 and 10 (UVa 10500 limits are small)
        N = random.randint(2, 10)
        M = random.randint(2, 10)
        
        # Generate starting coordinates (1-indexed)
        start_r = random.randint(1, N)
        start_c = random.randint(1, M)
        
        print(f"{N} {M}")
        print(f"{start_r} {start_c}")
        
        for r in range(1, N + 1):
            row_chars = []
            for c in range(1, M + 1):
                if r == start_r and c == start_c:
                    # Starting cell MUST be empty
                    row_chars.append('0')
                else:
                    # Randomly choose 'X' or 'O'. 
                    # We bias towards 'O' to allow for more complex robot paths.
                    row_chars.append(random.choice(['X', '0', '0', '0']))
            
            # Print row with spaces between characters
            print(" ".join(row_chars))
            
    # Print the termination signal
    print("0 0")

if __name__ == "__main__":
    try:
        count = int(input("Enter number of test cases to generate: "))
        generate_test_cases(count)
    except ValueError:
        print("Please enter a valid integer.")
import random

def generate_test_cases(num_cases):
    """
    Generates 'num_cases' random test cases for the UVa 11076 problem.
    """
    # Print the number of test cases (though this problem doesn't need it,
    # it's good practice for other problems).
    # print(num_cases) # UVa 11076 doesn't read a T value, so we skip this.
    
    for _ in range(num_cases):
        # 1. Generate N, the number of digits.
        # Let's bias it towards larger N to create harder test cases.
        n = random.randint(1, 12)
        print(n)

        # 2. Generate N random digits.
        digits = [random.randint(0, 9) for _ in range(n)]
        
        # 3. Print the digits, space-separated.
        # The map(str, ...) converts each integer digit to a string.
        # ' '.join(...) combines them with spaces in between.
        print(' '.join(map(str, digits)))

    # 4. Print the termination case.
    print(0)

if __name__ == "__main__":
    # Get the desired number of test cases from the command line, default to 20000.
    import sys
    
    try:
        # Check if a command-line argument is provided
        if len(sys.argv) > 1:
            num_to_generate = int(sys.argv[1])
        else:
            num_to_generate = 20000
    except ValueError:
        print("Usage: python generate_tests.py [number_of_cases]")
        sys.exit(1)
        
    generate_test_cases(num_to_generate)
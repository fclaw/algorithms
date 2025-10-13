import random
import math

def generate_test_cases(num_cases):
    """
    Generates a specified number of test cases for UVa 10238 - Throw the Dice!
    and prints them to standard output.
    """

    # --- Configuration ---
    # Constraints from the problem description
    MIN_FACES = 1
    MAX_FACES = 50
    
    MIN_THROWS = 1
    MAX_THROWS = 50

    # Print the total number of test cases first
    print(num_cases)

    for i in range(num_cases):
        # --- Generate Random Base Values ---
        # Let's generate a mix of small and large cases
        if i < num_cases // 2:
            # Generate smaller, more typical cases first
            faces = random.randint(MIN_FACES, 20)
            throws = random.randint(MIN_THROWS, 20)
        else:
            # Generate larger, more challenging cases
            faces = random.randint(20, MAX_FACES)
            throws = random.randint(20, MAX_THROWS)

        # --- Calculate Sum Range ---
        min_sum = throws * 1
        max_sum = throws * faces

        # --- Generate a Target Sum ---
        # It's more interesting to generate sums that are actually possible.
        # Let's also add a small chance for impossible sums (edge cases).
        
        chance_for_impossible = random.random() # a float between 0.0 and 1.0

        if chance_for_impossible < 0.10: # 10% chance of an impossible target
            # Generate a target that is guaranteed to be out of range
            if random.random() < 0.5:
                # Target is too small
                target = random.randint(0, min_sum - 1)
            else:
                # Target is too large
                target = random.randint(max_sum + 1, max_sum + 50)
        else: # 90% chance of a possible target
            # Generate a target sum within the valid range [min_sum, max_sum]
            target = random.randint(min_sum, max_sum)
            
        # Ensure target isn't negative if min_sum is 0 or 1
        if target < 0:
            target = 0
            
        # Print the generated test case in the required format
        print(f"{faces} {throws} {target}")

if __name__ == '__main__':
    # You can change this number to generate more or fewer tests
    number_of_tests_to_generate = 200  
    generate_test_cases(number_of_tests_to_generate)
import random
import subprocess
import sys

# Replace this with the exact name of your compiled C++ executable
CPP_EXECUTABLE = "./exe" 

OPERATORS = ['+', '-', '*', '/']

def generate_weird_expression(max_depth, current_depth=0):
    if current_depth >= max_depth or random.random() < 0.3:
        # Generate numbers, sometimes negative, sometimes decimals
        num = str(random.randint(1, 500))
        if random.random() < 0.2: num = "-" + num
        return num
    
    op = random.choice(OPERATORS)
    left = generate_weird_expression(max_depth, current_depth + 1)
    right = generate_weird_expression(max_depth, current_depth + 1)
    
    # Randomly add massive amounts of spaces
    sp1 = " " * random.randint(0, 3)
    sp2 = " " * random.randint(0, 3)
    
    expr = f"{left}{sp1}{op}{sp2}{right}"
    
    # Wrap in parens randomly
    if random.random() < 0.6:
        expr = f"({expr})"
        # Double or triple wrap!
        if random.random() < 0.2:
            expr = f"(({expr}))"
            
    return expr

def fuzz():
    tests_run = 0
    while tests_run < 10000:
        expr = generate_weird_expression(max_depth=15)
        
        # 1. Ask Python what the answer is
        try:
            py_ans = eval(expr)
            # Skip massive numbers or deep floats to avoid standard precision differences
            if abs(py_ans) > 1e6: continue 
        except ZeroDivisionError:
            continue
        except SyntaxError:
            continue # Skip invalid Python syntax like "5 - - 3"

        # Format Python answer EXACTLY like C++ printf("%.2f")
        if abs(py_ans) < 0.005: py_ans = 0.0
        expected_str = f"{py_ans:.2f}"

        # 2. Ask your C++ program what the answer is
        try:
            # We pass the expression via standard input
            process = subprocess.Popen([CPP_EXECUTABLE], 
                                       stdin=subprocess.PIPE, 
                                       stdout=subprocess.PIPE, 
                                       stderr=subprocess.PIPE,
                                       text=True)
            
            cpp_out, cpp_err = process.communicate(input=expr + "\n", timeout=1)
            cpp_out = cpp_out.strip()
            
            # 3. Compare!
            if cpp_out != expected_str:
                print("\n" + "="*50)
                print("💥 BUG FOUND! 💥")
                print("="*50)
                print(f"Expression : {expr}")
                print(f"Python Says: {expected_str}")
                print(f"C++ Says   : {cpp_out}")
                print(f"C++ Errors : {cpp_err}")
                print("="*50)
                sys.exit(1)
                
        except subprocess.TimeoutExpired:
            print(f"\n💥 TLE / INFINITE LOOP CAUGHT! 💥\nExpression: {expr}")
            process.kill()
            sys.exit(1)

        tests_run += 1
        if tests_run % 100 == 0:
            print(f"Passed {tests_run} tests...")

    print("\n🎉 Survived 10,000 tests! The logic is bulletproof.")

if __name__ == "__main__":
    fuzz()
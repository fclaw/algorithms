#include <iostream>
#include <cstdio>
#include <numeric> // For std::gcd

// This line "pastes" your entire library into this file at compile time.
// Make sure the path is correct relative to where you save this test file.
#include "arithmetics.cpp"



// ... after the includes ...

namespace arith = algorithms::onlinejudge::maths::utility::arithmetics;

void run_tests() {
    // A lambda function to make testing concise
    auto test = [](long long b, long long m) {
        // We call your modInverse function from the arith namespace
        arith::ModInverse<unsigned long long> res = arith::modInverse((unsigned long long)b, (unsigned long long)m); 
        
        if (res.status == arith::Failure) {
            if (std::gcd(b, m) != 1) {
                printf("Correctly failed for b=%lld, m=%lld (gcd is %lld)\n", b, m, std::gcd(b, m));
            } else {
                printf("ERROR: Incorrectly failed for b=%lld, m=%lld\n", b, m);
            }
        } else {
            // Use 128-bit int to safely check the result without overflow
            unsigned __int128 check = ((unsigned __int128)res.val * b) % m;
            if (check == 1) {
                printf("PASS: modInverse(%lld, %lld) = %llu\n", b, m, res.val);
            } else {
                printf("FAIL: modInverse(%lld, %lld) gave %llu. Check value: %llu\n", b, m, res.val, (unsigned long long)check);
            }
        }
    };

    printf("--- Running Test Suite ---\n");

    // Small prime modulus
    test(2, 13);
    test(5, 13);
    test(12, 13);

    printf("\n--- Composite Modulus ---\n");
    test(5, 18);
    test(7, 18); // This is equivalent to test(25, 18)

    printf("\n--- Cases That Should Fail ---\n");
    test(2, 18);
    test(9, 18);
    test(13, 26);

    printf("\n--- Large Modulus Cases ---\n");
    unsigned long long MOD = 10000000000007ULL;
    test(2, MOD);
    test(123456789, MOD);
    test(MOD - 1, MOD);
    
    printf("\n--- Test Suite Complete ---\n");
}

int main() {
    run_tests();
    return 0;
}
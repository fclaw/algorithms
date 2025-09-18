
#include <bits/stdc++.h>


namespace algorithms::onlinejudge::maths::utility::big_integer
{
    class BigInt {
      private:
        // Digits are stored in reverse order for easier arithmetic
        // e.g., 123 is stored as {3, 2, 1}
        std::vector<int> digits;

      public:
        // Default constructor
        BigInt(unsigned long long n = 0) {
            if (n == 0) {
                digits.push_back(0);
                return;
            }
            while (n > 0) {
                digits.push_back(n % 10);
                n /= 10;
            }
        }

        // Constructor from string
        BigInt(const std::string& s) {
            if (s.empty() || s == "0") {
                digits.push_back(0);
                return;
            }
            for (int i = s.length() - 1; i >= 0; --i) {
                if (!isdigit(s[i])) {
                    throw std::invalid_argument("Invalid character in string");
                }
                digits.push_back(s[i] - '0');
            }
        }

        // Friend function for printing
        friend std::ostream& operator<<(std::ostream& os, const BigInt& b) {
            for (int i = b.digits.size() - 1; i >= 0; --i) {
                os << b.digits[i];
            }
            return os;
        }

        // --- Core Arithmetic Operations ---

        // Compound multiplication operator (shorthand version)
        // Modifies the current object. Must NOT be const.
        BigInt& operator*=(int n) {
            if (n == 0) {
                digits = {0}; // Multiplying by zero results in zero
                return *this;
            }
            if (n == 1) {
                return *this; // Multiplying by one changes nothing
            }

            int carry = 0;
            // Iterate through the existing digits and update them in-place.
            for (size_t i = 0; i < digits.size(); ++i) {
                int current = digits[i] * n + carry;
                digits[i] = current % 10;
                carry = current / 10;
            }

            // If there's a carry left over, we need to add new digits.
            while (carry > 0) {
                digits.push_back(carry % 10);
                carry /= 10;
            }
            
            // Return a reference to the modified object.
            return *this;
        }
        
        // Binary multiplication operator. Should be const.
        BigInt operator*(int n) const {
            // 1. Make a copy of the current object.
            BigInt result = *this; 
            
            // 2. Use the compound assignment operator to modify the copy.
            result *= n;
            
            // 3. Return the modified copy.
            return result;
        }

        // You can add more operators like +, -, /, % as needed
        // ...

        // --- Utility Functions ---
        
        // To get the digits for frequency counting
        const std::vector<int>& get_digits() const {
            return digits;
        }
    };

}
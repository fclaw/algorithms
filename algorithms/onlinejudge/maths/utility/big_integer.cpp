
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

        BigInt operator += (const BigInt& other) {
      int carry = 0;
    
    // The loop needs to run as long as there are digits in either number
    // or there is a carry left over.
    for (size_t i = 0; i < other.digits.size() || carry > 0; ++i) {
        // If the current number (*this) runs out of digits, we need to
        // extend it with zeros to continue the addition.
        if (i >= this->digits.size()) {
            this->digits.push_back(0);
        }

        // Get the i-th digit of the 'other' number, or 0 if it's shorter.
        int other_digit = (i < other.digits.size()) ? other.digits[i] : 0;

        // Perform the grade-school addition for this "column".
        int current = this->digits[i] + other_digit + carry;
        this->digits[i] = current % 10; // The new digit for this position
        carry = current / 10;           // The new carry for the next position
    }
    
    // Return a reference to the modified object.
    return *this;
        }
        

        // You can add more operators like +, -, /, % as needed
        // ...

        // --- Utility Functions ---
        
        // To get the digits for frequency counting
        const std::vector<int>& get_digits() const {
            return digits;
        }

        std::string get_string() const {
          std::string s;
          for(auto d : digits)
            s += std::to_string(d);
          return s;
        }
    };

    BigInt operator + (const BigInt& lhs, const BigInt& rhs) {
         // Determine which number has more digits to use as the base for our sum.
    // This is a small optimization to reduce vector reallocations.
    if (lhs.get_digits().size() > rhs.get_digits().size()) {
        BigInt result = lhs; // Make a copy of the larger number
        result += rhs;      // Add the smaller one to it
        return result;
    } else {
        BigInt result = rhs; // Make a copy of the larger (or equal-sized) number
        result += lhs;      // Add the smaller one to it
        return result;
    }
    }
}
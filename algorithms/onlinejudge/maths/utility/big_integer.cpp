
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

        BigInt& operator+=(const BigInt& other) {
          // Make sure *this is at least as long as other.
            if (digits.size() < other.digits.size()) {
                digits.resize(other.digits.size(), 0);
            }
            
            int carry = 0;
            for (size_t i = 0; i < digits.size(); ++i) {
                int other_digit = (i < other.digits.size()) ? other.digits[i] : 0;
                int current = digits[i] + other_digit + carry;
                digits[i] = current % 10;
                carry = current / 10;
            }

            // Handle final carry
            if (carry > 0) {
                digits.push_back(carry);
            }
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
        // Handle the case of the number being zero.
        if (digits.empty() || (digits.size() == 1 && digits[0] == 0)) {
            return "0";
        }

        std::string s = "";
        
        // Find the most significant digit (the last non-zero digit in our reversed vector).
        // This step is crucial for trimming leading zeros.
        int first_digit_idx = digits.size() - 1;
        while (first_digit_idx > 0 && digits[first_digit_idx] == 0) {
            first_digit_idx--;
        }
        
        // Iterate backwards from the most significant digit to the least significant.
        for (int i = first_digit_idx; i >= 0; --i) {
            s += std::to_string(digits[i]);
        }
        
        return s;
        }

        BigInt operator/(int n) const {
            if (n == 0) {
                throw std::invalid_argument("Division by zero");
            }
            BigInt result;
            result.digits.clear();
            
            long long remainder = 0;
            
            // Iterate from Most Significant Digit to Least
            for (int i = this->digits.size() - 1; i >= 0; --i) {
                // "Bring down" the next digit
                remainder = remainder * 10 + this->digits[i];
                
                result.digits.push_back(remainder / n);
                remainder = remainder % n;
            }
            
            // The result's digits are in reverse order, which is backwards for us.
            // We need to reverse them back to our standard {lsb, ..., msb} format.
            std::reverse(result.digits.begin(), result.digits.end());
            
            // Trim leading zeros from the result (e.g., if 123 / 10 = 012.3 -> 12)
            while (result.digits.size() > 1 && result.digits.back() == 0) {
                result.digits.pop_back();
            }
            
            return result;
        }


        BigInt operator*(const BigInt& other) const {
            BigInt result(0); // Start with a result of 0

            // For each digit in the other number...
            for (size_t i = 0; i < other.digits.size(); ++i) {
                int other_digit = other.digits[i];
                
                // Multiply this BigInt by that single digit.
                BigInt partial_product = (*this) * other_digit; // We already have BigInt * int
                
                // Shift the partial product to the left by 'i' positions.
                // The easiest way is to insert 'i' zeros at the beginning of its digits vector.
                if (partial_product.digits.size() != 1 || partial_product.digits[0] != 0) {
                    partial_product.digits.insert(partial_product.digits.begin(), i, 0);
                }
                
                // Add this partial product to the running total.
                result += partial_product; // We need operator+=
            }

            // Trim leading zeros on the final result
            while (result.digits.size() > 1 && result.digits.back() == 0) {
                result.digits.pop_back();
            }
            
            return result;
        }


    // It's also good practice to overload operator<< using this function
    friend std::ostream& operator<<(std::ostream& os, const BigInt& b) {
        os << b.get_string();
        return os;
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
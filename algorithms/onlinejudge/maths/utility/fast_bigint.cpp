#include <bits/stdc++.h>

namespace algorithms::onlinejudge::maths::utility::fast_bigint
{
    struct BigInt {
        static const int BASE = 1e9;
        static const int BASE_DIGITS = 9;
        std::vector<int> a; // Limbs stored in little-endian order

        BigInt() : a(1, 0) {}
        BigInt(long long v) { *this = v; }
        BigInt(const std::string& s) { read(s); }

        void trim() {
            while (a.size() > 1 && a.back() == 0) a.pop_back();
        }

        BigInt& operator=(long long v) {
            a.clear();
            do {
                a.push_back(v % BASE);
                v /= BASE;
            } while (v > 0);
            return *this;
        }

        void read(const std::string& s) {
            a.clear();
            for (int i = (int)s.length(); i > 0; i -= BASE_DIGITS) {
                if (i < BASE_DIGITS)
                    a.push_back(std::stoi(s.substr(0, i)));
                else
                    a.push_back(std::stoi(s.substr(i - BASE_DIGITS, BASE_DIGITS)));
            }
            trim();
        }

        // Comparisons
        bool operator<(const BigInt& o) const {
            if (a.size() != o.a.size()) return a.size() < o.a.size();
            for (int i = (int)a.size() - 1; i >= 0; --i)
                if (a[i] != o.a[i]) return a[i] < o.a[i];
            return false;
        }
        bool operator==(const BigInt& o) const { return a == o.a; }
        bool operator<=(const BigInt& o) const { return !(o < *this); }
        bool operator>(const BigInt& o) const  { return o < *this; }

        // Addition (A + B)
        BigInt operator+(const BigInt& o) const {
            BigInt res;
            res.a.clear();
            int carry = 0;
            for (size_t i = 0; i < std::max(a.size(), o.a.size()) || carry; ++i) {
                long long sum = carry;
                if (i < a.size()) sum += a[i];
                if (i < o.a.size()) sum += o.a[i];
                carry = sum >= BASE;
                res.a.push_back(sum % BASE);
            }
            return res;
        }

        // Subtraction (A - B, assumes A >= B)
        BigInt operator-(const BigInt& o) const {
            BigInt res = *this;
            int carry = 0;
            for (size_t i = 0; i < o.a.size() || carry; ++i) {
                long long diff = res.a[i] - carry - (i < o.a.size() ? o.a[i] : 0);
                carry = diff < 0;
                if (carry) diff += BASE;
                res.a[i] = diff;
            }
            res.trim();
            return res;
        }

        // Fast Multiplication by small integer (A * int) -> O(N)
        BigInt operator*(long long v) const {
            BigInt res;
            res.a.clear();
            long long carry = 0;
            for (size_t i = 0; i < a.size() || carry; ++i) {
                long long cur = carry + (i < a.size() ? (long long)a[i] * v : 0);
                carry = cur / BASE;
                res.a.push_back(cur % BASE);
            }
            res.trim();
            return res;
        }

        // Full Multiplication (A * B) -> O(N * M)
        BigInt operator*(const BigInt& o) const {
            BigInt res;
            res.a.assign(a.size() + o.a.size(), 0);
            for (size_t i = 0; i < a.size(); ++i) {
                long long carry = 0;
                for (size_t j = 0; j < o.a.size() || carry; ++j) {
                    long long cur = res.a[i + j] + carry + (long long)a[i] * (j < o.a.size() ? o.a[j] : 0);
                    carry = cur / BASE;
                    res.a[i + j] = cur % BASE;
                }
            }
            res.trim();
            return res;
        }


        // Fast Division by small integer (A / int) -> O(N)
        BigInt operator/(long long v) const {
            BigInt res;
            res.a.resize(a.size());
            long long rem = 0;
            for (int i = (int)a.size() - 1; i >= 0; --i) {
                long long cur = a[i] + rem * BASE;
                res.a[i] = cur / v;
                rem = cur % v;
            }
            res.trim();
            return res;
        }


        // Modulo by small integer (A % int) -> O(N)
        long long operator%(long long v) const {
            long long rem = 0;
            for (int i = (int)a.size() - 1; i >= 0; --i) {
                rem = (a[i] + rem * BASE) % v;
            }
            return rem;
        }

        // Stream I/O
        friend std::ostream& operator<<(std::ostream& os, const BigInt& b) {
            os << (b.a.empty() ? 0 : b.a.back());
            for (int i = (int)b.a.size() - 2; i >= 0; --i) {
                os << std::setw(BASE_DIGITS) << std::setfill('0') << b.a[i];
            }
            return os;
        }
        friend std::istream& operator>>(std::istream& is, BigInt& b) {
            std::string s;
            if (is >> s) b.read(s);
            return is;
        }
    };

    struct SignedBigInt {
        bool is_neg;
        BigInt mag; // Magnitude (our BigInt from earlier)

        SignedBigInt() : is_neg(false), mag(0) {}
        SignedBigInt(long long v) {
            is_neg = (v < 0);
            mag = std::abs(v);
        }

        // Multiplication: (sign1 ^ sign2) and (mag1 * mag2)
        SignedBigInt operator*(const SignedBigInt& o) const {
            SignedBigInt res;
            res.is_neg = (is_neg ^ o.is_neg);
            res.mag = mag * o.mag;
            if (res.mag == 0) res.is_neg = false; // 0 is never negative
            return res;
        }

        // Comparison for max / min in DP:
        bool operator<(const SignedBigInt& o) const {
            if (is_neg != o.is_neg) return is_neg; // Negative is smaller than positive
            if (is_neg) return o.mag < mag;        // If both negative: -10 < -5 (10 > 5)
            return mag < o.mag;                    // If both positive: normal comparison
        }

        friend std::ostream& operator<<(std::ostream& os, const SignedBigInt& b) {
            if (b.is_neg && b.mag > 0) os << "-";
            os << b.mag;
            return os;
        }
    };
}
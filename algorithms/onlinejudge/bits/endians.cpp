#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <bitset>



namespace algorithms::onlinejudge::bits::endians
{
    // https://onlinejudge.org/external/5/594.pdf, manipulate bit string with bitset
    /**
	 * 1. Convert to binary notation
     * Interpret the given signed 32-bit integer as a binary number.
     * 2. Convert to two’s complement (if negative)
     * Since the input is a signed integer, it is already stored in two’s complement form, so no extra conversion is needed.
     * 3. Reverse the bytes (not bits!)
     * The key operation here is reversing the byte order (endian conversion). Given a 32-bit integer (4 bytes), you swap:
     * Byte 1 ↔ Byte 4
     * Byte 2 ↔ Byte 3
     * This is what changes between big-endian and little-endian representation.
     * 4.Restore the integer value
     */
    const size_t N = 32;
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        std::string s;
        while(std::cin >> s)
        {
            int number = std::stoi(s);
            bool isNegative = number < 0;
            std::bitset<N> bits = std::bitset<N>(std::abs(number));
            if(isNegative) 
            {
                bits = bits.flip();
                int i = 0;
                while(bits[i] != 0)
                  bits[i++] = 0;
                bits[i] = 1;
            }
            std::bitset<N> swapped;
            for (int i = 0; i < 4; i++)
              for (int j = 0; j < 8; j++)
                // Swap byte positions
                swapped[i * 8 + j] = bits[(3 - i) * 8 + j];
            printf("%d converts to %d\n", number, (int)swapped.to_ulong());
        }
    }
}
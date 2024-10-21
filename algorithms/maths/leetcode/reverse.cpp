

namespace algorithms::math::leetcode::reverse_number
{
    /** https://leetcode.com/problems/reverse-integer  
     *  bit manipulation. General delineation
     *  1 Extract the least significant bit (LSB) of the number using bitwise AND with 1 (n & 1).
     *  2 Shift the extracted bit to the correct position in the reversed number.
     *  3 Shift the original number to the right to process the next bit.
     *  4 Repeat until all bits are processed.
     * 
     *   Start with a result initialized to 0. 
     *   For each bit in the original number:
     *   Extract the least significant bit (n & 1).
     *   Shift the result to the left (to make room for the new bit).
     *   Add the extracted bit to the result.
     *   Shift the original number to the right.
     *   Continue the process for all the bits. */
    int reverse(int x) 
    {
        return 1;
    }
}
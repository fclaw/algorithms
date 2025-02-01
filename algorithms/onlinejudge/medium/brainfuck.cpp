#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <vector>

typedef unsigned char uc;
typedef std::vector<uc> vuc;

const size_t TAPE_N = 100;

// . Output the value of the byte at the pointer.
const char O = '.';
// + Increment (increase by one) the byte at the pointer.
const char I = '+';
// - Decrement (decrease by one) the byte at the pointer.
const char D = '-';
// > Increment the pointer (to point to the next cell to the right).
const char F = '>';
// < Decrement the pointer (to point to the next cell to the left).
const char B = '<';


namespace algorithms::onlinejudge::easy::brainfuck
{
    // https://onlinejudge.org/external/119/11956.pdf, simulation; ignore ‘.’
    /**
        A display’s program is a sequence of commands executed sequentially. The commands of the display
        processor is a subset of brainfuck language commands. The commands that processor was capable to
        execute were ‘>’, ‘<’, ‘+’, ‘-’ and ‘.’, which are described in the table below. Moreover, this LED
        display has an array of 100 bytes of circular memory (initialised with zeros) and a pointer to this
        array (initialised to point to the leftmost byte of the array). This means, that after incrementing a
        pointer, which points to the rightmost byte of memory, it will point to the leftmost byte and vice versa.
        Individual bytes are circular as well, so increasing a 255 gives a 0 and vice versa
     */
    void printHex(uc cell) 
    {
        std::cout << 
        std::hex <<
        std::uppercase <<
        std::setw(2) <<
        std::setfill('0') << 
        static_cast<int>(cell);
    }

    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int tc, c = 0;
        scanf("%d", &tc);
        std::cin.ignore();

        while(tc--)
        {
            std::string sequence;
            vuc tape = vuc(TAPE_N, 0);
            auto ptr = tape.begin();
            std::getline(std::cin, sequence);

            for(auto c : sequence)
            {
                if(c == O) continue;
                if(c == I) ++(*ptr);
                else if(c == D) --(*ptr);
                else if(c == F)
                {
                    if(ptr + 1 == tape.end())
                      ptr = tape.begin();
                    else ++ptr;  
                }
                else if(c == B)
                {
                    if(ptr == tape.begin())
                      ptr = tape.end() - 1;
                    else --ptr;
                }
            }

            printf("Case %d: ", ++c); 
            for(int i = 0; i < tape.size(); i++)
            {
                printHex(tape[i]);
                if(i != tape.size() - 1) std::cout << " ";
            }
            std::cout << std::endl;
        }
    }
}
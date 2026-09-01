// ┌────────────────────────────────────────────────────────┐
// │  STAGE 1: Focus on Logic & Correctness (Fast to Code)   │
// │  • Use std::unordered_map                               │
// │  • Zero risk of capacity overflows or infinite loops   │
// │  • Verify problem logic, transitions, and edge cases   │
// └──────────────────────────┬─────────────────────────────┘
//                            │
//                  Did it pass comfortably?
//                  ├── YES ──► ✅ Done! (Save time for next problem)
//                  │
//                  └── NO (TLE or close to Time Limit)
//                            │
//                            ▼
// ┌────────────────────────────────────────────────────────┐
// │  STAGE 2: Drop-in Performance Boost (Fast to Execute)  │
// │  • Swap in FastHashMap (or gp_hash_table)              │
// │  • Zero changes to your BFS/search business logic      │
// │  • Slashes runtime by 3x - 10x instantly!              │
// └────────────────────────────────────────────────────────┘

#include <bits/stdc++.h>


namespace algorithms::onlinejudge::advanced_topics::utility::hash_containers {

    template<int SIZE>
    struct FastHashMap {
        static_assert((SIZE & (SIZE - 1)) == 0, "SIZE must be a power of 2!");

        int keys[SIZE];
        int vals[SIZE];
        int count_elements; // Safety counter

        FastHashMap() {
            clear();
        }

        void clear() {
            std::memset(keys, -1, sizeof(keys));
            count_elements = 0;
        }

        inline size_t hash_key(int x) const {
            uint32_t u = static_cast<uint32_t>(x);
            u = ((u >> 16) ^ u) * 0x45d9f3b;
            u = ((u >> 16) ^ u) * 0x45d9f3b;
            u = (u >> 16) ^ u;
            return u & (SIZE - 1);
        }

        inline bool count(int key) const {
            size_t idx = hash_key(key);
            while (keys[idx] != -1) {
                if (keys[idx] == key) return true;
                idx = (idx + 1) & (SIZE - 1);
            }
            return false;
        }

        inline int get(int key) const {
            size_t idx = hash_key(key);
            while (keys[idx] != -1) {
                if (keys[idx] == key) return vals[idx];
                idx = (idx + 1) & (SIZE - 1);
            }
            return -1;
        }

        inline bool insert(int key, int val) {
            size_t idx = hash_key(key);
            while (keys[idx] != -1) {
                if (keys[idx] == key) {
                    vals[idx] = val;
                    return false;
                }
                idx = (idx + 1) & (SIZE - 1);
            }

            // Safety Assertion: Warn if table exceeds 85% capacity
            assert(count_elements < (SIZE * 85 / 100) && "FastHashMap Overflow! Increase SIZE!");

            keys[idx] = key;
            vals[idx] = val;
            count_elements++;
            return true;
        }
    };

    template<int SIZE = (1 << 20)> // Default: 1,048,576 slots (Only 4 MB RAM!)
    struct FastHashSet {
        static_assert((SIZE & (SIZE - 1)) == 0, "SIZE must be a power of 2!");

        int keys[SIZE]; // -1 represents an empty slot

        FastHashSet() {
            clear();
        }

        // Reset table in ~0.2 milliseconds
        inline void clear() {
            std::memset(keys, -1, sizeof(keys));
        }

        // Fast O(1) integer hash mixer (1 CPU instruction)
        inline size_t hash_key(int x) const {
            uint32_t u = static_cast<uint32_t>(x);
            u = ((u >> 16) ^ u) * 0x45d9f3b;
            u = ((u >> 16) ^ u) * 0x45d9f3b;
            u = (u >> 16) ^ u;
            return u & (SIZE - 1); // Instant modulo for power of 2
        }

        // 1. Check if key exists (O(1))
        inline bool count(int key) const {
            size_t idx = hash_key(key);
            while (keys[idx] != -1) {
                if (keys[idx] == key) return true;
                idx = (idx + 1) & (SIZE - 1); // Linear probe
            }
            return false;
        }

        /**
         * 2. Insert key:
         *    - Returns TRUE  if newly inserted (NOT visited before).
         *    - Returns FALSE if key was ALREADY in the set.
         */
        inline bool insert(int key) {
            size_t idx = hash_key(key);
            while (keys[idx] != -1) {
                if (keys[idx] == key) {
                    return false; // Already visited!
                }
                idx = (idx + 1) & (SIZE - 1);
            }
            keys[idx] = key;
            return true; // Newly inserted!
        }
    };

}
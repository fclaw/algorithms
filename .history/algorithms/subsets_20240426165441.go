package main

import "fmt"

// generateSubsets is the main function to generate all subsets of a given set of integers
func generateSubsets(nums []int) [][]int {
    var subsets [][]int

    // recursive helper function to generate subsets
    var backtrack func(start int, currentSubset []int)
    backtrack = func(start int, currentSubset []int) {
        // add the current subset to the result (making a copy to avoid reference issues)
        subsets = append(subsets, append([]int(nil), currentSubset...))

        // iterate over the remaining elements
        for i := start; i < len(nums); i++ {
            // include the current element in the subset
            currentSubset = append(currentSubset, nums[i])

            // recurse with the updated subset
            backtrack(i + 1, currentSubset)

            // backtrack by removing the last added element to explore other subsets
            currentSubset = currentSubset[:len(currentSubset)-1]
        }
    }

    // start the recursive backtracking with an empty subset
    backtrack(0, []int{})

    return subsets
}

func main() {
    nums := []int{1, 2, 3} // example set
    subsets := generateSubsets(nums)

    fmt.Println("All subsets:")
    for _, subset := range subsets {
        fmt.Println(subset)
    }
}

package main

import "fmt"


func generateSubsets(xs []int) [][]int {
	var x 
	return nil
}


func main() {
    nums := []int{1, 2, 3} // example set
    subsets := generateSubsets(nums)

    fmt.Println("All subsets:")
    for i := 0; i < len(subsets); i++ {
        fmt.Println(subsets[i])
    }
}

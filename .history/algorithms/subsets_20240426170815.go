package main

import "fmt"



func main() {
    nums := []int{1, 2, 3} // example set
    subsets := generateSubsets(nums)

    fmt.Println("All subsets:")
    for _, subset := range subsets {
        fmt.Println(subset)
    }
}

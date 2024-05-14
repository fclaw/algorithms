package main

import "fmt"
import "vector"


func main() {
	fmt.Print("Enter a number: ")
	var number int64
	_, err := fmt.Scanf("%d", &number) // or %f and change grade to float64
	if err != nil {
		fmt.Printf("%s\n", err)
	} else {
		var subsets [][]int

	}
}

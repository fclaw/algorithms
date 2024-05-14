package main

import "fmt"

const boilingF = 212.3

func main() {
	var f = boilingF
	var c = (f - 32) * 5 / 9
	fmt.Printf("boiling point = %.2f°F or %g.1°C\n", f, c)
	// Output:
	// boiling point = 212°F or 100°C
}

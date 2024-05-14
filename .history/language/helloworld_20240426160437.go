package main

import "fmt"

const boilingF = 212.3

func main() {
	var f = boilingF
	var c = (f - 32) * 5 / 9
	fmt.Printf("boiling point = %.1f°F or %.1f°C\n", f, c)
	// Output:
	// boiling point = 212°F or 100°C

    x := 1
	p := &x
    fmt.Println(p)

}

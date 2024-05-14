package main

import "fmt"


func main() {
    
	var n = flag.Bool("n", false, "omit trailing newline")

	flag.Parse()

    fmt.Println(n)

	var f = boilingF
	var c = (f - 32) * 5 / 9
	fmt.Printf("boiling point = %.1f°F or %.1f°C\n", f, c)
	// Output:
	// boiling point = 212°F or 100°C

    var x int
	p := &x
    fmt.Println(*p)

}

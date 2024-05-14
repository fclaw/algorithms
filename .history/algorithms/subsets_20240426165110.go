package main

import "fmt


type vec = vector.Vector

func main() {
	fmt.Print("Enter a number: ")
	var number int64
	_, err := fmt.Scanf("%d", &number) // or %f and change grade to float64
	if err != nil {
		fmt.Printf("%s\n", err)
	} else {
		vec2 := make(vec, 2)

	}
}

package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	fmt.Print("Enter a grade: ")
	var grade int // or grade := 0
	_, err := fmt.Scanf("%d", &grade) // or %f and change grade to float64
	if err != nil {
		log.Fatal(err)
	}
}
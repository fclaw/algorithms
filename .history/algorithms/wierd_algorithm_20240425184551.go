package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	fmt.Print("Enter a number: ")
	n := 0
	_, err := fmt.Scanf("%d", &number) // or %f and change grade to float64
	if err != nil {
		log.Fatal(err)
	}
}
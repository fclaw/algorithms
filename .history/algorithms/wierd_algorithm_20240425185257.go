package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	fmt.Print("Enter a number: ")
	number := 0
	_, err := fmt.Scanf("%d", &number) // or %f and change grade to float64
	if err != nil {
		log.Fatal(err)
	} else {
		for {
			fmt.Printf("%d\t", number)
			if number == 1 {
				break
			}
			else if number % 2 == 0 {
				number /= 2
			}
			else {
				number = number * 3 + 1 
			}
		}
	}
}
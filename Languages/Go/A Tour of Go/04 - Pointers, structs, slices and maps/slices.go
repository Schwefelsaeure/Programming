package main

import "fmt"

func main() {
    primes := []int {2, 3, 5, 7, 11, 13}

    var selection []int = primes[1:3]
    fmt.Println(selection)
}

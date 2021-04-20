package main

import "fmt"

var pow = []int {1, 2, 4}

func main() {
    for i, value := range pow {
        fmt.Printf("2**%d = %d\n", i, value)
    }
}

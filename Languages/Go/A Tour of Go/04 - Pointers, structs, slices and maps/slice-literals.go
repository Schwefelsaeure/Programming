package main

import "fmt"

func main() {
    tuple_slice := []struct {
        i int
        b bool
    } {
        {1, true},
        {2, false},
    }

    fmt.Println(tuple_slice)
}

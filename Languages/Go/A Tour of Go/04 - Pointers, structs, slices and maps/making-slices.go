package main

import "fmt"

func main() {
    a := make([]int, 5)

    fmt.Println(a, len(a), cap(a))
}

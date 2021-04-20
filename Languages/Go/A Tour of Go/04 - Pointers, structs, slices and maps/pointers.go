package main

import "fmt"

func main() {
    i, j := 1, 2

    p := &i
    fmt.Println("*p: ", *p)
    *p = 3
    fmt.Println("i: ", i)

    p = &j
    *p = *p + 1
    fmt.Println("j: ", j)
}

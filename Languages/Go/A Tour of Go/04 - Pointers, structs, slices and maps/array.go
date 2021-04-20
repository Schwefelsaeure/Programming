package main

import "fmt"

func main() {
    var a[2]string
    a[0] = "Hello"
    a[1] = "World"

    fmt.Println(a[0], a[1])
    fmt.Println(a)

    primes := [3]int {2, 3, 5}
    fmt.Println(primes)
}

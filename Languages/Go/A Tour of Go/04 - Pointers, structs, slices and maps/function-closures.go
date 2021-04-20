package main

import "fmt"

func adder() func(int) int {
    sum := 0

    return func(x int) int {
        sum += x
        return sum
    }
}

func main() {
    pos, neg := adder(), adder()

    for i := 0; i < 5; i++ {
        pos(i)
        neg(-i)
    }

    fmt.Println(pos(0))
    fmt.Println(neg(0))
}

package main

import (
    "fmt"
    "math"
)

func compute(fn func(float64, float64) float64) float64 {
    return fn(2, 3)
}

func main() {
    squareSum := func(x, y float64) float64 {
        return x*x + y*y
    }

    fmt.Println(squareSum(1, 2))
    fmt.Println(compute(squareSum))
    fmt.Println(compute(math.Pow))
}

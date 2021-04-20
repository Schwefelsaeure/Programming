package main

import "fmt"

func main() {
    var slice[]int
    printSlice(slice)

    slice = append(slice, 0)
    printSlice(slice)
}

func printSlice(slice []int) {
    fmt.Printf("len=%d, cap%d, %v\n", len(slice), cap(slice), slice)
}

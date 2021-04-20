package main

import "fmt"

type Vertex struct {
    Lat float64;
    Long float64;
}

func main() {
    m := map[string]Vertex {
        "Munich": Vertex{ 1.0, 2.0 },
        "London": Vertex{ 3.0, 4.0 },
    }

    fmt.Println(m)
}

package main

import (
	"flag"
	"fmt"
)

var (
	day  = flag.Uint("day", 1, "day")
	part = flag.String("part", "a", "part")
	lang = flag.String("lang", "cpp", "language")
)

func main() {
	flag.Parse()

	fmt.Println("day: ", *day)
	fmt.Println("part: ", *part)
	fmt.Println("language: ", *lang)
}

package main

import (
	"flag"
	"fmt"
	"path/filepath"
)

var (
	day  = flag.Uint("day", 1, "day")
	part = flag.String("part", "a", "part")
	lang = flag.String("lang", "cpp", "language")
)

func main() {
	flag.Parse()

	filename := fmt.Sprintf("main.%s", *lang)
	path := filepath.Join(fmt.Sprintf("%02d", *day), *part, filename)
	fmt.Println(path)
}

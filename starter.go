package main

import (
	"flag"
	"fmt"
	"log"
	"os"
	"path/filepath"
)

var (
	day  = flag.Uint("day", 1, "day")
	part = flag.String("part", "a", "part")
	lang = flag.String("lang", "cpp", "language")
)

type Language string

const (
	Cpp    Language = "cpp"
	Python Language = `import sys

with open(sys.argv[1]) as f:
     TODO = [line.strip() for line in f]

print()
`
	Go    Language = "go"
	R     Language = "R"
	Shell Language = "sh"
)

func write(name, contents string) {
	file, createErr := os.Create(name)

	if createErr != nil {
		log.Fatal(createErr)
	}

	defer file.Close()

	_, writeErr := file.WriteString(contents)

	if writeErr != nil {
		log.Fatal(writeErr)
	}
}

func main() {
	flag.Parse()

	// TODO: validate day, part, lang
	// TODO: make string for each language

	filename := fmt.Sprintf("main.%s", *lang)
	formattedDay := fmt.Sprintf("%02d", *day)
	path := filepath.Join(formattedDay, *part, filename)
	write(path, string(Python)) // TODO: figure out the contents to write here
}

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
	Cpp Language = `#include <iostream>

int main(const int, const char** argv) {
  std::cout << TODO << '\n';
}
`
	Python Language = `import sys

with open(sys.argv[1]) as f:
     TODO = [line.strip() for line in f]

print()
`
	Go Language = `package main

import (
	"fmt"
)

func main() {
	fmt.Println(TODO)
}
`
	R Language = `args <- commandArgs(trailingOnly = TRUE)

TODO <- readLines(args[1])

cat(TODO, "\n", sep = "")
`
	Shell Language = `#!/usr/bin/env bash

echo $TODO
`
)

func languageFromExtension(extension string) (Language, error) {
	switch extension {
	case "cpp":
		return Cpp, nil
	case "go":
		return Go, nil
	case "R":
		return R, nil
	case "py":
		return Python, nil
	case "sh":
		return Shell, nil
	}
	return "", fmt.Errorf("unsupported language %s", extension)
}

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

	// TODO: validate day, part

	filename := fmt.Sprintf("main.%s", *lang)
	formattedDay := fmt.Sprintf("%02d", *day)
	path := filepath.Join(formattedDay, *part, filename)
	language, err := languageFromExtension(*lang)
	if err != nil {
		log.Fatal(err)
	}
	write(path, string(language))
}

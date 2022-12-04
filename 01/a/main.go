package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	file, err := os.Open("input.txt")
	if err != nil {
		panic("couldn't open file")
	}
	defer file.Close()

	var cals []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		cals = append(cals, scanner.Text())
	}
	if scanner.Err() != nil {
		panic("couldn't read file")
	}

	var max_elf_cals, current_elf_cals int

	for _, cal := range cals {
		if cal == "" {
			if current_elf_cals > max_elf_cals {
				max_elf_cals = current_elf_cals
			}
			current_elf_cals = 0
		} else {
			cal_int, err := strconv.Atoi(cal)
			if err != nil {
				panic("bad input")
			}
			current_elf_cals += cal_int
		}
	}
	fmt.Println(max_elf_cals)
}

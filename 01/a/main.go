package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	file, err := os.Open("../input.txt")
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

	var maxElfCals, currentElfCals int

	for _, cal := range cals {
		if cal == "" {
			if currentElfCals > maxElfCals {
				maxElfCals = currentElfCals
			}
			currentElfCals = 0
		} else {
			calInt, err := strconv.Atoi(cal)
			if err != nil {
				panic("bad input")
			}
			currentElfCals += calInt
		}
	}
	fmt.Println(maxElfCals)
}

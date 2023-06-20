package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
)

func main() {
	file, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatal("couldn't open file")
	}
	defer file.Close()

	var cals []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		cals = append(cals, scanner.Text())
	}
	if scanner.Err() != nil {
		log.Fatal("couldn't read file")
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
				log.Fatal("bad input")
			}
			currentElfCals += calInt
		}
	}
	fmt.Println(maxElfCals)
}

package main

import (
	"bufio"
	"errors"
	"fmt"
	"log"
	"os"
)

// TODO: make the other literals globals
func priority(c byte) (byte, error) {
	if c >= byte('a') && c <= byte('z') {
		return c - byte('a') + 1, nil
	} else if c >= byte('A') && c <= byte('Z') {
		return c - 2 * byte('A') + byte('Z') + 2, nil
	} else {
		return 0, errors.New("bad input")
	}
}


type void struct{}
var sentinel void


func main() {
	file, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatal("couldn't open file")
	}
	defer file.Close()

	var rucksacks []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		rucksacks = append(rucksacks, scanner.Text())
	}
	if scanner.Err() != nil {
		log.Fatal("couldn't read file")
	}

	priorities := make([]byte, 0, len(rucksacks))
	var intersection byte

	for _, r := range rucksacks {
		c1 := make(map[byte]struct{})
		c2 := make(map[byte]struct{})  // TODO: any??

		for i := 0; i < len(r) / 2; i++ {
			c1[byte(r[i])] = sentinel
		}
		for i := len(r) / 2; i < len(r); i++ {
			c2[byte(r[i])] = sentinel
		}

		for k := range(c1) {
			if _, ok := c2[k]; ok {
				intersection = k
				break
			}
		}
		rPriority, err := priority(intersection)
		if err != nil {
		}
		priorities = append(priorities, rPriority)
	}

	answer := 0
	for _, p := range(priorities) {
		answer += int(p)
	}

	fmt.Println(answer)
}

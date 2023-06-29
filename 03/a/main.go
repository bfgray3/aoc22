package main

import (
	"bufio"
	"errors"
	"fmt"
	"log"
	"os"
)

var sentinel any

// TODO: make the other literals globals
func priority(c byte) (byte, error) {
	if c >= byte('a') && c <= byte('z') {
		return c - byte('a') + 1, nil
	} else if c >= byte('A') && c <= byte('Z') {
		return c - 2*byte('A') + byte('Z') + 2, nil
	} else {
		return 0, errors.New("bad input")
	}
}

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
		c1 := make(map[byte]any)
		c2 := make(map[byte]any)

		for i := 0; i < len(r)/2; i++ {
			c1[r[i]] = sentinel
		}
		for i := len(r) / 2; i < len(r); i++ {
			c2[r[i]] = sentinel
		}

		for k := range c1 {
			if _, ok := c2[k]; ok {
				intersection = k
				break
			}
		}
		rPriority, err := priority(intersection)
		if err != nil {
			log.Fatal("error finding priority")
		}
		priorities = append(priorities, rPriority)
	}

	var answer uint
	for _, p := range priorities {
		answer += uint(p)
	}

	fmt.Println(answer)
}

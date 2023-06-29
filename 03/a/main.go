package main

import (
	"bufio"
	"errors"
	"fmt"
	"log"
	"os"
)

var sentinel any

const lowercaseA byte = byte('a')
const lowercaseZ byte = byte('z')
const uppercaseA byte = byte('A')
const uppercaseZ byte = byte('Z')

func priority(c byte) (byte, error) {
	if c >= lowercaseA && c <= lowercaseZ {
		return c - lowercaseA + 1, nil
	} else if c >= uppercaseA && c <= uppercaseZ {
		return c - 2*uppercaseA + uppercaseZ + 2, nil
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
		halfSize := len(r) / 2

		c1 := make(map[byte]any, halfSize)
		c2 := make(map[byte]any, halfSize)

		for i := 0; i < halfSize; i++ {
			c1[r[i]] = sentinel
		}
		for i := halfSize; i < len(r); i++ {
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

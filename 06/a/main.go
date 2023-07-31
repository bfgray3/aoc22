package main

import (
	"fmt"
	"log"
	"os"
)

var sentinel any

const markerLength = 4

func main() {
	data, err := os.ReadFile(os.Args[1])
	if err != nil {
		log.Fatal("couldn't read file")
	}

	index := markerLength

	for ; ; index++ {
		s := make(map[byte]any, index-markerLength)
		for i := index - markerLength; i < index; i++ {
			// TODO: bail early here if it's already in there???
			s[data[i]] = sentinel
		}
		if len(s) == markerLength {
			break
		}
	}

	fmt.Println(index)
}

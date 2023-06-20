package main

import (
	"bufio"
	"fmt"
	"os"
	"log"
	"strconv"
	"strings"
)

type rnge struct {
	start, end int
}

type rngePair struct {
	a, b rnge
}

func parseRange(s string) rnge {
	splitS := strings.Split(s, "-")
	start, _ := strconv.Atoi(splitS[0])
	end, _ := strconv.Atoi(splitS[1])
	return rnge{start, end}
}
func parseRanges(s string) rngePair {
	splitS := strings.Split(s, ",")
	return rngePair{parseRange(splitS[0]), parseRange(splitS[1])}
}

func rangeContained(rp rngePair) bool {
	return rp.a.start >= rp.b.start && rp.a.end <= rp.b.end || rp.b.start >= rp.a.start && rp.b.end <= rp.a.end
}

func main() {
	file, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatal("couldn't open file")
	}
	defer file.Close()

	var data []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		data = append(data, scanner.Text())
	}
	if scanner.Err() != nil {
		log.Fatal("couldn't read file")
	}

	var overlapCount uint

	for _, row := range data {
		if rangeContained(parseRanges(row)) {
			overlapCount++
		}
	}
	fmt.Println(overlapCount)
}

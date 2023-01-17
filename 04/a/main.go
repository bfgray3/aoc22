package main

import (
	"bufio"
	"fmt"
	"os"
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
	file, err := os.Open("../input.txt")
	if err != nil {
		panic("couldn't open file")
	}
	defer file.Close()

	var data []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		data = append(data, scanner.Text())
	}
	if scanner.Err() != nil {
		panic("couldn't read file")
	}

	var overlapCount uint

	for _, row := range data {
		if rangeContained(parseRanges(row)) {
			overlapCount++
		}
	}
	fmt.Println(overlapCount)
}

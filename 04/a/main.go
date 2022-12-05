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

type rnge_pair struct {
	a, b rnge
}

func parse_rnge(s string) rnge {
	split_s := strings.Split(s, "-")
	start, _ := strconv.Atoi(split_s[0])
	end, _ := strconv.Atoi(split_s[1])
	return rnge{start, end}
}
func parse_ranges(s string) rnge_pair {
	split_s := strings.Split(s, ",")
	return rnge_pair{parse_rnge(split_s[0]), parse_rnge(split_s[1])}
}

func range_contained(rp rnge_pair) bool {
	return rp.a.start >= rp.b.start && rp.a.end <= rp.b.end || rp.b.start >= rp.a.start && rp.b.end <= rp.a.end
}

func main() {
	file, err := os.Open("input.txt")
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

	var overlap_count uint

	for _, row := range data {
		if range_contained(parse_ranges(row)) {
			overlap_count++
		}
	}
	fmt.Println(overlap_count)
}

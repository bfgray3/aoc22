package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
)

var winning = map[byte]byte{
	'R': 'S',
	'P': 'R',
	'S': 'P',
}

var scoreTable = map[byte]uint64{
	'R': 1,
	'P': 2,
	'S': 3,
}

const (
	WIN  uint64 = 6
	TIE  uint64 = 3
	LOSS uint64 = 0
)

func parseOpponentMove(c byte) (byte, error) {
	switch c {
	case 'A':
		return 'R', nil
	case 'B':
		return 'P', nil
	case 'C':
		return 'S', nil
	}
	return 0, fmt.Errorf("unsupported opponent move %c", c)
}

func parseMyMove(c byte) (byte, error) {
	switch c {
	case 'X':
		return 'R', nil
	case 'Y':
		return 'P', nil
	case 'Z':
		return 'S', nil
	}
	return 0, fmt.Errorf("unsupported own move %c", c)
}

func main() {
	var score uint64

	file, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatal("couldn't open file")
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		rawText := scanner.Text()

		myMove, myErr := parseMyMove(rawText[len(rawText)-1])
		opponentMove, opponentErr := parseOpponentMove(rawText[0])

		if myErr != nil || opponentErr != nil {
			log.Fatal("Error parsing move")
		}

		score += scoreTable[myMove]

		if myMove == opponentMove {
			score += TIE
		} else if winning[myMove] == opponentMove {
			score += WIN
		} else {
			score += LOSS
		}
	}

	if scanner.Err() != nil {
		log.Fatal("couldn't read file")
	}

	fmt.Println(score)
}

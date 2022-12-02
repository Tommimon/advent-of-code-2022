//
// Day 2 solution of Advent Of Code 2022 by Riccardo Negri
// First part solution: 11906
// Second part solution: 11186
//

package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
)

func main() {
	// open file
	f, err := os.Open("input.txt")
	if err != nil {
		log.Fatal(err)
	}

	// close the file at the end of the program
	defer func(f *os.File) {
		err := f.Close()
		if err != nil {
			log.Fatal(err)
		}
	}(f)

	// read the file line by line using scanner
	score1 := 0
	score2 := 0
	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		line := scanner.Text()
		line = strings.Replace(line, "\n", "", -1)
		shapes := strings.Split(line, " ")

		// part 1: A and X are rock, B and Y are paper, C and Z are scissors
		shapeScore := map[string]int{
			"X": 1,
			"Y": 2,
			"Z": 3,
		}
		// winning combinations
		if (shapes[0] == "A") && (shapes[1] == "Y") || (shapes[0] == "B") && (shapes[1] == "Z") || (shapes[0] == "C") && (shapes[1] == "X") {
			score1 += 6
		}
		// tie combinations
		if (shapes[0] == "A") && (shapes[1] == "X") || (shapes[0] == "B") && (shapes[1] == "Y") || (shapes[0] == "C") && (shapes[1] == "Z") {
			score1 += 3
		}
		// shape score1
		score1 += shapeScore[shapes[1]]

		// part 2: X you loose, Y you draw, Z you win
		values := map[string]int{
			"A": 0,
			"B": 1,
			"C": 2,
		}
		if shapes[1] == "Y" { // draw
			score2 += 3
			score2 += values[shapes[0]] + 1
		} else if shapes[1] == "Z" { // win
			score2 += 6
			score2 += (values[shapes[0]]+1)%3 + 1
		} else { // lose
			tmp := values[shapes[0]] - 1
			if tmp < 0 {
				tmp = 2
			}
			score2 += tmp%3 + 1
		}
	}

	err = scanner.Err()
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(score1)
	fmt.Println(score2)
}

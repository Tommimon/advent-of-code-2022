//
// Day 3 solution of Advent Of Code 2022 by Riccardo Negri
// First part solution: 8401
// Second part solution: 2641
//

package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
)

func getPriority(value int) int {
	// 65 is A, 90 is Z, 97 is a
	if value >= 65 && value <= 90 {
		return value - 65 + 27
	} else {
		return value - 97 + 1
	}
}

func main() {
	score1 := 0
	score2 := 0
	lineNumber := 0
	var group [3]string

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
	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		line := strings.Replace(scanner.Text(), "\n", "", -1)

		// part 1
		for _, value := range line[:len(line)/2] {
			fmt.Println(string(value))
			if strings.Contains(line[len(line)/2:], string(value)) {
				score1 += getPriority(int(value))
				break
			}
		}

		// part 2
		group[lineNumber%3] = line
		if lineNumber%3 == 2 {
			for _, value := range group[0] {
				if strings.Contains(group[1], string(value)) && strings.Contains(group[2], string(value)) {
					score2 += getPriority(int(value))
					break
				}
			}
		}

		lineNumber += 1
	}

	err = scanner.Err()
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(score1)
	fmt.Println(score2)
}

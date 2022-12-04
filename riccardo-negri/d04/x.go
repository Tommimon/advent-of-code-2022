//
// Day 4 solution of Advent Of Code 2022 by Riccardo Negri
// First part solution: 453
// Second part solution: 919
//

package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func main() {
	score1 := 0
	score2 := 0
	var numbers [4]int

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
		sections := strings.Split(strings.ReplaceAll(line, ",", "-"), "-")
		for ind, value := range sections {
			numbers[ind], _ = strconv.Atoi(value)
		}

		// part 1
		ab := numbers[1] - numbers[0]
		cd := numbers[3] - numbers[2]
		if ab > cd {
			if numbers[2] >= numbers[0] && numbers[3] <= numbers[1] {
				score1 += 1
			}
		} else {
			if numbers[0] >= numbers[2] && numbers[1] <= numbers[3] {
				score1 += 1
			}
		}

		// part 2
		i := 0
		for i < 4 {
			j := i / 2 * 2
			if 0 >= (numbers[i]-numbers[(j+2)%4])*(numbers[i]-numbers[(j+3)%4]) {
				score2 += 1
				break
			}
			i += 1
		}
	}

	err = scanner.Err()
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(score1)
	fmt.Println(score2)
}

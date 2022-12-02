//
// Day 1 solution of Advent Of Code 2022 by Riccardo Negri
// First part solution: 73211
// Second part solution: 213958
//

package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"sort"
	"strconv"
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
	scanner := bufio.NewScanner(f)
	temp := 0
	var sums []int
	for scanner.Scan() {
		line := scanner.Text()
		line = strings.Replace(line, "\n", "", -1)
		if line == "" {
			sums = append(sums, temp)
			temp = 0
		} else {
			num, err := strconv.ParseInt(line, 10, 64)
			if err != nil {
				log.Fatal(err)
			}
			temp += int(num)
		}
	}

	err = scanner.Err()
	if err != nil {
		log.Fatal(err)
	}

	sort.Ints(sums)

	// part 1
	fmt.Println(sums[len(sums)-1])

	// part 2
	sum := 0
	i := 0
	for i < 3 {
		sum += sums[len(sums)-1-i]
		i += 1
	}
	fmt.Println(sum)
}

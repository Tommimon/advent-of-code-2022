//
// Day 6 solution of Advent Of Code 2022 by Riccardo Negri
// First part solution: 1109
// Second part solution: 3965
//

use std::collections::{HashSet};
use std::fs::File;
use std::io::{BufRead, BufReader};

fn main() {
    let filename = "input.txt";
    let mut part1= true;

    // Open the file in read-only mode (ignoring errors).
    let file = File::open(filename).unwrap();
    let reader = BufReader::new(file);


    // Read the file line by line using the lines() iterator from std::io::BufRead.
    let lines = reader.lines().enumerate();
    for (_, line) in  lines {
        let line = line.unwrap(); // Ignore errors.

        for i in 3..line.len() {
            let mut counts1 : HashSet<char> = HashSet::new();
            let mut counts2 : HashSet<char> = HashSet::new();

            // part 1
            for j in 0..4 {
                let c =  line.as_bytes()[i-j] as char;
                counts1.insert(c,);
            }
            if counts1.len() == 4 && part1 {
                part1 = false;
                println!("{}", i + 1);
            }

            // part 12
            for j in 0..14 {
                if j <= i {
                    let c =  line.as_bytes()[i-j] as char;
                    counts2.insert(c,);
                }
            }
            if counts2.len() == 14 {
                println!("{}", i + 1);
                break
            }


        }
    }



}

//
// Day 5 solution of Advent Of Code 2022 by Riccardo Negri
// First part solution: SVFDLGLWV
// Second part solution: DCVTCVPCL
//

use std::fs::File;
use std::io::{BufRead, BufReader};

fn print_stacks(stacks: Vec<Vec<String>>) {
    for s in stacks.clone() {
        let mut line: String = "-->".to_owned();
        for e in s {
            line.push_str(&e)
        }
        println!("{}", line)
    }
    println!()
}

fn main() {
    let filename = "input.txt";
    let stack_num = 9;
    let mut stacks1: Vec<Vec<String>> = std::iter::repeat(vec![]).take(stack_num).collect::<Vec<Vec<String>>>();
    let mut stacks2: Vec<Vec<String>> = std::iter::repeat(vec![]).take(stack_num).collect::<Vec<Vec<String>>>();
    let mut reading_phase = 0; // 0 is the stacks, 1 is between, 2 is the instructions

    // Open the file in read-only mode (ignoring errors).
    let file = File::open(filename).unwrap();
    let reader = BufReader::new(file);


    // Read the file line by line using the lines() iterator from std::io::BufRead.
    let lines = reader.lines().enumerate();
    for (_, line) in  lines {
        let line = line.unwrap(); // Ignore errors.
        match reading_phase {
            0 => {
                if line.contains("[") {
                    for i in (1..(stack_num *4+1)).step_by(4) {
                        if i < line.len() {
                            let cc: char = line.as_bytes()[i] as char;
                            if cc != ' ' {
                                stacks1[(i-1)/4].push(cc.to_string())
                            }
                        }

                    }
                } else {
                    // reverse the stacks
                    for i in 0..stack_num {
                        stacks1[i].reverse();
                    }
                    stacks2 = stacks1.clone();
                    reading_phase = 1;
                }
            }
            1 => {
                // skip one line
                reading_phase = 2
            }
            2 => {
                if line.contains("move") {
                    let s : Vec<String> = line.split_whitespace().map(|x|x.to_string()).collect();
                    let amount = s[1].trim_end().parse().expect("Wrong number format!");
                    let src : usize = s[3].trim_end().parse().expect("Wrong number format!");
                    let dst : usize = s[5].trim_end().parse().expect("Wrong number format!");

                    // part 1
                    for _ in 0..amount {
                        let src_stack : & mut Vec<String> = &mut stacks1[src - 1];
                        let tmp = src_stack.pop().expect("Vector is empty!");
                        let dst_stack : & mut Vec<String> = &mut stacks1[dst - 1];
                        dst_stack.push(tmp)
                    }
                    //print_stacks(stacks1.clone())

                    // part 2
                    let mut v : Vec<String> = Vec::new();
                    let src_stack : & mut Vec<String> = &mut stacks2[src - 1];
                    for _ in 0..amount {
                        let tmp = src_stack.pop().expect("Vector is empty!");
                        v.push(tmp)
                    }
                    let dst_stack : & mut Vec<String> = &mut stacks2[dst - 1];
                    for _ in 0..amount {
                        let tmp = v.pop().expect("Vector is empty!");
                        dst_stack.push(tmp)
                    }
                    //print_stacks(stacks2.clone())
                } else {
                    reading_phase = 3
                }
            }
            _ => {}
        }
    }

    for s in stacks1 {
        print!("{}", s[s.len()-1]);
    }
    println!();

    for s in stacks2 {
        print!("{}", s[s.len()-1]);
    }
    println!()
}
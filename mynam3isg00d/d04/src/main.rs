//This sucks, i found a better solution on reddit using scan_fmt!()

use std::fs;

fn main() {
    let input = fs::read_to_string("input.txt").expect("ERROR in opening file");

    let sol1 = input.split("\r\n").filter(|x| -> bool {
        let elf1 = x.split(",").collect::<Vec<&str>>()[0].split("-").collect::<Vec<&str>>();
        let elf2 = x.split(",").collect::<Vec<&str>>()[1].split("-").collect::<Vec<&str>>();

        let r11 = elf1[0].parse::<i32>().unwrap();
        let r12 = elf1[1].parse::<i32>().unwrap();
        let r21 = elf2[0].parse::<i32>().unwrap();
        let r22 = elf2[1].parse::<i32>().unwrap();

        let a = r11 >= r21 && r12 <= r22;
        let b = r21 >= r11 && r22 <= r12;

        return a || b;
    }).count();

    let sol2 = input.split("\r\n").filter(|x| -> bool {
        let elf1 = x.split(",").collect::<Vec<&str>>()[0].split("-").collect::<Vec<&str>>();
        let elf2 = x.split(",").collect::<Vec<&str>>()[1].split("-").collect::<Vec<&str>>();

        let r11 = elf1[0].parse::<i32>().unwrap();
        let r12 = elf1[1].parse::<i32>().unwrap();
        let r21 = elf2[0].parse::<i32>().unwrap();
        let r22 = elf2[1].parse::<i32>().unwrap();

        let a = (r21 >= r11) && (r12 - r11 >= r21 - r11);
        let b = (r11 >= r21) && (r22 - r21 >= r11 - r21);

        return a || b;
    }).count();

    println!("Part 1: {sol1}");
    println!("Part 2: {sol2}");
}

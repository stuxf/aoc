use std::collections::HashMap;
use std::fs::read_to_string;

fn main() {
    let contents = read_to_string("input").unwrap();

    let mut id_ctr = HashMap::new();
    let mut left: Vec<i32> = Vec::new();
    let mut right: Vec<i32> = Vec::new();

    for line in contents.lines() {
        let ids: Vec<i32> = line
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<i32>>();
        left.push(ids[0]);
        right.push(ids[1]);
        *id_ctr.entry(ids[1]).or_insert(0) += 1;
    }

    left.sort_unstable();
    right.sort_unstable();
    
    let diff: i32 = left.iter()
        .zip(right.iter())
        .map(|(l, r)| (l - r).abs())
        .sum();
    println!("{}", diff);
    
    let similarity: i32 = left.iter()
        .map(|&id| id * id_ctr.get(&id).unwrap_or(&0))
        .sum();
    println!("{}", similarity);
}

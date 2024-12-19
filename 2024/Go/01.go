package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

func abs(x int) int {
	if x > 0 {
		return x
	}
	return -x
}

func main() {
	f, _ := os.Open("input")
	scanner := bufio.NewScanner(f)
	defer f.Close()

	var left, right []int

	idCount := make(map[int]int)

	for scanner.Scan() {
		var l_id, r_id int
		fmt.Sscanf(scanner.Text(), "%d %d", &l_id, &r_id)
		left = append(left, l_id)
		right = append(right, r_id)
		idCount[r_id]++
	}

	sort.Ints(left)
	sort.Ints(right)

	diff := 0
	for i := range left {
		diff += abs(left[i] - right[i])
	}

	fmt.Println(diff)

	similarity := 0
	for _, value := range left {
		similarity += idCount[value] * value
	}

	fmt.Println(similarity)
}

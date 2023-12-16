package main

import (
	"fmt"
	"sort"
)

func main() {
	strs := []string{"fv", "ab", "ee", "ti", "q", "ta"}

	//sort.Ints(nums)
	sort.Slice(strs, func(i, j int) bool {
		return strs[i] < strs[j]
	})
	fmt.Println(strs)
}

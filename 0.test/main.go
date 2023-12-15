package main

import (
	"fmt"
)

func dfs(nums []int, target, index, sum int, ret *int) {

	if index == len(nums) {
		if sum == target {
			*ret++
		}

		return
	}

	dfs(nums, target, index+1, sum+nums[index], ret)
	dfs(nums, target, index+1, sum-nums[index], ret)
}

func findTargetSumWays(nums []int, target int) int {
	ret := 0
	dfs(nums, target, 0, 0, &ret)
	return ret
}

func main() {
	nums := []int{1}
	target := 1

	ret := findTargetSumWays(nums, target)
	fmt.Println(ret)
}

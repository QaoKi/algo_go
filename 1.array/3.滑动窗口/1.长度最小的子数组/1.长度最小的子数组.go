package main

/*
	题目： leetcode 209
		给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的 连续 子数组，并返回其长度。
		如果不存在符合条件的子数组，返回 0。

		示例1：
		输入：s = 7, nums = [2,3,1,2,4,3]
		输出：2
		解释：子数组 [4,3] 是该条件下的长度最小的子数组。
*/

/*
	这题的关键在于，需要把所有的子数组都找出来，再找出满足条件的子数组，然后取长度最小的
*/

/*
	暴力法，两层循环
		把每一个元素，作为子数组的首元素，子数组不断向后扩张，当子数组满足条件时，求子数组的长度
		取所有满足条件的子数组的长度最小值
	时间复杂度：O(n^2)
*/

func min(a, b int) int {
	if a > b {
		return b
	}
	return a
}

func baoli(target int, nums []int) int {
	ans := len(nums) + 1
	//第一层循环，每一个元素，作为子数组的首元素
	for i := 0; i < len(nums); i++ {
		sum := 0
		//第二层循环，子数组不断向后扩张，当满足条件时，计算长度
		for j := i; j < len(nums); j++ {
			sum += nums[j]
			if sum >= target {
				ans = min(ans, j-i+1)
				//满足了就别再向后扩张了，再向后扩张肯定满足条件，并且长度会更长
				break
			}
		}
	}

	if ans == len(nums)+1 {
		ans = 0
	}
	return ans
}

/*
	滑动窗口：采用两个指针 left 和 right ，两个指针之间组成一个滑动窗口（两个指针所指向的元素，也包含在窗口中）。
		窗口的值就是窗口中所有元素累加的和
		当窗口的值小于 target，right 向后移动，扩大滑动窗口（值不够，需要扩充）
		当窗口的值大于等于 target，此时符合条件，
			记录此时滑动窗口的长度，然后不断的让 left 向后移动（不断的尝试缩小窗口，看看是否还能满足条件）。

	时间复杂度：O(n)
*/

func minSubArrayLen(target int, nums []int) int {
	//sum 是当前滑动窗口的值，res先赋值最大的长度
	left, right, sum, res := 0, 0, 0, len(nums)+1

	for ; right < len(nums); right++ {
		sum += nums[right]
		//当窗口满足条件了，让 left 右移，不断的尝试缩小窗口。否则的话， right 直接向后移扩大窗口的值
		for sum >= target {
			//记录滑动窗口最小的长度
			res = min(res, right-left+1)
			//缩小滑动窗口，让 left 向后移
			sum -= nums[left]
			left++
		}
	}

	if res == len(nums)+1 {
		res = 0
	}
	return res
}

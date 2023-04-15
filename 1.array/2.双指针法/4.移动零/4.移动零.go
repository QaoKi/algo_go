package main

/*
	题目： leetcode 283
		给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

		说明：
			必须在原数组上操作，不能拷贝额外的数组。
			尽量减少操作次数。

		示例1：
			输入: [0,1,0,3,12]
			输出: [1,3,12,0,0]
*/

/*
	这道题的解题，和 27题 移除元素 思路类似。
	不过需要注意的是，在 移除元素 题中，元素可以直接被覆盖，但是在本题中不能覆盖，需要交换
	1，使用两个指针 left 和 curr，刚开始都指向下标 0
	2，如果 nums[curr] == 0，让 curr++
	3，如果 nums[curr] != 0，让 nums[left] 和 nums[curr] 交换，并让 left++, curr++
	left 指向的是要被交换的 0，如果第一个数不是0，就让它自己和自己交换，然后 left 和 curr 同时向后移动
	或者可以让 left 初始时指向 -1，当 curr 遇到 != 0 的元素，让 left 的下一个元素和 curr 进行交换
*/

func moveZeroes(nums []int) {
	left, right := 0, 0
	for ; right < len(nums); right++ {
		if nums[right] != 0 {
			nums[left], nums[right] = nums[right], nums[left]
			left++
		}
	}
}

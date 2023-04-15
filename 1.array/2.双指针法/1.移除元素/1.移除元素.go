package main

/*
	题目： leetcode 27
		给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
		不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。
		元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。

		示例1：
		输入：nums = [3,2,2,3], val = 3
		输出：2, nums = [2,2]
*/

/*
	首先要明确题意，将值等于 val 的元素移除，其实就是让后面的元素朝前移动将其覆盖就行。

	双指针法：
		使用两个指针 left 和 right
		left 指向新数组最后一个元素的下一个元素，right 用来遍历检查 nums 中每个元素
		实际上类似于快排中的思路，left指向左边界的下一个元素，当出现合适的元素时，将该元素添加到左边界中
		在这题中，合适的元素就是值不等于 val 的元素

		刚开始 left 和 right 都指向 nums 下标为 0 的元素。
		用 right 指针遍历 nums 的每个元素，
		如果 nums[right] 等于 val，跳过
		如果 nums[right] 不等于 val，那么将该元素添加到新数组的尾部，而新数组的尾部，由 left 标记着，
			所以直接将 nums[right] 复制到 nums[left]，新数组增大了，left 后移，继续指向新数组最后一个元素的下一个元素
		直到 right 到达数组的末尾，新数组的新长度为 left
*/

func removeElement(nums []int, val int) int {
	length := len(nums)
	left, right := 0, 0

	for ; right < length; right++ {
		if nums[right] != val {
			nums[left] = nums[right]
			left++
		}
	}

	return left
}

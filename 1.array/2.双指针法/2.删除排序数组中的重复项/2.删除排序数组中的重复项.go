package main

/*
	题目： leetcode 26
		给定一个【升序排列】数组，你需要在 原地 删除重复出现的元素，使得每个元素只出现一次，返回移除后数组的新长度。
		不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

		示例1：
		输入：nums = [1,1,2]
		输出：2, 并且原数组 nums 的前两个元素被修改为 1, 2。
*/

/*
	双指针法：数组已经是有序的
		使用两个指针 left 和 right
		left 指向新数组的最后一个元素，right 用来遍历检查 nums 中每个元素

		刚开始 left 指向下标为0的元素，right 指向下标为 0 或者下标为 1 的元素都可以，
			如果 nums[left] 和 nums[right] 相等，说明 nums[right] 是无效元素，跳过
			如果 nums[left] 和 nums[right] 不相等，说明 nums[right] 是有效元素，
				将 nums[right] 插入到新数组的尾部，因为此时 left 指向新数组的最后一个元素，
				所以要将 nums[right] 插入到 nums[left] 的下一个元素，
				因为新数组的元素增加了，所以 left 后移
		直到 right 到达数组的末尾，该数组的新长度为 left + 1

		因为返回值是 left+1，如果给定的 nums 为空的话，会出错，返回在函数开头做一下 basecase
*/

func removeDuplicates(nums []int) int {
	length := len(nums)
	if length == 0 || length == 1 {
		return length
	}

	left, right := 0, 0
	for ; right < length; right++ {
		if nums[right] != nums[left] {
			nums[left+1] = nums[right]
			left++
		}
	}

	return left + 1
}

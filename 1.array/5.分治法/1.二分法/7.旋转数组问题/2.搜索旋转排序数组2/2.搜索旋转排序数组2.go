package main

/*
	leetcode 81
	题目：
		假设按照升序排序的数组在预先未知的某个点上进行了旋转
		例如，数组 [0,0,1,2,2,5,6] 可能变为 [2,5,6,0,0,1,2]
		搜索一个给定的目标值，判断给定的目标值是否存在于数组中。若存在返回 true，否则返回 false。

		和 1.搜索旋转排序数组 的区别是数组中可以包含重复的元素
*/

/*
	数组中包含了重复的元素，依然采用之前的方法，用 mid将数组分为两部分，
		当 nums[left] < nums[mid] 时，依然可以判定前半部分是有序的，
		但是当 nums[left] == nums[mid]时无法判断，
			比如 nums = [1 1 0 1 1 1 1 1]，left = 0, mid = 3,
				前半部分为 [1 1 0 1]，nums[left] 和 nums[mid] 都等于1，但是前半部分是无序的。
		所以当 nums[left] == nums[mid] 时，我们选择left++，重新二分。可以看到，后移以后，nums[left]还是等于nums[mid]，
			再后移，此时找到了target，但其实这样最坏情况下相等于顺序遍历进行比较了，时间复杂度变成 O(n)
		其他步骤和 1.搜索旋转排序数组 相同
*/

func search(nums []int, target int) bool {
	if len(nums) == 0 {
		return false
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if nums[mid] == target {
			return true
		}

		//无法判定前半部分是否是有序，跳过这个元素
		if nums[left] == nums[mid] {
			left++
			continue
		}

		//前半部分有序
		if nums[left] < nums[mid] {
			// target 是否在前半部分
			if nums[left] <= target && target < nums[mid] {
				//在前半部分，缩小范围
				right = mid - 1
			} else {
				//不在前半部分，继续去拆分后半部分
				left = mid + 1
			}

		} else {
			// 前半部分是无序的，那么后半部分是有序的，判断 target 是否在后半部分中
			if nums[mid] < target && target <= nums[right] {
				//在后半部分，缩小范围
				left = mid + 1
			} else {
				//不在后半部分，继续去拆分前半部分
				right = mid - 1
			}
		}
	}
	return false
}

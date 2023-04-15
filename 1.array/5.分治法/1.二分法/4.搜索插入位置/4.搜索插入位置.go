package main

/*
	leetcode 35
	给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
	你可以假设数组中无重复元素。
*/

/*
	这道题就是找数组中第一个大于等于给定元素的位置
*/

//查找第一个大于等于给定值的元素，返回下标
func searchInsert(nums []int, target int) int {
	if len(nums) == 0 {
		return 0
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if nums[mid] >= target {
			if mid == 0 || nums[mid-1] < target {
				return mid
			} else {
				right = mid - 1
			}
		} else {
			left = mid + 1
		}
	}

	//没找到大于等于 target的，插入到数组的最后
	return len(nums)
}

/*
	这道题用基本的二分查找也能够解决，
		1，如果目标值在数组中，没什么好说的，可以找到，直接返回
		2，如果目标值不在数组中，思考二分查找的过程，最终 left的值，就是该目标值按顺序插入的位置
*/

func searchInsert1(nums []int, target int) int {
	if len(nums) == 0 {
		return 0
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if nums[mid] == target {
			return mid
		} else if nums[mid] > target {
			right = mid - 1
		} else {
			left = mid + 1
		}

	}
	return left
}

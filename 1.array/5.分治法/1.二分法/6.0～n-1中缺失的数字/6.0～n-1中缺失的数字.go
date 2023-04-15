package main

/*
	剑指 offer 53 ②
	一个长度为n-1的递增排序数组中的所有数字都是唯一的，并且每个数字都在范围0～n-1之内。
	在范围0～n-1内的n个数字中有且只有一个数字不在该数组中，请找出这个数字

	示例 1:
		输入: [0,1,3]
		输出: 2

	示例 2:
		输入: [0,1,2,3,4,5,6,7,9]
		输出: 8
*/

/*
	所要找的，是第一个值大于其下标的数字，比如 [0,1,2,3,4,6,7,8]，数字4的下标为4，
	但是数字6的下标为5,并且之后的每一个数字，都大于其下标，而我们要找的就是第一个这样的数字6，其下标，就是缺失的数字5

	这道题，其实和 查找有序数组中第一个等于给定值的下标，写代码的思路是一样的，让left和right不断的靠近要找的值
*/

func missingNumber(nums []int) int {
	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if mid == nums[mid] {
			left = mid + 1
		} else {
			//判断是否是第一个
			if mid == 0 || nums[mid-1] == mid-1 {
				return mid
			} else {
				right = mid - 1
			}

		}
	}

	//当数组不缺数字的时候，返回数组的下一个插入位置
	return len(nums)
}

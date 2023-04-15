package main

/*
	leetcode 33
	题目：
		假设按照升序排序的数组在预先未知的某个点上进行了旋转
		例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2]
		搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回-1。

		假设数组中不存在重复的元素。时间复杂度要求O(logn)。
*/

/*
	时间复杂度为 O(logn)的方法
	int mid = left + (right - left) / 2;
	求出一个下标的中间值 mid，将数组分成两部分，[left, mid] 和 [mid + 1, right]
	这两部分肯定有一部分是有序的，另一部分可能是有序的，也可能仍然是一个循环有序数据
	比如 [4,5,6,7,8,9,0,1,2]，mid = 7,
	分成 [4,5,6,7,8] 和 [9,0,1,2]，前半部分是有序的，后半部分是仍是一个循环有序数组
	判断这两部分，哪部分是有序的，再判断 num 是否在有序的部分中，
	如果不在有序的部分，重复上面的步骤，继续拆分循环有序数组。
*/

func search(nums []int, target int) int {
	if len(nums) == 0 {
		return -1
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if nums[mid] == target {
			return mid
		}

		/*
			判断前半部分是否有序，虽然数组中没有重复的数字，但是这里依然要用 <= 来判断，
				比如nums = [2, 1]，target = 1，此时 mid = (0+1)/2 = 0，此时前半部分只有一个数字 [2]，
				如果用 if (nums[left] < nums[mid]) 去判断的话，会认为前半部分为无序的，
				但其实这种情况下，前半部分是有序的
				所以判断前半部分是否有序的时候，用 if(nums[left] <= nums[mid])，
		*/
		if nums[left] <= nums[mid] {
			// 前半部分是有序的，判断 target 是否在前半部分中
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

	return -1
}

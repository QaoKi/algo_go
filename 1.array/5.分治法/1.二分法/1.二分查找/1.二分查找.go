package main

/*
	leetcode 704
	题目：
		给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target，
		写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。

	二分查找的条件：
		1，必须是有序的
		2，能够通过索引访问，所以一般都是数组，所以需要连续的内存。如果是链表这种，复杂度会增高
		3，数据量太少，不如直接遍历找。而数据量太大，因为数据要用连续的内存存储，对空间消耗太大

	时间复杂度：O(logn)
*/

func search(nums []int, target int) int {
	if len(nums) == 0 {
		return -1
	}

	left, right := 0, len(nums)-1
	for left <= right {
		/*
			小技巧，防止溢出：mid = L + (R-L)/2，
			a/2 == a >> 1  a除以2，等于a右移一位，所以  mid = L + (R-L) >> 1，位运算比算数运算快很多
			但是，(R-L) >> 1 需要单独算，如果放到一起，运行会出错
				int temp = (R-L) >> 1;
				int mid  = L + temp;
		*/

		mid := left + (right-left)/2
		if nums[mid] == target {
			return mid
		} else if nums[mid] > target {
			right = mid - 1 //注意 left 和 right 值更新的边界，不然可能会和快排一样出现死循环
		} else {
			left = mid + 1
		}

	}
	return -1
}

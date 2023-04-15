package main

/*
	leetcode 153
	题目：
		假设按照升序排序的数组在预先未知的某个点上进行了旋转，也可能没旋转
		例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2]
		请找出其中最小的元素。

		数组中不存在重复的元素。
*/

/*
	数组中不存在重复的元素，那么，当元素位于 [left, right] 区间内。
	如果 nums[left] <= nums[right]，说明 [left, right] 区间是没被翻转的，则 nums[left] 就是最小值，直接返回。
	如果 [left, right] 区间发生了翻转，取一个中间值 nums[mid]，
		如果 nums[left] <= nums[mid]，说明区间 [left,mid] 连续递增，
			则最小元素一定不在这个区间里，可以直接排除。因此，令 left = mid+1，在 [mid+1,right] 继续查找
				（因为数组已经发生了翻转，这个连续递增的区间，肯定是原来数组后面的元素翻转到了前面），
				比如 nums = [7 8 9 1 2]，此时nums[mid] = 9，nums[left] = 7，这个区间肯定不是要找的区间。
		否则，说明区间 [left,mid] 不连续，则最小元素一定在这个区间里。因此，令 right = mid，在 [left,mid] 继续查找
			注意 right 更新时被设为 mid 而不是 mid-1，因为 mid 无法被排除是否是要找的元素。

*/
func findMin(nums []int) int {
	left, right := 0, len(nums)-1
	for left <= right {
		//元素在[left, right]区间内，如果该区间是连续递增的，那么nums[left]就是最小的值，直接返回
		if nums[left] <= nums[right] {
			return nums[left]
		}

		//到这，说明区间[left, right]不连续，发生了翻转
		mid := left + (right-left)/2
		if nums[left] <= nums[mid] {
			//[left, mid] 是连续的区间，排除
			left = mid + 1
		} else {
			//[left, mid] 不连续，要找的元素就在这个区间内
			right = mid
		}
	}

	return -1
}

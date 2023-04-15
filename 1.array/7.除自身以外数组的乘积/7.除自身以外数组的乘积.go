package main

/*
	leetcode 238
	题目：
		给定一个大小为 n 的数组 nums，其中 n > 1，返回输出数组 output ，
		其中 output[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积。
		请不要使用除法，且在 O(n) 时间复杂度内完成此题。

		说明:
			题目数据保证数组之中任意元素的全部前缀元素和后缀（甚至是整个数组）的乘积都在 32 位整数范围内。
		进阶：
			在常数空间复杂度内完成这个题目，输出数组不被视为额外空间

		示例 1：
			输入: [1,2,3,4]
			输出: [24,12,8,6]
*/

/*
	这道题如果能用除法的话很简单，
		首先将所有的数都相乘，得到一个值 num，
		然后遍历数组，每次让 num 去除以 nums[i]，就得到了除 nums[i] 之外其余各元素的乘积。
	不过该题不让用除法，并且，如果 nums[i] 等于0，会出错。

	方法1，借助辅助数组
		除 nums[i] 之外其余各元素的乘积，等于 nums[i] 左边所有数的乘积，再乘上 nums[i] 右边所有数的乘积。
		借助两个数组 L 和 R，
			L[i] 保存的是 nums[i] 左边所有数的乘积，这个值不包含 nums[i] 本身，让 L[0] = 1。
			R[i] 保存的是 nums[i] 右边所有数的乘积，这个值不包含 nums[i] 本身，让后 R[n-1] = 1。
			公式为
				L[i] = L[i-1] * nums[i-1]
				R[i] = R[i+1] * nums[i+1]
			比如 nums = [2,1,3,4]
				那么 L[0] = 1, L[1] = 2, L[2] = 2*1 = 2, L[3] = 2*1*3 = 6。
					 R[3] = 1, R[2] = 4, R[1] = 4*3 = 12, R[0] = 4*3*1 = 12.
			最终 res[i] = L[i] * R[i]

	时间复杂度：O(n)
	空间复杂度：O(n)
*/
func productExceptSelf(nums []int) []int {
	res := make([]int, len(nums))
	if len(nums) == 0 {
		return res
	}
	L := make([]int, len(nums))
	R := make([]int, len(nums))
	L[0] = 1
	R[len(nums)-1] = 1

	//填充L
	for i := 1; i < len(nums); i++ {
		L[i] = L[i-1] * nums[i-1]
	}

	//填充R
	for i := len(nums) - 2; i >= 0; i-- {
		R[i] = R[i+1] * nums[i+1]
	}

	for i := 0; i < len(nums); i++ {
		res[i] = L[i] * R[i]
	}

	return res
}

/*
	方法2，常数空间复杂度
		因为题目中说了，输出数组 res 不算辅助数组，所以我们可以借助 res 来存储我们需要的数据。
		一共需要两组数，L 和 R，
			1，用方法1 中构造 L 的方式来构造 res 那么 res[i] 就是方法1 中的 L[i]，
			2，我们没有构造 R 数组，而右边的乘积，我们可以用一个变量 R 来不断的累积。
				初始时让 R = 1，从后往前遍历数组，让 res[i] = res[i] * R，
				并更新 R = R * nums[i]。这样最终的结果就保存到 res 中了。


	时间复杂度：O(n)
	空间复杂度：O(1)
*/
func productExceptSelf1(nums []int) []int {
	res := make([]int, len(nums))
	if len(nums) == 0 {
		return res
	}

	R := 1
	res[0] = 1
	//用填充L的方式填充res
	for i := 1; i < len(nums); i++ {
		res[i] = res[i-1] * nums[i-1]
	}

	//从后往前遍历
	for i := len(nums) - 1; i >= 0; i++ {
		res[i] = res[i] * R
		R = R * nums[i]
	}

	return res
}

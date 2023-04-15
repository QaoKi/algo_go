package main

/*
	leetcode 448
	题目：
		给你一个含 n 个整数的数组 nums ，其中 nums[i] 在区间 [1, n] 内。
		请你找出所有在 [1, n] 范围内但没有出现在 nums 中的数字，并以数组的形式返回结果。

		进阶：
			你能在不使用额外空间且时间复杂度为 O(n) 的情况下解决这个问题吗? 你可以假定返回的数组不算在额外空间内。

		示例 1：
			输入：nums = [4,3,2,7,8,2,3,1]
			输出：[5,6]
		示例 2：
			输入：nums = [1,1]
			输出：[2]
*/

/*
	长度为 n 的数组 nums ，每个元素的值在区间 [1, n] 内。

	方法1，
		用 map 将 nums 数组中元素的值都记录下来，然后从 1 遍历到 n，查看哪些数字不存在 map 中。

	时间复杂度：O(n)
	空间复杂度：O(n)
*/
func findDisappearedNumbers(nums []int) []int {
	res := []int{}
	n := len(nums)
	if n == 0 {
		return res
	}

	mapCount := map[int]bool{}
	for _, num := range nums {
		mapCount[num] = true
	}

	for i := 1; i <= n; i++ {
		if _, ok := mapCount[i]; !ok {
			res = append(res, i)
		}
	}

	return res
}

/*
	方法2，
		修改原数组的值，数组下标的范围是 [0...n-1]，数组中值的范围为 [1...n]。
		我们考虑用 nums 代替哈希，数组的值是 nums[i]，因为值的范围比下标范围大 1，所以我们
			修改下标为 nums[i]-1 的值，也就是修改 nums[nums[i] - 1] 的值。
		步骤：
			1，遍历 nums，每遇到一个数 x，就让 nums[x−1] 增加 n。
				由于 nums 中所有数均在 [1...n] 之间，增加以后，这些数必然大于 n，
			2，再遍历 nums，若 nums[i] 未大于 n，说明没有遇到过数字 i+1，这样就找到了缺失的数字 i+1。
		注意
			当我们在第一步遍历增加的时候 nums[i]的数可能已经被加过 n 了，因此需要对 n 取模来还原出它本来的值。

	时间复杂度：O(n)
	空间复杂度：O(1)
*/
func findDisappearedNumbers1(nums []int) []int {
	res := []int{}
	n := len(nums)
	if n == 0 {
		return res
	}

	for i := 0; i < n; i++ {
		//nums[i] 的值可能在前面的遍历中被增加过，需要对 n 取模来还原出它本来的值，不然会越界
		//这里需要减 1 以后再取模，不然 nums[i] % n - 1，x 可能会等于 -1
		x := (nums[i] - 1) % n
		nums[x] += n
	}

	for i := 0; i < n; i++ {
		if nums[i] <= n {
			//nums[i] 小于等于 n，说明数字 i+1 没有出现过
			res = append(res, i+1)
		}
	}

	return res
}

package main

/*
   题目：leetcode 416
       给定一个只包含正整数的非空数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
   示例：
       输入: [1, 5, 11, 5]
       输出: true
       数组可以分割成 [1, 5, 5] 和 [11].
*/

/*
   这道题换一种表述方法，可以转成 0-1背包问题：
       给定一个只包含正整数的非空数组 nums，判断是否可以从数组中选出一些数字，使得这些数字的和等于整个数组的元素和的一半。
           这道题与传统的「0-1背包问题」的区别在于，传统的「0-1背包问题」要求选取的物品的重量之和不能超过背包的总容量，
           这道题则要求选取的数字的和恰好等于整个数组的元素和的一半。也就是选取的物品的重量之和为背包总容量的一半。

   选出来的数字之和，是否等于所有元素和的一半是我们要求的结果。
   先确定【状态】（影响结果的因素），在背包问题中，状态是背包的容量和可挑选的物品。
       dp[n][w]表示在前n个物品中选物品装进去，当背包容量 w 时，所能装下的最大的重量。
       对于这题来说，状态就是所有元素的和，和可选择的数字。
       dp[n][s] = x，表示对于前n个数字，是否能能挑选出一个子集，使得子集的和为s（s为所有元素之和的一半），
           若能那么x为true，否则x为false。
   【选择】：数字选出来或者不选出来
   【base case】：1，当数组中元素只有一个时，返回false
                   2，当数组中所有元素之和为奇数时，返回false
                   3，当背包容量为0时，只要不选取任何正整数，则被选取的正整数等于 0。所以，对于所有 0 <= i < n，都有dp[i][0] = true

   对于数组的最后一个元素，我们选择装或者不装，不装的话，传给子过程的背包容量不变，装的话，背包容量变小
   状态转移方程：
       F(N, S) = F(N - 1, S) || F( N - 1, S - nums[N - 1] )
       转成dp数组的形式就为：dp[N][S] = dp[N-1][S] || dp[N-1][S - nums[N-1]]

*/

/*
   时间复杂度：O(N*tager)，空间复杂度 O(N*tager)
*/

func canPartition(nums []int) bool {
	//先求出所有数的和
	sum := 0
	for _, n := range nums {
		sum += n
	}

	// 和为奇数时，不可能划分成两个和相等的集合
	if (sum % 2) != 0 {
		return false
	}

	//直接让sum变成一半
	target := sum / 2
	dp := make([][]bool, len(nums)+1)
	for i := 0; i < len(nums)+1; i++ {
		dp[i] = make([]bool, target+1)
	}

	//如果背包容量为空，那么肯定为true
	for i := 0; i < len(nums)+1; i++ {
		dp[i][0] = true
	}

	for n := 1; n <= len(nums); n++ {
		for s := 1; s <= target; s++ {
			// 不装进去
			noIn := dp[n-1][s]
			in := false
			//装进去
			if s >= nums[n-1] {
				in = dp[n-1][s-nums[n-1]]
			}
			dp[n][s] = noIn || in
		}
	}

	return dp[len(nums)][target]
}

/*
   状态压缩
*/

func canPartition2(nums []int) bool {
	//先求出所有数的和
	sum := 0
	for _, n := range nums {
		sum += n
	}

	// 和为奇数时，不可能划分成两个和相等的集合
	if (sum % 2) != 0 {
		return false
	}

	//直接让sum变成一半
	target := sum / 2
	dp := make([]bool, target+1)
	dp[0] = true

	for n := 1; n <= len(nums); n++ {
		for s := target; s >= 1; s-- {
			// 不装进去
			noIn := dp[s]
			in := false
			//装进去
			if s >= nums[n-1] {
				in = dp[s-nums[n-1]]
			}
			dp[s] = noIn || in
		}
	}

	return dp[target]
}

func main() {
}

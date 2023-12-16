package main

/*
   给你一个由 不同 整数组成的数组 nums ，和一个目标整数 target 。
   请你从 nums 中找出并返回总和为 target 的元素组合的个数。
   题目数据保证答案符合 32 位整数范围。

   示例：
       输入：nums = [1,2,3], target = 4
       输出: 4
       解释: 所有可能的组合为：
               (1, 1, 1, 1)
               (1, 2, 1)
               (1, 3)
               (2, 2)
*/

/*
   本题题目描述说是求组合，组合不强调顺序，(1,5)和(5,1)是同一个组合。
   原题是 leetcode 377，不过原题是让求排列，我这里把题目改了一下，求组合的数量，
       因为求排列，用这种方法不行。

   和 零钱兑换2 是一样的问题，都是从数组中选一些数出来，然后凑成目标值 target，并且数字都是可以无数次被选中。

   之所以把这题记录下来，两个目的
       1，作为一个 零钱兑换2 引申出来的一个问题。
       2，区分原题，原题求的是排列，本题求的是组合，不同的问法，解法是不一样的。
           原题会在 “爬楼梯思路” 中给出答案

   在 零钱兑换2 中，因为零钱都是大于0的，所以如果 target 等于 0，那么只有不选任何的硬币才能达成条件，只有这一种方法，
       所以对于任意的 0 <= i <= N，dp[i][0] = 1。

   但是在本题中，数字是可以为 0 的，此时如果 target 等于 0，那么可选的方法就很多了，
       比如 [0],[0,0] 都可以作为答案，所以，要像 目标和 问题一样，不能初始化 dp[i][0]，
       而是让 j 从 0 开始遍历，去函数中求 dp[i][0]

   定义 dp 数组
       dp[i][j] = x，表示在前 i 个数字中选数，凑出整数 j 的方法有 x 种。
   状态转移方程
       对于第 i 个数字，
       如果不选该数字，那么 dp[i][j] = dp[i-1][j]
       如果选择该数字，该数字在 nums 中的下标为 i-1，
           因为该数字可以被选择无数次，所以 dp[i][j] = dp[i][j - nums[i-1]]

       把这两种情况加起来，所以状态转移方程为
           dp[i][j] = dp[i-1][j] + dp[i][j - nums[i-1]]
   base case
       如果 nums 中没有数字，那么只有当 target = 0 时才符合，所以 dp[0][0] = 1
       当 target 等于0，和 目标和 那题类似，不能 判断出 dp[i][0] 有多少种方法，
           所以，不对 target 等于 0 的情况进行初始化，而是让 j 从 0 开始循环，去函数中计算 dp[i][0]
*/

func combinationSum(nums []int, target int) int {
	dp := make([][]int, len(nums)+1)
	for i := 0; i < len(nums)+1; i++ {
		dp[i] = make([]int, target+1)
	}

	// base case
	dp[0][0] = 1
	for i := 1; i <= len(nums); i++ {
		for j := 0; j <= target; j++ {
			noIn := dp[i-1][j]
			in := 0
			if j >= nums[i-1] {
				in = dp[i][j-nums[i-1]]
			}

			dp[i][j] = noIn + in
		}
	}
	return dp[len(nums)][target]
}

//状态压缩
func combinationSum2(nums []int, target int) int {
	dp := make([]int, target+1)
	// base case
	dp[0] = 1
	for i := 1; i <= len(nums); i++ {
		for j := 0; j <= target; j++ {
			noIn := dp[j]
			in := 0
			if j >= nums[i-1] {
				in = dp[j-nums[i-1]]
			}

			dp[j] = noIn + in
		}
	}
	return dp[target]
}

func main() {
}

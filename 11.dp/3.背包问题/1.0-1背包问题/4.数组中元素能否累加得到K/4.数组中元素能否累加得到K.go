package main

/*
   题目：
       给定一个数组nums，和一个整数K。如果可以任意选择nums中的
       数字，每个数字只能选择一次，能不能累加得到K，返回true或者false
*/

/*
   和 分割等和子集 类似，转成0-1背包问题：选取的物品的重量之和正好为背包总容量
   写出状态转移方程。
       F(N, K) = F(N-1, K) || F(N-1, K - nums[N-1])

   base case:
       当 K=0，对于所有 0 <= i < n，都有dp[i][K] = true
*/

func dp(nums []int, K int) bool {
	dp := make([][]bool, len(nums)+1)
	for i := 0; i < len(nums)+1; i++ {
		dp[i] = make([]bool, K+1)
	}

	// base case
	for i := 0; i <= len(nums); i++ {
		dp[i][0] = true
	}

	for n := 1; n <= len(nums); n++ {
		for k := 1; k <= K; k++ {
			noIn := dp[n-1][k]
			in := false
			if k >= nums[n-1] {
				in = dp[n-1][k-nums[n-1]]
			}

			dp[n][k] = noIn || in
		}
	}

	return dp[len(nums)][K]
}

//状态压缩
func dp2(nums []int, K int) bool {
	dp := make([]bool, K+1)

	// base case
	dp[0] = true

	for n := 1; n <= len(nums); n++ {
		for k := K; k >= 1; k-- {
			noIn := dp[k]
			in := false
			if k >= nums[n-1] {
				in = dp[k-nums[n-1]]
			}

			dp[k] = noIn || in
		}
	}

	return dp[K]
}

func main() {

}

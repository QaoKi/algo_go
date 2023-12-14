package main

/*
   题目：
       给定一个可装载重量为 W 的背包和 N 个物品，其中第i个物品的重量为 wt[i]，
       现在让你用这个背包装物品，最多能装的重量是多少？
   示例：
       N = 3, W = 4
       wt = [2, 1, 3]
       返回 4，选择后两件物品装进背包，总重量 4 等于W。
*/

/*
   题目中的物品不可以分割，对于每个物品来说，要么装进背包，要么不装，所以叫0-1背包问题。
   这道题不考虑物品的价值。问的是最多能装的重量。
   写出状态转移方程。第 N 个物品在数组中的下标为 N-1
       F(N, W) = max( F(N-1, W), F(N-1, W-wt[N-1]) + wt[N-1] )
*/

func dp(wt []int, W int) int {
	// 数组全填入 0，base case 已初始化
	dp := make([][]int, len(wt)+1)
	for i := 0; i < len(wt)+1; i++ {
		dp[i] = make([]int, W+1)
	}

	for n := 1; n <= len(wt); n++ {
		for w := 1; w <= W; w++ {
			// 不装
			noIn := dp[n-1][w]
			// 装
			in := 0
			if w >= wt[n-1] {
				in = dp[n-1][w-wt[n-1]] + wt[n-1]
			}

			dp[n][w] = noIn
			if in > noIn {
				dp[n][w] = in
			}
		}
	}
	return dp[len(wt)][W]
}

//状态压缩
func dp2(wt []int, W int) int {
	dp := make([]int, W+1)

	for n := 1; n <= len(wt); n++ {
		for w := W; w >= 1; w-- {
			// 不装
			noIn := dp[w]
			// 装
			in := 0
			if w >= wt[n-1] {
				in = dp[w-wt[n-1]] + wt[n-1]
			}

			dp[w] = noIn
			if in > noIn {
				dp[w] = in
			}
		}
	}

	return dp[W]
}

func main() {

}

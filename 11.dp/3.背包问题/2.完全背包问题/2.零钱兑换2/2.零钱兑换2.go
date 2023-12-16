package main

/*
   题目：leetcode 518
       给定不同面额的硬币和一个总金额。写出函数来计算可以凑成总金额的硬币组合数。假设每一种面额的硬币有无限个。
   示例：
       输入: amount = 5, coins = [1, 2, 5]
       输出: 4
       解释: 有四种方式可以凑成总金额:
               5=5
               5=2+2+1
               5=2+1+1+1
               5=1+1+1+1+1
   这个问题和我们前面讲过的两个背包问题，有一个最大的区别就是，每个物品的数量是无限的，这就是「完全背包问题」
*/

/*
   经典的0-1背包问题，是挑选硬币，总金额是否能等于给定的 amount，这道题是求可以凑成总金额的组合数目。
   能凑成总金额是amount的组合数目是我们要求的结果值。
   【状态】：不变，依然是背包的容量和可挑选的物品
       F(N, S) = x，若只使用前N个物品，当背包容量为S时，有x种方法可以装满背包。
       用dp数组表示为 dp[n][s] = x
   【选择】：硬币选出来或者不选出来
   【base case】：
       1，如果S为0，那么只有不选任何的硬币才能达成条件，只有这一种方法，所以对于任意的 0 <= n <= N，dp[n][0] = 1

   状态转移方程和0-1背包有所不同。
   如果不把第 n 个物品装入背包，也就是说不使用 coins[n-1] 这个面值的硬币，
       那么凑出面额 s 的方法数 dp[n][s] 应该等于dp[n-1][s]，继承之前的结果。
   如果把第n个物品装入了背包，也就是说决定使用 coins[n-1] 这个面值的硬币，那么 dp[n][s] 应该等于 dp[n][s-coins[n-1]]。
       因为硬币的数量是无限的，决定使用，但是没决定要使用多少次。所以，第一维度的 n 不要减1
   状态转移方程：
       F(N, S) = F(N - 1, S) + F( N, S - coins[N - 1] )
       转成dp数组的形式就为：dp[n][s] = dp[n-1][s] + dp[n][s - coins[n-1]]

   时间复杂度：O(N*amount)，空间复杂度 O(N*amount)
*/
func change(amount int, coins []int) int {

	dp := make([][]int, len(coins)+1)
	for i := 0; i < len(coins)+1; i++ {
		dp[i] = make([]int, amount+1)
	}

	// base case
	for i := 0; i < len(coins)+1; i++ {
		dp[i][0] = 1
	}

	for n := 1; n <= len(coins); n++ {
		for w := 1; w <= amount; w++ {
			noIn := dp[n-1][w]
			in := 0
			if w >= coins[n-1] {
				in = dp[n][w-coins[n-1]]
			}

			// 装进去+不装进去
			dp[n][w] = noIn + in
		}
	}
	return dp[len(coins)][amount]
}

/*
   change2 是一种错误的思路，我原本的想法是，dp[n][s] 表示从前N个硬币中挑选，是否能让挑选出来的总值等于 s
   这样 dp[n][s] 就是一个bool类型，但是这样会丢失满足的情况
   比如     amount = 5, coins = [1, 2, 5]
            有 4 种情况满足：
               5=5
               5=2+2+1
               5=2+1+1+1
               5=1+1+1+1+1
            但是要注意，第二种和第三种情况，都是在 dp[2][5] 的时候满足
            如果用 if dp[2][5] == true {
                      ret++
                  }
            这样会丢失一个满足情况
*/
func change2(amount int, coins []int) int {

	dp := make([][]bool, len(coins)+1)
	for i := 0; i < len(coins)+1; i++ {
		dp[i] = make([]bool, amount+1)
	}

	// base case
	for i := 0; i < len(coins)+1; i++ {
		dp[i][0] = true
	}

	for n := 1; n <= len(coins); n++ {
		for w := 1; w <= amount; w++ {
			noIn := dp[n-1][w]
			in := false
			if w >= coins[n-1] {
				in = dp[n][w-coins[n-1]]
			}

			dp[n][w] = noIn || in
		}
	}

	ret := 0
	for i := 0; i < len(coins)+1; i++ {
		if dp[i][amount] {
			ret++
		}
	}
	return ret
}

/*
   状态压缩，状态转移方程为
       dp[n][s] = dp[n-1][s] + dp[n][s - coins[n-1]]
   和 零钱兑换1 一样，第二层循环从前往后循环
*/

func change3(amount int, coins []int) int {
	// 上一行数据
	dp := make([]int, amount+1)
	// base case
	dp[0] = 1
	for i := 1; i <= len(coins); i++ {
		for j := 1; j <= amount; j++ {
			noIn := dp[j]
			in := 0
			if j >= coins[i-1] {
				in = dp[j-coins[i-1]]
			}

			dp[j] = noIn + in
		}
	}

	return dp[amount]
}

func main() {
}

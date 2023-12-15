package main

/*
   题目：leetcode 1049
       有一堆石头，每块石头的重量都是正整数。
       每一回合，从中选出任意两块石头，然后将它们一起粉碎。
       假设石头的重量分别为 x 和 y，且 x <= y。那么粉碎的可能结果如下：
           如果 x == y，那么两块石头都会被完全粉碎；
           如果 x != y，那么重量为 x 的石头将会完全粉碎，而重量为 y 的石头新重量为 y-x。

       最后，最多只会剩下一块石头。返回此石头最小的可能重量。如果没有石头剩下，就返回 0。

       示例：
           输入：[2,7,4,1,8,1]
           输出：1
           解释：
               组合 2 和 4，得到 2，所以数组转化为 [2,7,1,8,1]，
               组合 7 和 8，得到 1，所以数组转化为 [2,1,1,1]，
               组合 2 和 1，得到 1，所以数组转化为 [1,1,1]，
               组合 1 和 1，得到 0，所以数组转化为 [1]，这就是最优值。
*/

/*
   把题目换种说法转化成 0-1背包问题，把一堆石头分成两堆，尽量让两堆石头的重量相等。
   计算出所有石头的总重量 sum，重量的一半 target = sum / 2;
   也就是从所有石头中选，尽量让选出来的重量是 target，所以背包的重量就为 target。

   定义 dp 数组
       dp[i][j] 表示从前 i 个石头中选，当背包容量为 j 时，能选出来的重量最大是多少。
   状态转移方程
       dp[i][j] = max(dp[i-1][j], dp[i-1][j - stones[i-1]] + stones[i-1])
                   max(第i个石头不装，第i个石头装)，第i个石头的下标为 i-1
   base case
       当背包容量为0，装不了石头，所以 dp[i][0] = 0
       当可选的石头为0，也装不了，所以 dp[0][j] = 0

   最终求出来 dp[stones.size()][target] 后
       表示选出来的一堆石头 A，重量是 dp[stones.size()][target]，
       那么另一堆石头 B 的重量就是 sum - dp[stones.size()][target]，
       让这两堆石头相碰撞，因为 B 的重量是 >= A 的重量，所以结果就是 B - A

   时间复杂度：O(n*target)
   空间复杂度：O(n*target)
*/

func lastStoneWeightII(stones []int) int {
	sum := 0
	for _, n := range stones {
		sum += n
	}

	target := sum / 2
	dp := make([][]int, len(stones)+1)
	for i := 0; i < len(stones)+1; i++ {
		dp[i] = make([]int, target+1)
	}

	// 因为数组中的值都被初始化为0，所以已经处理好了 base case

	for n := 1; n <= len(stones); n++ {
		for t := 1; t <= target; t++ {
			noIn := dp[n-1][t]
			in := 0
			if t >= stones[n-1] {
				in = dp[n-1][t-stones[n-1]] + stones[n-1]
			}

			dp[n][t] = noIn
			if in > noIn {
				dp[n][t] = in
			}
		}
	}

	ret := sum - dp[len(stones)][target] - dp[len(stones)][target]

	if ret < 0 {
		ret = -ret
	}

	return ret
}

/*
   状态压缩
*/

func lastStoneWeightII2(stones []int) int {
	sum := 0
	for _, n := range stones {
		sum += n
	}

	target := sum / 2
	dp := make([]int, target+1)

	// 因为数组中的值都被初始化为0，所以已经处理好了 base case

	for n := 1; n <= len(stones); n++ {
		for t := target; t >= 1; t-- {
			noIn := dp[t]
			in := 0
			if t >= stones[n-1] {
				in = dp[t-stones[n-1]] + stones[n-1]
			}

			dp[t] = noIn
			if in > noIn {
				dp[t] = in
			}
		}
	}

	ret := sum - dp[target] - dp[target]

	if ret < 0 {
		ret = -ret
	}

	return ret
}

func main() {

}

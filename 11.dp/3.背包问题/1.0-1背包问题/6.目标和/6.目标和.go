package main

import "fmt"

/*
   题目：leetcode 494
       给定一个非负整数数组，a1, a2, ..., an, 和一个目标数 target。现在你有两个符号 + 和 -。
       对于数组中的任意一个整数，你都可以从 + 或 - 中选择一个符号添加在前面。
       返回可以使最终数组和为目标数 target 的所有添加符号的方法数。

       示例：
           输入：nums: [1, 1, 1, 1, 1], target: 3
           输出：5
           解释：
               -1+1+1+1+1 = 3
               +1-1+1+1+1 = 3
               +1+1-1+1+1 = 3
               +1+1+1-1+1 = 3
               +1+1+1+1-1 = 3

               一共有5种方法让最终目标和为3。
*/

/*
   方法1，暴力递归
   对于每一个数字，两种选择，前面放 + 或者 前面放 -
   时间复杂度：O(2^n)
   空间复杂度：O(n)，为递归使用的栈空间大小。
*/
func dfs(nums []int, target, index, sum int, ret *int) {

	if index == len(nums) {
		if sum == target {
			*ret++
		}

		return
	}

	dfs(nums, target, index+1, sum+nums[index], ret)
	dfs(nums, target, index+1, sum-nums[index], ret)
}

func findTargetSumWays(nums []int, target int) int {
	ret := 0
	dfs(nums, target, 0, 0, &ret)
	return ret
}

// 函数内嵌的写法
func findTargetSumWays2(nums []int, target int) int {
	count := 0
	var backtrack func(int, int)
	backtrack = func(index, sum int) {
		if index == len(nums) {
			if sum == target {
				count++
			}
			return
		}
		backtrack(index+1, sum+nums[index])
		backtrack(index+1, sum-nums[index])
	}
	backtrack(0, 0)
	return count
}

/*
   https://leetcode-cn.com/problems/target-sum/solution/494-mu-biao-he-dong-tai-gui-hua-zhi-01be-78ll/

   方法2，动态规划
   对于 0-1背包问题，每个数字要么选要么不选，但本题是数字必须选，但是该数字要么前面加 + ，要么前面加 - 。
   我们先求出所有数字的累加和，设为 sum。
   所有的数字，前面要么是 +，要么是 -。假设所有前面是 + 的数字，累加起来和为 x
       那么，所有前面都是 - 的数字，累加起来和为 sum - x（这里只考虑数字本身的值，不考虑 -）。
   我们最终是想让 正数和 - 负数和 等于 target，也就是让 x - sum + x = target
   sum 和 target 都是已知的，所以我们要求的是 x，可以得出 x = (target + sum) / 2
   于是就转化成了求容量为 x 的 0-1背包问题 => 要装满容量为 x 的背包，有几种方案
       （在 nums 中选数，选出来的数字累加和为 x 的方案数量）
       这和之前的背包问题不一样， 之前的问题是能装多少的重量，现在问的是把背包装满有几种方法

   定义 dp 数组
       dp[i][j] 表示从数组的前 i 个数中选数，填满容量为 j 的背包，有 dp[i][j] 种方法。

   状态转移方程
       因为我们要求的是填满容量为 j 的背包方法的数量，对于第 i 个数，
       我们可以不选，不选的话，那么 dp[i][j] 就等于 dp[i-1][j]（前 i-1 个数填满容量为 j 的背包方法的数量）
       如果我们选了，那么 dp[i][j] 就等于 dp[i-1][j - num[i-1]]（前 i-1 个数填满容量为 j-num[i-1] 的背包方法的数量）
           第 i 个数，在数组中的下标为 i-1
       总的方法，等于上面两种情况相加，所以：

       dp[i][j] = dp[i-1][j] + dp[i-1][j - num[i-1]]
   base case
       1，如果 target 大于 sum，就算所有的数都是正的，也不可能实现，返回0
       2，如果 x 不是整数，也就是 (target + sum) 不是偶数，那么不可能实现，返回 0；
       3，如果可选的数字为0，那么只有当背包容量也为0时，才有一个解，所以 dp[0][0] = 1
       4，需要注意的是，如果背包容量为0，此时不能确定 dp[i][0] 的值为多少 (1 <= i <= nums.size())，
           因为 nums 中可能存在 0，也就是说物品的重量可能为 0，
           比如 nums = [0,0,0,0,0]，此时从 nums 中选数，使得累加和为 0 的方法就很多了，
           所以不需要初始化 dp[i][0]，而是去函数中求，所以需要让 j 从 0 开始遍历，
*/

// class Solution {
// public:
//     int findTargetSumWays(vector<int>& nums, int target) {
//         int sum = 0;
//         for (int i : nums)
//             sum += i;

//         if (target > sum || (target + sum) % 2 != 0)
//             return 0;

//         int x = (target + sum) / 2;
//         vector<vector<int>> dp(nums.size() + 1, vector<int>(x + 1, 0));

//         //base case
//         dp[0][0] = 1;

//         for (int i = 1; i <= nums.size(); i++) {
//             // j 从 0开始遍历，求 dp[i][0], (1 <= i <= nums.size())
//             for (int j = 0; j <= x; j++) {
//                 //不选
//                 int onIn = dp[i - 1][j];
//                 int in = 0;
//                 //选，背包的容量得够才能选
//                 if (j >= nums[i - 1])
//                     in = dp[i - 1][j - nums[i - 1]];

//                 dp[i][j] = in + onIn;
//             }
//         }
//         return dp[nums.size()][x];
//     }
// };

/*
   状态压缩
       第一维的 i 要从 0 开始遍历
       第二维要从前往后遍历
*/

// class Solution {
// public:
//     int findTargetSumWays(vector<int>& nums, int target) {
//         int sum = 0;
//         for (int i : nums)
//             sum += i;

//         if (target > sum || (target + sum) % 2 != 0)
//             return 0;

//         int x = (target + sum) / 2;
//         vector<int> dp(x + 1, 0);

//         //base case
//         dp[0] = 1;

//         for (int i = 1; i <= nums.size(); i++) {
//             //这里可以优化下写法，更简便，不过为了逻辑和上面的统一，就不优化了
//             for (int j = x; j >= 0; j--) {
//                 //不选，继承上一行的数据
//                 int onIn = dp[j];
//                 int in = 0;
//                 //选，背包的容量得够才能选
//                 if (j >= nums[i - 1])
//                     in = dp[j - nums[i - 1]];

//                 dp[j] = in + onIn;
//             }
//         }
//         return dp[x];
//     }
// };

func main() {
	nums := []int{1}
	target := 1

	ret := findTargetSumWays(nums, target)
	fmt.Println(ret)
}

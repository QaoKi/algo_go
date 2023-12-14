#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


/*
	题目： leetcode 198
		你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，
		影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，
		如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

		给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。
		示例 1：
			输入：[1,2,3,1]
			输出：4
			解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。偷窃到的最高金额 = 1 + 3 = 4 。

*/

/*
	1，dp
		看到题目，感觉和股票问题中，带有冷冻期的问题类似，但是比那道题简单，应该股票问题中，当天可以选择
			三个操作：买入、卖出、休息，而这道题只有两个操作：偷或者不偷
		我们像股票问题那题一样，
			定义dp[i][0]，表示经过i个家庭以后的最大金额，并且，第i个家庭选择不偷
			定义dp[i][1]，表示经过i个家庭以后的最大金额，并且，第i个家庭选择偷
		那么状态转移方程为：（ 第i家，在nums数组中的下标为 i-1 ）
			dp[i][0] = max( dp[i-1][1], dp[i-1][0] )
				解释：第i家没偷，可能是上一家偷了，这家不能偷了，也可能上一家也没偷，这家也选择不偷
			dp[i][1] = dp[i-1][0] + nums[i - 1]
				解释：第i家偷了，那么上一家肯定没偷，总金额加上第i家的钱（第i家的钱，在nums数组中下标为 i-1 ）
		最终结果在 dp[n][0]和dp[n][1] 中选较大的

		base case:
			dp[0][0] = 0，当一家也没得偷的时候，总金额为0
			dp[0][1] = INT_MIN，当一家也没得偷的时候，不可能偷，初始化为 INT_MIN，表示不可能
*/

int dp(vector<int> &nums) {
	int n = nums.size();
	if(n == 0) return 0;

	vector<vector<int>> dp(n + 1, vector<int>(2, 0));
	dp[0][0] = 0;
	dp[0][1] = INT_MIN;

	for (int i = 1; i <= n; i++) {
		dp[i][0] = max(dp[i - 1][1], dp[i - 1][0]);
		dp[i][1] = dp[i - 1][0] + nums[i - 1];
	}

	return max(dp[n][0], dp[n][1]);
}

/*
	2，状态压缩
		状态转移方程为
			dp[i][0] = max( dp[i-1][1], dp[i-1][0] )
			dp[i][1] = dp[i-1][0] + nums[i - 1]
		可以看到，当前行的数据，只和上一行的两个值有关，可以用两个变量来存储这两个值
*/

int dp_plus(vector<int> &nums) {
	int n = nums.size();
	if(n == 0) return 0;

	int dp_0 = 0;
	int dp_1 = INT_MIN;

	for (int i = 0; i < n; i++) {
		int dp_0_pre = dp_0;
		dp_0 = max(dp_1, dp_0);
		dp_1 = dp_0_pre + nums[i];
	}

	return max(dp_0, dp_1);
}

/*
	3，换种思路
		像股票问题一样，不用再定义一个状态，改变一下状态转移方程就可以求出

		对于第 i家，选择有偷或者不偷，
			如果选择偷，那么第i-1家就不能偷，那么偷第i家送带来的总金额，就是dp[i-2] + nums[i]，
			如果选择不偷，那么总金额就是 dp[i-1]，继承之前的数据
		所以，状态转移方程为
			dp[i] = max( dp[i-1], dp[i-2] + nums[i] )
		
		这种思路更好，第1种思路有些麻烦
*/

int dp2(vector<int> &nums) {
	int n = nums.size();
	if(n == 0) return 0;

	vector<int> dp(n + 1, 0);
	//base case
	dp[0] = 0;
	//方程中用到了 dp[i-2]，所以循环要从i=2开始，不然会越界
	dp[1] = nums[0];

	for (int i = 2; i <= n; i++) {
		dp[i] = max( dp[i - 1], dp[i - 2] + nums[i - 1]);
	}

	return dp[n];
}

/*
	4，状态压缩
		压缩也很好压缩，用两个变量，保存dp[i-1]和dp[i-2]
*/
int dp2_plus(vector<int> &nums) {
	int n = nums.size();
	if(n == 0) return 0;

	//base case
	int dp_old = 0;
	int dp_new = nums[0];

	//注意下标
	for (int i = 1; i < n; i++) {
		int temp = dp_new;
		dp_new = max( dp_new, dp_old + nums[i]);
		dp_old = temp;
	}

	return dp_new;
}

int main()
{
	return 0;
}
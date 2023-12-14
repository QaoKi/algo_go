#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


/*
	题目： leetcode 213
		你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，
		这个地方所有的房屋都 围成一圈 ，这意味着第一个房屋和最后一个房屋是紧挨着的。
		同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警 。

		给定一个代表每个房屋存放金额的非负整数数组，计算你 在不触动警报装置的情况下 ，能够偷窃到的最高金额。
		示例 1：
			输入：[2,3,2]
			输出：3
			解释：你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。

*/

/*
	1，dp
		和demo1_打家劫舍 相比，首尾形成了环，也就是说，偷了第一家，就不能偷最后一家，或者偷了最后一家，
		就不能偷第一家了，那么，把这两种情况都算出来，取较大的值。
	
	实现：
		如何算这两种情况？
			将 nums数组拆分
				1，nums[1:len-1]，不包括第一家
				2，nums[0:len-2]，不包括最后一家
			将拆分的数组分别代入demo1的方法中求解
*/

int dp(vector<int> &nums) {
	int n = nums.size();
	if(n == 0) return 0;
	if(n == 1) return nums[0];

	int no_0 = dp_help(nums, 1, n - 1);
	int no_end = dp_help(nums, 0, n - 2);

	return max(no_0, no_end);
}

int dp_help(vector<int> &nums, int start, int end) {
	if(start > end) return 0;

	//base case
	int dp_old = 0;
	int dp_new = nums[start];

	//注意下标
	for (int i = start + 1; i <= end; i++) {
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
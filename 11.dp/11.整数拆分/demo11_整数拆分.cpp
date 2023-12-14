#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


/*
	题目： leetcode 343，剑指offer 14-1 剪绳子
		给定一个正整数 n，将其拆分为至少两个正整数的和，并使这些整数的乘积最大化。 返回你可以获得的最大乘积。
		说明: 
			你可以假设 n 不小于 2 且不大于 58。

		示例 1：
			输入: 2
			输出: 1
			解释: 2 = 1 + 1, 1 × 1 = 1。
		示例 2：
			输入: 10
			输出: 36
			解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36。
*/

/*
	对于给定的正整数 n，要拆成至少两个正整数，设 k 是拆分出的第一个正整数，则剩下的部分是 n-k，
	对于 n-k，可以选择继续拆分，也可以选择不拆（至少拆成两个，k 和 n-k 已经是两个了）。

	定义 dp 数组，
		dp[i] 表示将正整数 i 拆分成至少两个正整数的和之后，这些正整数的最大乘积。
	求状态转移方程
		当 i = 0 或者 i = 1 时，0 和 1 都不能拆分，因此 dp[0] = dp[1] = 0。
		当 i ≥ 2 时，假设对正整数 i 拆分出的第一个正整数是 j (1 ≤ j < i)，
			那么对于剩下的部分 i-j，
				可以选择不拆，不拆的话，乘积就是 j*(i-j)；
				可以选择继续拆，拆的话，乘积就是 j*dp[i-j]
			所以，当 j 固定时，dp[i] = max(j*(i-j), j*dp[i-j])。而 j 的取值范围是 1 到 i-1，所以
			需要遍历 j 所有的可能取值，再取结果最大的。
		所以，递归公式为 dp[i] = max(dp[i], max(j*(i-j), j*dp[i-j]))，1 <= j <= i-1
	base case：
		dp[0] = dp[1] = 0;
		dp[2] = 1;

	时间复杂度：O(n^2)
	空间复杂度：O(n)
*/
class Solution {
public:
    int integerBreak(int n) {
		vector<int> dp(n + 1, 0);
		//base case
		dp[2] = 1;

		//从 dp[3] 开始求
		for (int i = 3; i <= n; i++) {
			// 1 <= j <= i-1
			for (int j = 1; j <= i - 1; j++) {
				dp[i] = max(dp[i], max(j * (i - j), j * dp[i - j]));
			}
		}

		return dp[n];
	}
};

/*
	2，状态压缩
		既然和爬楼梯一样，那么自然可以压缩到空间复杂度为O(1)
		用两个变量保存之前的状态
*/

int dp_plus(string s) {
	int n = s.length();
	if(n == 0 || s[0] == '0') return 0;

	int n_1 = 1;	//dp[i-1]
	//这里直接初始化dp[i-2]为1，当i=1的时候，就不需要特殊处理了
	int n_2 = 1;	//dp[i-2]

	for (int i = 1; i < n; i++) {
		int curr = 0;
		if (s[i] != '0')
			curr = n_1;

		int temp = (s[i - 1] - '0') * 10 + (s[i] - '0');
		if(10 <= temp && temp <= 26) 
			curr += n_2;
			
		n_2 = n_1;
		n_1 = curr;
	}

	return n_1;
}

int main()
{
	return 0;
}
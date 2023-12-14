#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

using namespace std;

/*
	题目： leetcode 62
		一个机器人位于一个 m x n 网格的左上角。
		机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角.
		问总共有多少条不同的路径？

		示例：
			输入：m = 3, n = 2
			输出：3
			解释：
				从左上角开始，总共有 3 条路径可以到达右下角。
				1. 向右 -> 向下 -> 向下
				2. 向下 -> 向下 -> 向右
				3. 向下 -> 向右 -> 向下

*/

/*
	1，dp
		和 demo1_最小路径和 题型类似，只不过现在求的是路径的数量
		二维数组，【状态】有两个，横纵坐标 i和j
		【选择】：向右走或者向下走
		定义 dp[i][j]：从左上角dp[0][0]走到 dp[i][j]有多少条不同的路径。
		求状态转移方程：
			求状态转移方程的思路，和求 demo2_爬楼梯 的思路类似，想走到dp[i][j]。那只能从dp[i-1][j]或者dp[i][j-1]走过来，
			那么走到dp[i][j]的路径数，就是走到dp[i-1][j]的路径数，加上走到dp[i][j-1]的路径数。
			所以，
				dp[i][j] = dp[i-1][j] + dp[i][j-1]
		base case：
			1，如果数组只有一行或者只有一列，那么很明显，只有走这条唯一的路。

*/

int dp(int m, int n) {
	if(m == 0 || n == 0) return 0;

	vector<vector<int>> dp(m, vector<int>(n, 0));

	//base case
	for (int i = 0; i < m; i++) {
		dp[i][0] = 1;
	}

	for (int i = 0; i < n; i++) {
		dp[0][i] = 1;
	}

	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			dp[i][j] = dp[i-1][j] + dp[i][j-1];
		}
	}

	return dp[m - 1][n - 1];
}

/*
	2，状态压缩
		这里的原理和 demo1_最小路径和 是一样的，
		这里dp[0]的初始化就不需要持续关注了，因为在开始求新一行数据的时候，dp[0]始终是1
*/

int dp_plus(int m, int n) {
	if(m == 0 || n == 0) return 0;

	//dp数据，保存的是上一行的数据，所以base case也是处理第一行的数据
	vector<int> dp(n, 0);
	
	//base case
	for (int i = 0; i < n; i++) {
		dp[i] = 1;
	}

	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			dp[j] = dp[j] + dp[j-1];
		}
	}

	return dp[n - 1];
}

/*
	3，排列组合
		从左上角到右下角的过程中，我们需要移动 m+n-2 次，其中有 m-1 次向下移动，n-1 次向右移动。
		因此路径的总数，就等于从 m+n-2 次移动中选择 m-1 次向下移动的方案数，即组合数：（注释不能表示数学符号，就不列了）
		(m+n-2)! / (m-1)!(n-1)!
*/

int uniquePaths(int m, int n) {
	long long ans = 1;
	for (int x = n, y = 1; y < m; ++x, ++y) {
		ans = ans * x / y;
	}
	return ans;
}

int main()
{
	return 0;
}
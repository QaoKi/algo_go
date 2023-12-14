#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

using namespace std;

/*
	题目： leetcode 64
		给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，
		使得路径上的数字总和为最小。
		说明：每次只能向下或者向右移动一步。

		比如
			1	3	1	
			1	5	1	
			4	2	1	
		输出：7
		解释：因为路径 1→3→1→1→1 的总和最小。

*/

/*
	1，dp
		二维数组，【状态】有两个，横纵坐标 i和j
		【选择】：向右走或者向下走
		定义 dp[i][j]：从左上角dp[0][0]走到 dp[i][j]所经过路径的最小和。
		那么状态转移方程为：
			dp[i][j] = min(dp[i][j-1], dp[i-1][j]) + grid[i][j]
		base case：
			1，dp[0][0] = grid[0][0]
			2，如果数组只有一行或者只有一列，那么很明显，只有走这条唯一的路。

*/

int dp(vector<vector<int>> &grid) {
	int m = grid.size(), n = grid[0].size();
	if(m == 0 || n == 0) return 0;

	vector<vector<int>> dp(m, vector<int>(n, 0));

	//base case
	dp[0][0] = grid[0][0];

	//其实第一列数据的初始化，可以放到第一层循环和第二层循环之间
	//在优化空间复杂度时，需要在那里初始化，这样的话可以做到统一
	for (int i = 1; i < m; i++) {
		dp[i][0] = dp[i - 1][0] + grid[i][0];
	}

	for (int i = 1; i < n; i++) {
		dp[0][i] = dp[0][i - 1] + grid[0][i];
	}

	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			dp[i][j] = min(dp[i][j - 1], dp[i - 1][j]) + grid[i][j];
		}
	}

	return dp[m - 1][n - 1];
}

/*
	2，状态压缩
		状态转移方程为：
			dp[i][j] = min(dp[i][j-1], dp[i-1][j]) + grid[i][j]
		只和当前行和上一行的数据有关，在求当前行下标为j的结果时，需要用到当前行下标为j-1的数据，
		所以，需要先求出当前行低位的数据，再用当前行低位的数据求当前行高位的数据，
		所以，遍历n的时候，应该从前往后遍历
		但是，还是有一个坑，就是dp[0]的初始化，在求第一行的时候，dp[0] = grid[0][0]，
		但是在求下面其他行的时候，需要重新初始化，
			在求第二行的时候，dp[0]应该等于 grid[0][0] + grid[1][0]
			在求第三行的时候，dp[0]应该等于 grid[0][0] + grid[1][0] + grid[2][0]
		因为 n是从1开始求的，求dp[1]的时候，需要用到dp[0]，所以在开始求每一行数据时，要初始化dp[0]

*/

int dp_plus(vector<vector<int>> &grid) {
	int m = grid.size(), n = grid[0].size();
	if(m == 0 || n == 0) return 0;

	//dp数据，保存的是上一行的数据，所以base case也是处理第一行的数据
	vector<int> dp(n, 0);
	//base case
	dp[0] = grid[0][0];
	for (int i = 1; i < n; i++) {
		dp[i] = dp[i - 1] + grid[0][i];
	}

	//开始处理第 [2...m-1] 行的数据。
	for (int i = 1; i < m; i++) {
		//相当于二维数据的第一列数据的初始化
		dp[0] = dp[0] + grid[i][0];
		for (int j = 1; j < n; j++) {
			dp[j] = min(dp[j - 1], dp[j]) + grid[i][j];
		}
	}

	return dp[n - 1];
}

int main()
{
	return 0;
}
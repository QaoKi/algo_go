#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


/*
	题目： leetcode 1277
		给你一个 m * n 的矩阵，矩阵中的元素不是 0 就是 1，请你统计并返回其中完全由 1 组成的 正方形 子矩阵的个数。

		示例 1：
			输入：matrix =  
					[
						[0,1,1,1],
						[1,1,1,1],
						[0,1,1,1]
					]
			输出：15
			解释： 
				边长为 1 的正方形有 10 个。
				边长为 2 的正方形有 4 个。
				边长为 3 的正方形有 1 个。
				正方形的总数 = 10 + 4 + 1 = 15
*/

/*
	1，dp
		和demo1_最大正方形类似，不过这题是统计正方形的数量。
		定义 dp[i][j] = x 表示以(0, 0) 到 (i, j) 组成的矩阵中，以(i, j)为右下角，完全由 1 组成的 正方形 子矩阵的个数。
			如果以(i, j)为右下角的正方形的最大边长为 y，那么，以(i, j)为右下角还能再组成边长为y-1,y-2...1的正方形，
				所以，以(i, j)为右下角，最大边长为y的正方形所能组成的正方形数量为y，所以，dp[i][j] = y
				比如：
					a b c
					d e f
					g h i（这里用字母表示，方便描述，所有字母的值都是1）

					以i为右下角的正方形的数量为2（最大边长为2），分别是a->i 和 e->i
					可以看出，以e,f,h为右下角，都能形成正方形，为什么这里不统计呢？
						因为这些数据，在处理以e为右下角，以f为右下角的时候会计算，这里只求以i为右下角的正方形即可
			这样就转成demo1中，求以(i, j)为右下角，只包含 1 的正方形的边长最大值
		状态转移方程同样为
			dp[i][j] = min( dp[i-1][j], dp[i-1][j-1], dp[i][j-1] ) + 1
		
		用一个变量累加这些值
	
	总结：
		要理解，以(i,j)为右下角组成的正方形，这表示正方形的右下角已经固定了，就和之前以s[i]为结尾的子序列一样。

*/

int dp(vector<vector<char>>& matrix) {
	int rows = matrix.size();	//行的数量
	int columns = matrix[0].size();	//列的数量
	if(rows == 0 || columns == 0)
		return 0;

	vector<vector<int>> dp(rows, vector<int>(columns, 0));
	
	int ans = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if(matrix[i][j] == 1) {
				//特殊处理一下第一行和第一列
				if(i == 0 || j == 0)
					dp[i][j] = 1;
				else
					dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i][j - 1])) + 1;
			}		
			ans += dp[i][j];
		}
	}

	return ans;
}

/*
	2，状态压缩，压缩为一维数组
*/

int dp_plus(vector<vector<char>>& matrix) {
	int rows = matrix.size();	//行的数量
	int columns = matrix[0].size();	//列的数量
	if(rows == 0 || columns == 0)
		return 0;

	vector<int> dp(columns, 0);

	int ans = 0;
	for(int i = 0; i < rows; i++) {
		//在dp[i][j]被求出来之前，用一个变量保存dp[i - 1][j]，防止覆盖
		int dp_pre = dp[0];
		for (int j = 0; j < columns; j++) {
			int temp = dp[j];
			if(matrix[i][j] == 1) {
				if(i == 0 || j == 0)
					dp[j] = 1;
				else
					//此时dp[j]保存的是dp[i-1][j]，dp_pre是dp[i-1][j-1]，dp[j-1]是dp[i][j-1]
					dp[j] = min(dp[j], min(dp_pre, dp[j - 1])) + 1;
			} else {
				dp[j] = 0;
			}

			ans += dp[j];
			dp_pre = temp;
		}
	}

	return ans;
}

int main()
{
	return 0;
}
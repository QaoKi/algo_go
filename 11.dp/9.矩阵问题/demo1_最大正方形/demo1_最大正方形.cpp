#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


/*
	题目： leetcode 221
		在一个由 0 和 1 组成的二维矩阵内，找到只包含 1 的最大正方形，并返回其面积。

		示例 1：
			输入：matrix =  
							0 1 1 1
						    1 0 1 1  
			输出：4
		示例 2：
			输入：matrix =  
							0 1 
						    1 0
			输出：1
*/

/*
	1，dp
		正方形的面积等于边长的平方，因此要找到最大正方形的面积，首先需要找到最大正方形的边长，然后计算最大边长的平方即可。

		定义 dp[i][j] = x 表示以(0, 0) 到 (i, j) 组成的矩阵中，以(i, j)为右下角，只包含 1 的正方形的边长最大值为x。
		如何求 dp[i][j]？
			1，如果(i, j)位置值为0，那么 dp[i][j] = 0
			2，如果(i, j)位置值为1，dp[i][j]的值由其上方、左方和左上方的三个相邻位置的dp 值决定
				具体而言，dp[i][j]等于三个相邻位置的元素中的 dp 最小值加 1，
				状态转移方程如下：
					dp[i][j] = min( dp[i-1][j], dp[i-1][j-1], dp[i][j-1] ) + 1
				证明：
					还是画图比较明显，具体看 https://leetcode-cn.com/problems/maximal-square/solution/li-jie-san-zhe-qu-zui-xiao-1-by-lzhlyle/
					如果左、左上、上，三个位置中，有一个是0，那么当前位置只能是自身，也就是1，同样符合这条规律
		
		用一个变量保存最大的边长，最后返回面积

*/

int dp(vector<vector<char>>& matrix) {
	int rows = matrix.size();	//行的数量
	int columns = matrix[0].size();	//列的数量
	if(rows == 0 || columns == 0)
		return 0;

	vector<vector<int>> dp(rows, vector<int>(columns, 0));
	
	int maxSide = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if(matrix[i][j] == '1') {
				//特殊处理一下第一行和第一列
				//第一行和第一列的base case，就不单独处理，因为可能会出现maxSize比较不全的问题
				if(i == 0 || j == 0)
					dp[i][j] = 1;
				else
					dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i][j - 1])) + 1;
			}		
			maxSide = max(maxSide, dp[i][j]);
		}
	}

	return maxSide * maxSide;
}

/*
	2，状态压缩，压缩为一维数组
		状态转移方程为：
			dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i][j - 1])) + 1;
		要求的当前位置，和左、上、左上有关，
			和demo4_子序列问题/demo1_最长公共子序列的状态压缩类似
		需要使用一个变量，在求出dp[i][j]的时候，保存dp[i - 1][j]，防止被覆盖
*/

int dp_plus(vector<vector<char>>& matrix) {
	int rows = matrix.size();	//行的数量
	int columns = matrix[0].size();	//列的数量
	if(rows == 0 || columns == 0)
		return 0;

	vector<int> dp(columns, 0);

	int maxSide = 0;
	for(int i = 0; i < rows; i++) {
		//在dp[i][j]被求出来之前，用一个变量保存dp[i - 1][j]，防止覆盖
		int dp_pre = dp[0];
		for (int j = 0; j < columns; j++) {
			int temp = dp[j];
			if(matrix[i][j] == '1') {
				if(i == 0 || j == 0)
					dp[j] = 1;
				else
					//此时dp[j]保存的是dp[i-1][j]，dp_pre是dp[i-1][j-1]，dp[j-1]是dp[i][j-1]
					dp[j] = min(dp[j], min(dp_pre, dp[j - 1])) + 1;
			} else {
				dp[j] = 0;
			}

			maxSide = max(maxSide, dp[j]);
			dp_pre = temp;
		}
	}

	return maxSide * maxSide;
}

int main()
{
	return 0;
}
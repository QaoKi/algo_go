#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

using namespace std;

/*
	题目： leetcode 63
		一个机器人位于一个 m x n 网格的左上角。
		机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角.
		现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？
		网格中的障碍物和空位置分别用 1 和 0 来表示。
*/

/*
	1，dp
		和 demo2_不同路径 一样，只不过加了障碍物，obstacleGrid[i][j] = 1，表示这个位置是个障碍物
		状态转移方程：
			和demo2_不同路径 一样，依然是
				dp[i][j] = dp[i-1][j] + dp[i][j-1]
			我们不去挨个判断 dp[i-1][j] 或者 dp[i][j-1]是否是障碍物，
				因为如果他们其中有障碍物，比如 obstacleGrid[i-1][j]位置是障碍物，那么dp[i-1][j]=0，加上也不影响结果
			不过求dp[i][j]，我们需要判断一下 obstacleGrid[i][j]是否是障碍物，如果是障碍物，直接不用求，让它等于默认的0即可
		base case：
			1，如果数组只有一行或者只有一列，那么很明显，只有走这条唯一的路。但是如果路上有障碍物，那么障碍物之后的路，都走不通了，
				所以 base case的初始化也要改一下

*/

int dp(vector<vector<int>>& obstacleGrid) {
	int m = obstacleGrid.size();
	int n = obstacleGrid[0].size();
	if(m == 0 || n == 0) return 0;

	vector<vector<int>> dp(m, vector<int>(n, 0));

	//base case
	for (int i = 0; i < m; i++) {
		//遇到障碍物，之后的路都走不通了
		if(obstacleGrid[i][0] == 1)
			break;
		dp[i][0] = 1;
	}

	for (int i = 0; i < n; i++) {
		if(obstacleGrid[0][i] == 1)
			break;		
		dp[0][i] = 1;
	}

	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			//当前位置不是障碍物时才求
			if(obstacleGrid[i][j] == 0)
				dp[i][j] = dp[i-1][j] + dp[i][j-1];
		}
	}

	return dp[m - 1][n - 1];
}

/*
	2，状态压缩，这里的 dp[0] 要特殊处理一下，因为不一定就是1
*/

int dp_plus(vector<vector<int>>& obstacleGrid) {
	int m = obstacleGrid.size();
	int n = obstacleGrid[0].size();
	if(m == 0 || n == 0) return 0;

	//dp数据，保存的是上一行的数据，所以base case也是处理第一行的数据
	vector<int> dp(n, 0);
	//base case
	for (int i = 0; i < n; i++) {
		if(obstacleGrid[0][i] == 1)
			break;
		dp[i] = 1;
	}

	for (int i = 1; i < m; i++) {
		//如果上一行的dp[0]是0，那说明第一列这条路早就遇到了障碍物，之后的dp[0]都是0
		//如果之前都没遇到障碍物，判断当前行dp[0]是否是障碍物
		dp[0] = dp[0] != 0 && obstacleGrid[i][0] != 1 ? 1 : 0;
			
		for (int j = 1; j < n; j++) {
			if(obstacleGrid[i][j] == 0)
				dp[j] = dp[j] + dp[j-1];
			else
				//这里也要处理一下，不然会继承上一行的数据，造成错误
				dp[j] = 0;
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
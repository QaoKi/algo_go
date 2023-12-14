#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
/*
	题目： leetcode 120
		给定一个三角形 triangle ，找出自顶向下的最小路径和，
		每一步只能移动到下一行中相邻的结点上。
		相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点。
		也就是说，如果正位于当前行的下标 i ，那么下一步可以移动到下一行的下标 i 或 i + 1 。
		示例 1：
			输入：triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
			输出：11
			解释：如下面简图所示：
					2
					3 4
					6 5 7
					4 1 8 3
				自顶向下的最小路径和为 11（即，2 + 3 + 5 + 1 = 11）。

*/

/*	
	这道题的解和之前不同，之前求的是走到右下角的最小路径和，也就是 dp[m-1][n-1]
		而这道题求的是 dp[m-1][0], dp[m-1][1], dp[m-1][2]...dp[m-1][n-1]，所有这些值中，最小的那个

	定义 dp[i][j]：从左上角dp[0][0]走到 dp[i][j]所经过路径的最小和。
	【选择】向 dp[i+1][j]走，或者 向 dp[i+1][j+1]走

	那么状态转移方程为：
		dp[i][j] = min(dp[i-1][j-1], dp[i-1][j]) + grid[i][j]
	base case：
		1，dp数组要初始化成超大值
		2，dp[0][0] = grid[0][0]
		3，如果数组只有一列，那么很明显，只有走这条唯一的路。
		4，如果数组只有一行，再加上它是三角形，三角形的第一行只有一个元素，那么这一行就只有一个元素

*/

int dp(vector<vector<int>> &triangle) {
	//三角形有个特性，第一行有一个元素，第二行有两个元素。。。所以，一个有n行的三角形，最后一行的大小也为n
	int n = triangle.size();
	if(n == 0) return 0;

	//注意，要初始化成超大值
	vector<vector<int>> dp(n, vector<int>(n, INT_MAX));

	//base case
	//三角形的第一行数据，肯定是只有一个元素，直接等于 triangle[0][0] 就行，就不再初始化第一行的数据
	dp[0][0] = triangle[0][0];

	//只初始化第一列的数据
	//其实第一列数据的初始化，可以放到第一层循环和第二层循环之间
	//因为在状态压缩时，需要在那里初始化，这样的话可以做到统一
	for (int i = 1; i < n; i++) {
		dp[i][0] = dp[i - 1][0] + triangle[i][0];
	}

	for (int i = 1; i < n; i++) {
		//每一行的数据量不同，所以j的最大值也是不同的
		for (int j = 1; j < triangle[i].size(); j++) {
			dp[i][j] = min(dp[i-1][j - 1], dp[i - 1][j]) + triangle[i][j];
		}
	}

	//找最后一行的最小值
	int res = INT_MAX;
	for(int num : dp[n-1])
		res = min(res, num);

	return res;
}

/*
	2，状态压缩
		状态转移方程为：
			dp[i][j] = min(dp[i-1][j-1], dp[i-1][j]) + grid[i][j]
		只和上一行的数据有关，不过需要着重看一下遍历顺序，
			当只使用一个一维数组时，在求当前行下标j位置的数据时，需要用到上一行下标为j-1的数据，
			如果第二层循环是从前往后遍历，那么很明显，上一行下标j-1位置的数据，已经在计算当前行下标j-1位置时
			被覆盖了，所以，第二层循环要从后往前遍历
	注意的点：
		1，dp数组别忘了初始化为 INT_MAX
		2，第一列数据的base case 初始化，虽然是要放到第一层循环和第二层循环之间
			但是，不能在循环一开始就重新初始化，因为在求当前行j为1时，还是需要用到上一个下标为0的数据，也就是上一行的dp[0]，
			所以，需要等到当前行的数据dp[1]...dp[triangle[i].size()-1]都求完了，才能求当前行的dp[0]。

			这其实也是符合第二层遍历需要从后往前遍历的原则，当前行下标为0的数据，需要最后求
*/

int dp_plus(vector<vector<int>> &triangle) {
	int n = triangle.size();
	if(n == 0) return 0;

	//dp数据，保存的是上一行的数据，所以base case也是处理第一行的数据
	vector<int> dp(n, INT_MAX);
	//base case，第一行只有一个元素
	dp[0] = triangle[0][0];

	//因为是一维数组，所以第一列数据的base case 初始化，就需要放到第一层循环和第二层循环之间了
	for (int i = 1; i < n; i++) {	
		for (int j = triangle[i].size() - 1; j >= 1; j--) {
			dp[j] = min(dp[j - 1], dp[j]) + triangle[i][j];
		}

		//当前行下标为0的数据，需要最后求
		dp[0] = dp[0] + triangle[i][0];
	}

	//找最后一行的最小值
	int res = INT_MAX;
	for(int num : dp)
		res = min(res, num);

	return res;
}

/*
	3，将自顶向下的dp改成自底向上的dp
		上面自顶向上的dp，虽然符合常规的dp思路，但是写起来要注意很多边界问题，
		如果这道题我们考虑自底向上的思路，可以避免很多边界问题。

		自顶向下的时候，是从 dp[i][j]的值是从dp[i-1][j]和dp[i-1][j-1]中取一个较小值，加上triangle[i][j]计算得出。
		而自底向上的思路，dp[i][j]是从dp[i+1][j]和dp[i+1][j+1]中取一个较小值，加上triangle[i][j]计算得出。
		所以，自底向上dp的状态转移方程为
			dp[i][j] = min( dp[i+1][j], dp[i+1][j+1] ) + triangle[i][j]
		
		base case:
			自底向上，那么自然是先要求出最后一行，很明显，dp[n-1][i] = triangle[n-1][i]，n-1表示位于最后一行
		
		自底向上的好处：
			1，返回值直接返回dp[0][0]即可，因为顶部只有一个元素，不需要再像原来，需要去遍历找一个最小值
			2，即使使用二维数组，也只需要初始化最后一行的数据，不需要再像原来，还需要去处理第一列的数据
				（因为原来的方法，需要用到 dp[i-1][j-1]，i和j不能为0，最小为1，所以，第一行和第二列的数据需要单独处理）
				但是现在用到的是dp[i+1][j+1]，i和j可以为0，也就不需要单独处理了
			3，dp数组不需要初始化为 INT_MAX了，
				因为在求dp[i][j]的时候，dp[i+1][j+1]我们是已知的，不再像原来一样是 “越界” 的数据
*/

int dp2(vector<vector<int>>& triangle) {
	int n = triangle.size();
	if(n == 0) return 0;

	vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
	//base case 初始化最后一行，最底行各节点的最小路径和为节点值本身
	for (int j = 0; j < triangle[n-1].size(); j++) {
		dp[n-1][j] = triangle[n-1][j]; 
	}

	//从倒数第二行求
	for (int i = n-2; i >= 0; i--) {
		for (int j = 0; j < triangle[i].size(); j++) {
			dp[i][j] = min(dp[i+1][j], dp[i+1][j+1]) + triangle[i][j];
		}
	}
	// dp[0][0]即为题解
	return dp[0][0];
}

/*
	4，状态压缩
		状态转移方程为
			dp[i][j] = min( dp[i+1][j], dp[i+1][j+1] ) + triangle[i][j]

			在求当前行下标为j的数据时，需要使用到下一行下标为j+1的数据，所以该方法的第二层循环，需要从前往后
*/

int dp2_plus(vector<vector<int>>& triangle) {
	int n = triangle.size();
	if(n == 0) return 0;

	vector<int> dp(n, 0);
	//base case 初始化最后一行，最底行各节点的最小路径和为节点值本身
	for (int j = 0; j < triangle[n-1].size(); j++) {
		dp[j] = triangle[n-1][j]; 
	}

	//从倒数第二行求
	for (int i = n-2; i >= 0; i--) {
		for (int j = 0; j < triangle[i].size(); j++) {
			dp[j] = min(dp[j], dp[j+1]) + triangle[i][j];
		}
	}
	// dp[0][0]即为题解
	return dp[0];
}

int main()
{
	return 0;
}
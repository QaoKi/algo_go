#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

using namespace std;

/*
	��Ŀ�� leetcode 64
		����һ�������Ǹ������� m x n ���� grid �����ҳ�һ�������Ͻǵ����½ǵ�·����
		ʹ��·���ϵ������ܺ�Ϊ��С��
		˵����ÿ��ֻ�����»��������ƶ�һ����

		����
			1	3	1	
			1	5	1	
			4	2	1	
		�����7
		���ͣ���Ϊ·�� 1��3��1��1��1 ���ܺ���С��

*/

/*
	1��dp
		��ά���飬��״̬������������������ i��j
		��ѡ�񡿣������߻���������
		���� dp[i][j]�������Ͻ�dp[0][0]�ߵ� dp[i][j]������·������С�͡�
		��ô״̬ת�Ʒ���Ϊ��
			dp[i][j] = min(dp[i][j-1], dp[i-1][j]) + grid[i][j]
		base case��
			1��dp[0][0] = grid[0][0]
			2���������ֻ��һ�л���ֻ��һ�У���ô�����ԣ�ֻ��������Ψһ��·��

*/

int dp(vector<vector<int>> &grid) {
	int m = grid.size(), n = grid[0].size();
	if(m == 0 || n == 0) return 0;

	vector<vector<int>> dp(m, vector<int>(n, 0));

	//base case
	dp[0][0] = grid[0][0];

	//��ʵ��һ�����ݵĳ�ʼ�������Էŵ���һ��ѭ���͵ڶ���ѭ��֮��
	//���Ż��ռ临�Ӷ�ʱ����Ҫ�������ʼ���������Ļ���������ͳһ
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
	2��״̬ѹ��
		״̬ת�Ʒ���Ϊ��
			dp[i][j] = min(dp[i][j-1], dp[i-1][j]) + grid[i][j]
		ֻ�͵�ǰ�к���һ�е������йأ�����ǰ���±�Ϊj�Ľ��ʱ����Ҫ�õ���ǰ���±�Ϊj-1�����ݣ�
		���ԣ���Ҫ�������ǰ�е�λ�����ݣ����õ�ǰ�е�λ��������ǰ�и�λ�����ݣ�
		���ԣ�����n��ʱ��Ӧ�ô�ǰ�������
		���ǣ�������һ���ӣ�����dp[0]�ĳ�ʼ���������һ�е�ʱ��dp[0] = grid[0][0]��
		�����������������е�ʱ����Ҫ���³�ʼ����
			����ڶ��е�ʱ��dp[0]Ӧ�õ��� grid[0][0] + grid[1][0]
			��������е�ʱ��dp[0]Ӧ�õ��� grid[0][0] + grid[1][0] + grid[2][0]
		��Ϊ n�Ǵ�1��ʼ��ģ���dp[1]��ʱ����Ҫ�õ�dp[0]�������ڿ�ʼ��ÿһ������ʱ��Ҫ��ʼ��dp[0]

*/

int dp_plus(vector<vector<int>> &grid) {
	int m = grid.size(), n = grid[0].size();
	if(m == 0 || n == 0) return 0;

	//dp���ݣ����������һ�е����ݣ�����base caseҲ�Ǵ����һ�е�����
	vector<int> dp(n, 0);
	//base case
	dp[0] = grid[0][0];
	for (int i = 1; i < n; i++) {
		dp[i] = dp[i - 1] + grid[0][i];
	}

	//��ʼ����� [2...m-1] �е����ݡ�
	for (int i = 1; i < m; i++) {
		//�൱�ڶ�ά���ݵĵ�һ�����ݵĳ�ʼ��
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
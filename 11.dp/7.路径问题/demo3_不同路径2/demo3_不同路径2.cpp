#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

using namespace std;

/*
	��Ŀ�� leetcode 63
		һ��������λ��һ�� m x n ��������Ͻǡ�
		������ÿ��ֻ�����»��������ƶ�һ������������ͼ�ﵽ��������½�.
		���ڿ������������ϰ����ô�����Ͻǵ����½ǽ����ж�������ͬ��·����
		�����е��ϰ���Ϳ�λ�÷ֱ��� 1 �� 0 ����ʾ��
*/

/*
	1��dp
		�� demo2_��ͬ·�� һ����ֻ���������ϰ��obstacleGrid[i][j] = 1����ʾ���λ���Ǹ��ϰ���
		״̬ת�Ʒ��̣�
			��demo2_��ͬ·�� һ������Ȼ��
				dp[i][j] = dp[i-1][j] + dp[i][j-1]
			���ǲ�ȥ�����ж� dp[i-1][j] ���� dp[i][j-1]�Ƿ����ϰ��
				��Ϊ��������������ϰ������ obstacleGrid[i-1][j]λ�����ϰ����ôdp[i-1][j]=0������Ҳ��Ӱ����
			������dp[i][j]��������Ҫ�ж�һ�� obstacleGrid[i][j]�Ƿ����ϰ��������ϰ��ֱ�Ӳ�������������Ĭ�ϵ�0����
		base case��
			1���������ֻ��һ�л���ֻ��һ�У���ô�����ԣ�ֻ��������Ψһ��·���������·�����ϰ����ô�ϰ���֮���·�����߲�ͨ�ˣ�
				���� base case�ĳ�ʼ��ҲҪ��һ��

*/

int dp(vector<vector<int>>& obstacleGrid) {
	int m = obstacleGrid.size();
	int n = obstacleGrid[0].size();
	if(m == 0 || n == 0) return 0;

	vector<vector<int>> dp(m, vector<int>(n, 0));

	//base case
	for (int i = 0; i < m; i++) {
		//�����ϰ��֮���·���߲�ͨ��
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
			//��ǰλ�ò����ϰ���ʱ����
			if(obstacleGrid[i][j] == 0)
				dp[i][j] = dp[i-1][j] + dp[i][j-1];
		}
	}

	return dp[m - 1][n - 1];
}

/*
	2��״̬ѹ��������� dp[0] Ҫ���⴦��һ�£���Ϊ��һ������1
*/

int dp_plus(vector<vector<int>>& obstacleGrid) {
	int m = obstacleGrid.size();
	int n = obstacleGrid[0].size();
	if(m == 0 || n == 0) return 0;

	//dp���ݣ����������һ�е����ݣ�����base caseҲ�Ǵ����һ�е�����
	vector<int> dp(n, 0);
	//base case
	for (int i = 0; i < n; i++) {
		if(obstacleGrid[0][i] == 1)
			break;
		dp[i] = 1;
	}

	for (int i = 1; i < m; i++) {
		//�����һ�е�dp[0]��0����˵����һ������·����������ϰ��֮���dp[0]����0
		//���֮ǰ��û�����ϰ���жϵ�ǰ��dp[0]�Ƿ����ϰ���
		dp[0] = dp[0] != 0 && obstacleGrid[i][0] != 1 ? 1 : 0;
			
		for (int j = 1; j < n; j++) {
			if(obstacleGrid[i][j] == 0)
				dp[j] = dp[j] + dp[j-1];
			else
				//����ҲҪ����һ�£���Ȼ��̳���һ�е����ݣ���ɴ���
				dp[j] = 0;
		}
	}

	return dp[n - 1];
}

/*
	3���������
		�����Ͻǵ����½ǵĹ����У�������Ҫ�ƶ� m+n-2 �Σ������� m-1 �������ƶ���n-1 �������ƶ���
		���·�����������͵��ڴ� m+n-2 ���ƶ���ѡ�� m-1 �������ƶ��ķ������������������ע�Ͳ��ܱ�ʾ��ѧ���ţ��Ͳ����ˣ�
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
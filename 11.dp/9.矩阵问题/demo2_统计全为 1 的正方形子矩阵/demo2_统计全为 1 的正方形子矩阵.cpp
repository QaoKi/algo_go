#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


/*
	��Ŀ�� leetcode 1277
		����һ�� m * n �ľ��󣬾����е�Ԫ�ز��� 0 ���� 1������ͳ�Ʋ�����������ȫ�� 1 ��ɵ� ������ �Ӿ���ĸ�����

		ʾ�� 1��
			���룺matrix =  
					[
						[0,1,1,1],
						[1,1,1,1],
						[0,1,1,1]
					]
			�����15
			���ͣ� 
				�߳�Ϊ 1 ���������� 10 ����
				�߳�Ϊ 2 ���������� 4 ����
				�߳�Ϊ 3 ���������� 1 ����
				�����ε����� = 10 + 4 + 1 = 15
*/

/*
	1��dp
		��demo1_������������ƣ�����������ͳ�������ε�������
		���� dp[i][j] = x ��ʾ��(0, 0) �� (i, j) ��ɵľ����У���(i, j)Ϊ���½ǣ���ȫ�� 1 ��ɵ� ������ �Ӿ���ĸ�����
			�����(i, j)Ϊ���½ǵ������ε����߳�Ϊ y����ô����(i, j)Ϊ���½ǻ�������ɱ߳�Ϊy-1,y-2...1�������Σ�
				���ԣ���(i, j)Ϊ���½ǣ����߳�Ϊy��������������ɵ�����������Ϊy�����ԣ�dp[i][j] = y
				���磺
					a b c
					d e f
					g h i����������ĸ��ʾ������������������ĸ��ֵ����1��

					��iΪ���½ǵ������ε�����Ϊ2�����߳�Ϊ2�����ֱ���a->i �� e->i
					���Կ�������e,f,hΪ���½ǣ������γ������Σ�Ϊʲô���ﲻͳ���أ�
						��Ϊ��Щ���ݣ��ڴ�����eΪ���½ǣ���fΪ���½ǵ�ʱ�����㣬����ֻ����iΪ���½ǵ������μ���
			������ת��demo1�У�����(i, j)Ϊ���½ǣ�ֻ���� 1 �������εı߳����ֵ
		״̬ת�Ʒ���ͬ��Ϊ
			dp[i][j] = min( dp[i-1][j], dp[i-1][j-1], dp[i][j-1] ) + 1
		
		��һ�������ۼ���Щֵ
	
	�ܽ᣺
		Ҫ��⣬��(i,j)Ϊ���½���ɵ������Σ����ʾ�����ε����½��Ѿ��̶��ˣ��ͺ�֮ǰ��s[i]Ϊ��β��������һ����

*/

int dp(vector<vector<char>>& matrix) {
	int rows = matrix.size();	//�е�����
	int columns = matrix[0].size();	//�е�����
	if(rows == 0 || columns == 0)
		return 0;

	vector<vector<int>> dp(rows, vector<int>(columns, 0));
	
	int ans = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if(matrix[i][j] == 1) {
				//���⴦��һ�µ�һ�к͵�һ��
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
	2��״̬ѹ����ѹ��Ϊһά����
*/

int dp_plus(vector<vector<char>>& matrix) {
	int rows = matrix.size();	//�е�����
	int columns = matrix[0].size();	//�е�����
	if(rows == 0 || columns == 0)
		return 0;

	vector<int> dp(columns, 0);

	int ans = 0;
	for(int i = 0; i < rows; i++) {
		//��dp[i][j]�������֮ǰ����һ����������dp[i - 1][j]����ֹ����
		int dp_pre = dp[0];
		for (int j = 0; j < columns; j++) {
			int temp = dp[j];
			if(matrix[i][j] == 1) {
				if(i == 0 || j == 0)
					dp[j] = 1;
				else
					//��ʱdp[j]�������dp[i-1][j]��dp_pre��dp[i-1][j-1]��dp[j-1]��dp[i][j-1]
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
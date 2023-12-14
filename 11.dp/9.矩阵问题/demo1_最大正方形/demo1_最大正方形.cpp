#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


/*
	��Ŀ�� leetcode 221
		��һ���� 0 �� 1 ��ɵĶ�ά�����ڣ��ҵ�ֻ���� 1 ����������Σ��������������

		ʾ�� 1��
			���룺matrix =  
							0 1 1 1
						    1 0 1 1  
			�����4
		ʾ�� 2��
			���룺matrix =  
							0 1 
						    1 0
			�����1
*/

/*
	1��dp
		�����ε�������ڱ߳���ƽ�������Ҫ�ҵ���������ε������������Ҫ�ҵ���������εı߳���Ȼ��������߳���ƽ�����ɡ�

		���� dp[i][j] = x ��ʾ��(0, 0) �� (i, j) ��ɵľ����У���(i, j)Ϊ���½ǣ�ֻ���� 1 �������εı߳����ֵΪx��
		����� dp[i][j]��
			1�����(i, j)λ��ֵΪ0����ô dp[i][j] = 0
			2�����(i, j)λ��ֵΪ1��dp[i][j]��ֵ�����Ϸ����󷽺����Ϸ�����������λ�õ�dp ֵ����
				������ԣ�dp[i][j]������������λ�õ�Ԫ���е� dp ��Сֵ�� 1��
				״̬ת�Ʒ������£�
					dp[i][j] = min( dp[i-1][j], dp[i-1][j-1], dp[i][j-1] ) + 1
				֤����
					���ǻ�ͼ�Ƚ����ԣ����忴 https://leetcode-cn.com/problems/maximal-square/solution/li-jie-san-zhe-qu-zui-xiao-1-by-lzhlyle/
					��������ϡ��ϣ�����λ���У���һ����0����ô��ǰλ��ֻ��������Ҳ����1��ͬ��������������
		
		��һ�������������ı߳�����󷵻����

*/

int dp(vector<vector<char>>& matrix) {
	int rows = matrix.size();	//�е�����
	int columns = matrix[0].size();	//�е�����
	if(rows == 0 || columns == 0)
		return 0;

	vector<vector<int>> dp(rows, vector<int>(columns, 0));
	
	int maxSide = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if(matrix[i][j] == '1') {
				//���⴦��һ�µ�һ�к͵�һ��
				//��һ�к͵�һ�е�base case���Ͳ�����������Ϊ���ܻ����maxSize�Ƚϲ�ȫ������
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
	2��״̬ѹ����ѹ��Ϊһά����
		״̬ת�Ʒ���Ϊ��
			dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i][j - 1])) + 1;
		Ҫ��ĵ�ǰλ�ã������ϡ������йأ�
			��demo4_����������/demo1_����������е�״̬ѹ������
		��Ҫʹ��һ�������������dp[i][j]��ʱ�򣬱���dp[i - 1][j]����ֹ������
*/

int dp_plus(vector<vector<char>>& matrix) {
	int rows = matrix.size();	//�е�����
	int columns = matrix[0].size();	//�е�����
	if(rows == 0 || columns == 0)
		return 0;

	vector<int> dp(columns, 0);

	int maxSide = 0;
	for(int i = 0; i < rows; i++) {
		//��dp[i][j]�������֮ǰ����һ����������dp[i - 1][j]����ֹ����
		int dp_pre = dp[0];
		for (int j = 0; j < columns; j++) {
			int temp = dp[j];
			if(matrix[i][j] == '1') {
				if(i == 0 || j == 0)
					dp[j] = 1;
				else
					//��ʱdp[j]�������dp[i-1][j]��dp_pre��dp[i-1][j-1]��dp[j-1]��dp[i][j-1]
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
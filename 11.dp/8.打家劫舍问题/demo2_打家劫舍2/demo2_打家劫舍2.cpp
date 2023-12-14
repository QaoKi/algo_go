#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


/*
	��Ŀ�� leetcode 213
		����һ��רҵ��С͵���ƻ�͵���ؽֵķ��ݡ�ÿ�䷿�ڶ�����һ�����ֽ�
		����ط����еķ��ݶ� Χ��һȦ ������ζ�ŵ�һ�����ݺ����һ�������ǽ����ŵġ�
		ͬʱ�����ڵķ���װ���໥��ͨ�ķ���ϵͳ������������ڵķ�����ͬһ���ϱ�С͵���룬ϵͳ���Զ����� ��

		����һ������ÿ�����ݴ�Ž��ķǸ��������飬������ �ڲ���������װ�õ������ ���ܹ�͵�Ե�����߽�
		ʾ�� 1��
			���룺[2,3,2]
			�����3
			���ͣ��㲻����͵�� 1 �ŷ��ݣ���� = 2����Ȼ��͵�� 3 �ŷ��ݣ���� = 2��, ��Ϊ���������ڵġ�

*/

/*
	1��dp
		��demo1_��ҽ��� ��ȣ���β�γ��˻���Ҳ����˵��͵�˵�һ�ң��Ͳ���͵���һ�ң�����͵�����һ�ң�
		�Ͳ���͵��һ���ˣ���ô����������������������ȡ�ϴ��ֵ��
	
	ʵ�֣�
		����������������
			�� nums������
				1��nums[1:len-1]����������һ��
				2��nums[0:len-2]�����������һ��
			����ֵ�����ֱ����demo1�ķ��������
*/

int dp(vector<int> &nums) {
	int n = nums.size();
	if(n == 0) return 0;
	if(n == 1) return nums[0];

	int no_0 = dp_help(nums, 1, n - 1);
	int no_end = dp_help(nums, 0, n - 2);

	return max(no_0, no_end);
}

int dp_help(vector<int> &nums, int start, int end) {
	if(start > end) return 0;

	//base case
	int dp_old = 0;
	int dp_new = nums[start];

	//ע���±�
	for (int i = start + 1; i <= end; i++) {
		int temp = dp_new;
		dp_new = max( dp_new, dp_old + nums[i]);
		dp_old = temp;
	}

	return dp_new;
}

int main()
{
	return 0;
}
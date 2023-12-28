#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>


using namespace std;

/*
	������ leetcode 912 ���Դ���
	���������������⣺
		������Ϊ  1,2,3,4,5,6  ���������״��ʱ�� ÿ��ѡ�����һ������Ϊnum����ô����num�������û����
		ÿ��һ��ֻ�ܸ㶨һ������ʱ�临�Ӷȱ�ΪO(n^2)
		������ţ�
		ÿ���������������ѡ��һ��ֵ�ŵ�����������Ϊnum�������漰�����ʣ�����������ʱ�临�Ӷȣ�O(n*logn)��

	��������ǹ�������õģ���Ϊʱ�临�Ӷȵĳ�����ȹ鲢������
*/

void sort(vector<int> &nums, int L, int R) {
	if (L >= R) return;

	//���ݵ�����״���ǲ��ɿصģ����ǿ��Բ��÷��������ҹ̶�������״��
	//1.����������������ȡֵ��������״���޹�
	//2.��ϣ
	//�����������������ȡһ��ֵ�ŵ���������
	int index = rand() % (R - L + 1) + L;
	int num = nums[index];
	int pl = L - 1; //ָ��С��numֵ��������һ��ֵ
	int pr = R + 1; //ָ�����numֵ����ĵ�һ��ֵ
	int curr = L;	//��ǰֵ���±꣬������ָ��

	//�������е�����С��num�ķŵ�С�����򣬴��ڵķŵ��������򣬵��ڷŵ��м�
	while (curr < pr) {
		if (nums[curr] < num)
			swap(nums[curr++], nums[++pl]);
		else if (nums[curr] == num)
			curr++;
		else
			//curr�Ȳ���1�����жϻ��������������ֵ
			swap(nums[curr], nums[--pr]);
	}
	//����ʱ�������L-pl��������С��num������pr-R�Ǵ���num��ֵ
	//�ټ�����֣�ֱ��ʣһ����
	sort(nums, L, pl);
	sort(nums, pr, R);
}

vector<int> sortArray(vector<int>& nums) {
	srand(time(0));
	sort(nums, 0, nums.size() - 1);
	return nums;
}

int main()
{
	return 0;
}

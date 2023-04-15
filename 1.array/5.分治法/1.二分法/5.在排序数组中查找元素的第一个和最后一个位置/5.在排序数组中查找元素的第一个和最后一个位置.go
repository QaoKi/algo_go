#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
	leetcode 34�����Ƶ���Ŀ��278
	����һ�������������е��������� nums����һ��Ŀ��ֵ target���ҳ�����Ŀ��ֵ�������еĿ�ʼλ�úͽ���λ�á�
	��������в�����Ŀ��ֵ target������ [-1, -1]��
*/

/*
	�������е�һ�����ڸ���Ԫ�ص�λ�� �� ���һ�����ڸ���Ԫ�ص�λ�ã�
	ע�⣬����λ�ò���һ���ң�Ҫ�ֿ��ҡ�
*/

vector<int> searchRange(vector<int>& nums, int target) {
	vector<int> ans(2, -1);
	//��һ��
	int left = 0, right = nums.size() - 1;
	while(left <= right) {
		int mid = left + (right - left) / 2;
		if(nums[mid] > target)
			right = mid - 1;
		else if(nums[mid] < target)
			left = mid + 1;
		else {
			if(mid == 0 || nums[mid - 1] != target) {
				ans[0] = mid;
				break;
			}
			else
				right = mid - 1;
		}
	}

	//���һ��
	left = 0, right = nums.size() - 1;
	while(left <= right) {
		int mid = left + (right - left) / 2;
		if(nums[mid] > target)
			right = mid - 1;
		else if(nums[mid] < target)
			left = mid + 1;
		else {
			if(mid == nums.size() - 1 || nums[mid + 1] != target) {
				ans[1] = mid;
				break;
			}				
			else
				left = mid + 1;
		}
	}

	return ans;
}

int main()
{
	return 0;
}
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
	leetcode 34，类似的题目：278
	给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。
	如果数组中不存在目标值 target，返回 [-1, -1]。
*/

/*
	找数组中第一个等于给定元素的位置 和 最后一个等于给定元素的位置，
	注意，两个位置不能一起找，要分开找。
*/

vector<int> searchRange(vector<int>& nums, int target) {
	vector<int> ans(2, -1);
	//第一个
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

	//最后一个
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
#include <stdio.h>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;
/*
	leetcode 581
	题目：
		给你一个整数数组 nums ，你需要找出一个 连续子数组，如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。
		请你找出符合题意的 最短 子数组，并输出它的长度。

		进阶：
			你可以设计一个时间复杂度为 O(n) 的解决方案吗？

		示例 1：
			输入：nums = [2,6,4,8,10,9,15]
			输出：5
			解释：你只需要对 [6, 4, 8, 10, 9] 进行升序排序，那么整个表都会变为升序排序。
		示例 2：
			输入：nums = [1,3,2,2,2]
			输出：4
		示例 3：
			输入：nums = [1,2,4,5,3]
			输出：3
*/

/*
	看到示例1，刚开始的思路是，	
		从前往后，找到第一个 nums[i] > nums[i+1] 的元素，
		再从后往前，找到第一个 nums[j-1] > nums[j] 的元素，
		要排序的区间就是 [i...j]
	但这种思路是不对的，当遇到示例2 或者示例3 就不行了。

	我们假设将数组分成三个部分，左中右。左段和右段都是升序数组，中段是需要我们重新排序的。
	我们的目标就是找到中段的左边界和右边界。

	需要明确的一点是中段虽然是乱序的。但是，中段的最小值，要大于左段的最大值，中段的最大值，要小于右段的最小值。
	根据这一点，我们找左右边界。
	找右边界：
		定义右边界的变量为 right，从前往后遍历，
		因为中段的最大值，要小于右段的最小值，我们定义一个变量 max，来记录中段的最大值。初始时 max = nums[0]，
			如果 nums[i] 大于等于 max，更新 max = nums[i]，
			如果 nums[i] 小于 max，说明 nums[i] 处于乱序序列中，让 right = i。
		比如 nums = [2,6,4,8,10,9,15]
			当遍历到 i = 2 时，nums[i] = 4，此时 max = 6，nums[i] < max，让 right = 2
			继续遍历
			当遍历到 i = 5 时，nums[i] = 9，此时 max = 10，nums[i] < max，让 right = 5

		因为中段的最大值，都要小于右端的最小值，如果当前值小于了 max，那当前值肯定不处于右段，
		处于乱序中，所以当前值也需要排序。

	找左边界：
		定义左边界的变量为 left，从后往前遍历，
		因为中段的最小值，要大于左段的最大值，我们定义一个变量 min，来记录中段的最小值。初始时 max = nums[len - 1]，
			如果 nums[i] 大于等于 min，更新 min = nums[i]，
			如果 nums[i] 大于 min，说明 nums[i] 处于乱序序列中，让 left = i。
		比如 nums = [1,3,2,2,2]
			当遍历到 i = 1 时，nums[i] = 3，此时 min = 2，nums[i] > min，让 left = 1

		和找右边界同样的道理，中段的最小值，都要大于左段的最大值，如果当前值大于了 min，那当前值肯定不处于左段，
		处于乱序中，所以当前值也需要排序。
	
	时间复杂度：O(n)
	空间复杂度：O(1)
*/
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
		int max = nums[0], min = nums[n - 1];
		int left = 0, right = 0;

		//右边界
		for (int i = 0; i < n; i++) {
			if (nums[i] < max)
				right = i;
			else 
				max = nums[i];
		}

		//左边界
		for (int i = n - 1; i >= 0; i--) {
			if (nums[i] > min)
				left = i;
			else 
				min = nums[i];	
		}

		//输出也要注意，如果 left 和 right 没改变，或者 right 变得 比 left 小了，返回 0
		return right - left <= 0 ? 0 : right - left + 1;
	}
};

int main()
{
}
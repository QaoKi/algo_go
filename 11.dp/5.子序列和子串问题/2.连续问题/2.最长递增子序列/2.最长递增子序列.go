package main

/*
   题目：leetcode 300
   给你一个整数数组 nums ，找到其中最长严格递增子序列的长度

   子序列是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。
   例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。

   示例：
       输入：nums = [10,9,2,5,3,7,101,18]
       输出：4
       解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。

*/

/*
   方法1，动态规划
   思路：
       和 最大子序和 一样定义dp[i]，不过要注意的是，本题求的是子序列，并不要求连续
       定义 dp[i]为以 nums[i] 结尾的最长上升子序列的长度，注意 nums[i] 必须被选取（作为子序列的最后一个元素）。
       base case:
           1，对于每个元素nums[i]，以nums[i]为结尾的子序列，最起码是含有nums[i]的，所以dp[i]最小为1
           2，当nums只有一个元素时，最长递增子序列就是它本身，所以dp[0] = 1
   实现：
       双重循环
           对于第一重循环 for(int i = 0; i < nums.size(); i++)
               每次循环确定一个 dp[i] 的值：以 nums[i] 结尾的最长上升子序列的长度
           第二重循环，for(int j = 0; j < i; j++)
               让 nums[i] 去和nums[j]比较，0 <= j < i，
               在所有nums[i] > nums[j]的值中（比前面的值大，保证是递增的），选一个最大的dp[j]，
                   加 1 后赋值给dp[i]，这样 dp[i] 就求出来了
       最后，返回dp数组中，最大的值

   时间复杂度：两层循环，O(n^2)
   空间复杂度：O(n)
*/

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func lengthOfLIS(nums []int) int {
	dp := make([]int, len(nums))
	// base case，当递增子序列值只有它自己时，长度为1
	for i := 0; i < len(nums); i++ {
		dp[i] = 1
	}

	//第一层循环，求dp[i]
	for i := 1; i < len(nums); i++ {
		//在所有 nums[i] > nums[j] 的值中，选一个最大的dp[j]，加1后赋值给dp[i]
		for j := 0; j < i; j++ {
			if nums[i] > nums[j] {
				dp[i] = max(dp[i], dp[j]+1)
			}
		}
	}

	ret := dp[0]
	for i := 1; i < len(dp); i++ {
		ret = max(ret, dp[i])
	}
	return ret
}

/*
   方法2，贪心 + 二分查找

   思路：
       考虑一个简单的贪心，如果我们要使上升子序列尽可能的长，则我们需要让序列上升得尽可能慢，
           因此我们希望每次在上升子序列最后加上的那个数尽可能的小。
       基于上面的贪心思路，我们维护一个数组 tail[i] ，表示长度为 i + 1 的 最长递增子序列 的 末尾元素 的最小值，
           初始时，tail[0] = nums[0]，
       遍历nums数组，将每个元素二分插入 tail 中。
           如果 tail 中元素都比它小，将它插到最后
           否则，用它覆盖掉第一个大于等于它的元素
       最终，tail 数组的长度，就是所需要的结果值。

   实现：
       比如当nums = [1, 4, 6]，元素都是递增的，那么 tail = [1, 4, 6]，长度为3
       当nums = [10, 9, 2, 5, 3, 7]，
           首先遍历10，tail = [10]，然后遍历9，覆盖掉第一个比它大的元素10，tail=[9]，
           同理遍历2时，tail=[2]，遍历5时，5比tail中所有元素值都大，插到最后，tail = [2, 5]
           遍历到3时，覆盖掉5，tail=[2, 3]，遍历到7时，插入到最后，tail=[2, 3, 7]。
           最终，nums的最长递增子序列长度为3

   时间复杂度：遍历一遍数组，每次二分插入，所以时间复杂度为O(NlogN)
   空间复杂度：O(N)
*/

// int greed(vector<int> nums) {
//     if(nums.empty())
//         return 0;

//     //结果值，tails数组的有效长度
//     int len = 0;
//     vector<int> tails(nums.size(), 0);

//     //对每个nums[i]二分查找，找到tails数组中第一个大于nums[i]的元素覆盖掉，如果没有，则插入到tails尾部
//     //二分查找所用的方法见 5.find/demo3_二分查找变形问题

//     for(int i = 0; i < nums.size(); i++){
//         int left = 0, right = len - 1;
//         while(left <= right) {
//             int mid = (left + right) >> 1;
//             if (tails[mid] >= nums[i])
// 			    right = mid - 1;
// 		    else
// 			    left = mid + 1;
//         }

//         //到这时，如果tails中存在大于等于nums[i]的元素，那么left就是第一个大于等于nums[i]的下标
//         //在tails中找到了第一个大于等于nums[i]的元素，替换掉
//         if(left < len && tails[left] >= nums[i])
//             tails[left] = nums[i];
//         else
//             //没找到，插入到tails数组的尾部，tails数组的有效长度加1
//             tails[len++] = nums[i];
//     }

//     return len;
// }

func main() {
}

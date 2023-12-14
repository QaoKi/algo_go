#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
    题目：leetcode 673
    给定一个未排序的整数数组，找到最长递增子序列的个数。

    示例 1:
        输入: [1,3,5,4,7]
        输出: 2
        解释: 有两个最长递增子序列，分别是 [1, 3, 4, 7] 和[1, 3, 5, 7]。

*/

/*
    在 最长递增子序列 题目中，我们定义 dp[i] 表示以 nums[i] 结尾的最长上升子序列的长度。
        对于每一个数 nums[i]，如果它前面的数 nums[j] (0 <= j < i) 比当前数 nums[i] 小，
            即如果 nums[i] > nums[j]，那么 nums[i] 相对于 nums[j] 就是递增的趋势，
            以 nums[j] 为结尾的最长递增子序列长度为 dp[j]，现在 nums[i] 相对于 nums[j] 又递增了一个长度。
            所以以 nums[i] 为结尾的最长递增子序列长度就变成了 dp[i] = dp[j] + 1;
        但是因为满足 nums[i] > nums[j] 的 nums[j] 不止一个 (0 <= j < i)，dp[i] 应该取这些 dp[j] + 1 的最大值，
        并且这些 dp[j] + 1 还会有相等的情况，一旦相等，说明以 nums[i] 为结尾的最长递增子序列个数就应该增加了。
    
    1，我们再定义一个数组，count[i] 表示以 nums[i] 结尾的最长递增子序列的个数。
        在 nums[i] > nums[j] 的大前提下：
            如果 dp[j] + 1 > dp[i]，说明最长递增子序列的长度增加了，让 dp[i] = dp[j] + 1，长度增加，
                数量不变 count[i] = count[j]
            如果 dp[j] + 1 == dp[i]，说明最长递增子序列的长度并没有增加，但是出现了长度一样的情况，
                数量增加 count[i] += count[j]（这里是 count[i] += count[j]，而不是 count[i] += 1）

    2，定义一个变量，记录最长递增子序列的最大长度 maxLength，
    3，遍历 dp 数组，如果 dp[i] 等于 maxLength，将对应的数量 count[i] 加到结果 res 中
*/

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;

        int iMax = 0;
        vector<int> dp(nums.size(), 1);
        //同样初始化为1
        vector<int> count(nums.size(), 1);
        
        //注意这里不能因为 dp[0] 已知就从 i=1 开始循环，
        //因为如果 nums.size() 等于 1，从 i=1 开始循环就不会进入到这个循环中，那么就不会改变 iMax 的值
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    if (dp[j] + 1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                        count[i] = count[j];
                    }
                    else if (dp[j] + 1 == dp[i]){
                        count[i] += count[j];     
                    }
                }             
            }
            iMax = max(iMax, dp[i]);
        }

        //现在 iMax 就是数组的 最长递增子序列 的长度，统计 dp 数组中等于该值的 count 数量
        int ans = 0;
        for (int i = 0; i < dp.size(); i++) {
            if (dp[i] == iMax)
                ans += count[i];
        }

        return ans;
    }
};

int main() {
    return 0;
}
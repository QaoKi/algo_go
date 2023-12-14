#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

/*
    题目：leetcode 53
    给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

    示例：
        输入: [-2,1,-3,4,-1,2,1,-5,4]
        输出: 6
        解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
*/

/*
    只有一个数组，数组中的值可能为负数，
    考虑定义：nums[0..i] 中的「最大的子数组和」为dp[i]，如果这样定义的话，整个nums数组的「最大子数组和」就是dp[n-1]。
        假设我们知道了dp[i]，如何推导出dp[i + 1]呢？
            实际上是推到不出来的的，因为子数组是需要连续的，按照我们当前dp数组定义，
            并不能保证nums[0..i]中的最大子数组与nums[i + 1]是相邻的，也就没办法推导出dp[i]和dp[i+1]的关系。
    重新定义dp数组的含义：
        以nums[i]为结尾的「最大子数组和」为dp[i]。（nums[i]作为子数组的最后一个元素）
        这种定义之下，想得到整个nums数组的「最大子数组和」，不能直接返回dp[n-1]，而需要遍历整个dp数组，找到最大值
            int res = INT_MIN;
            for (int i = 0; i < n; i++) {
                res = max(res, dp[i]);
            }
            return res;

        假设我们知道了dp[i-1]，如何推导出dp[i]呢？
            dp[i]有两种「选择」
                1，与前面的相邻子数组连接，形成一个和更大的子数组；
                2，不与前面的子数组连接，自成一派，自己作为一个子数组。
            选择结果更大的那个
                所以，dp[i] = max(nums[i], nums[i] + dp[i - 1]);
    base case:  
        当数组中只有一个元素，很明显结果值为 nums[0] 
*/

int dp(vector<int> nums) {
    int n = nums.size();
    if(n == 0) return 0;

    vector<int> dp(nums.size(), 0);
    //base case
    dp[0] = nums[0];
    
    for(int i = 1; i < n; i++) {
        dp[i] = max(nums[i], nums[i] + dp[i - 1]);
    }

    int res = INT_MIN;
    for (int i = 0; i < n; i++) {
        res = max(res, dp[i]);
    }

    return res;
}

int main() {
    return 0;
}
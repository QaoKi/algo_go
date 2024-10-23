#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

/*
    题目：leetcode 152
    给你一个整数数组 nums ，请你找出数组中乘积最大的连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

    示例：
        输入: [2,3,-2,4]
        输出: 6
        解释: 子数组 [2,3] 有最大乘积 6。
*/

/*
    和 最大子序和 题型类似，只不过求的是乘积
    定义dp数组为：
        以nums[i]为结尾的「最大连续子数组乘积」为dp[i]。（nums[i]作为子数组的最后一个元素）

    如何求状态转移方程？
        像 最大子序和 一样，对于 nums[i]，有两种选择，
            1，要么与前面的相邻子数组连接，形成一个更大的子数组；
            2，要么不与前面的子数组连接，自成一派，自己作为一个子数组。
        所以 dp[i] = max( nums[i], nums[i] * dp[i - 1] );
    但是上面的方程是有问题的，并不满足「最优子结构」
        比如 nums = [5,6,−2,4,−3]，根据上面的方程，求出 dp = [5,30,-2,4,-3]。
        但是很明显，-3 与 -2 相乘，能够负负得正，所以dp[4]不应该等于-3，而应该等于 5 * 6 * -2 * 4 * -3。
        所以我们得到了一个结论：当前位置的最优解未必是由前一个位置的最优解转移得到的。

    根据正负性进行分类讨论：
        1，当前位置如果是一个负数的话，那么我们希望以它前一个位置结尾的某个段的积也是个负数，这样就可以负负得正，
            并且我们希望这个积尽可能「负得更多」，即尽可能小。
        2，如果当前位置是一个正数的话，我们更希望以它前一个位置结尾的某个段的积也是个正数，并且希望它尽可能地大。
    再定义一个数组 dp_min：
        表示以nums[i]为结尾的「最小连续子数组乘积」dp_min[i]（nums[i]作为子数组的最后一个元素）
    再求状态转移方程：
        对于nums[i]，我们也不再去判断是正还是负，直接让 nums[i]和 dp_max[i-1]还有dp_min[i-1] 相乘，
        dp_max[i]从 nums[i]、dp_max[i-1]*nums[i]、dp_min[i-1]*nums[i] 三者中取最大的那个。
        dp_min[i]从三者中取最小的那个。
        所以，
            dp_max[i] = max(nums[i], max(dp_max[i - 1] * nums[i], dp_min[i - 1] * nums[i]));
            dp_min[i] = min(nums[i], min(dp_max[i - 1] * nums[i], dp_min[i - 1] * nums[i]));

    base case:  
        当数组中只有一个元素，很明显结果值为 nums[0] 
*/

int dp(vector<int> nums) {
    int n = nums.size();
    if(n == 0) return 0;

    vector<int> dp_max(nums.size(), 0);
    vector<int> dp_min(nums.size(), 0);
    //base case
    dp_max[0] = nums[0];
    dp_min[0] = nums[0];
    
    for(int i = 1; i < n; i++) {
        dp_max[i] = max(nums[i], max(dp_max[i - 1] * nums[i], dp_min[i - 1] * nums[i]));
        dp_min[i] = min(nums[i], min(dp_max[i - 1] * nums[i], dp_min[i - 1] * nums[i]));
    }

    //同样，从dp_max中取最大的那个值
    int res = INT_MIN;
    for (int i = 0; i < n; i++) {
        res = max(res, dp_max[i]);
    }

    return res;
}

int main() {
    return 0;
}
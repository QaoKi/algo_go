#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
    题目：leetcode 122
        给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
        设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。
        注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

        示例：
            输入: [7,1,5,3,6,4]
            输出: 7
            解释：在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
                    随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6-3 = 3 。
*/

/*
    1，dp
        k为正无穷，则 k 和 k - 1 可以看成是相同的。根据demo0的状态转移方程
            dp[i][k][0] = max( dp[i-1][k][0], dp[i-1][k][1] + prices[i-1])
            dp[i][k][1] = max( dp[i-1][k][1], dp[i-1][k-1][0] - prices[i-1])
        把k和k-1看出一样的。
            dp[i][k][1] = max( dp[i-1][k][1], dp[i-1][k][0] -prices[i-1])
        发现k都是相同的，k已经不是对结果产生影响的【状态】了，去掉
        最终
            dp[i][0] = max( dp[i-1][0], dp[i-1][1] + prices[i-1])
            dp[i][1] = max( dp[i-1][1], dp[i-1][0] - prices[i-1])
*/

int dp(vector<int> &prices) {
    int n = prices.size();
    if(n == 0) return 0;

    vector<vector<int>> dp(n + 1, vector<int>(2, 0));
    //base case
    for(int i = 0; i <= n; i++) {
        dp[i][0] = 0;
        dp[i][1] = INT_MIN;
    }

    for (int i = 1; i <= n; i++) {
        dp[i][0] = max( dp[i-1][0], dp[i-1][1] + prices[i-1]);
        dp[i][1] = max( dp[i-1][1], dp[i-1][0] - prices[i - 1]);
    }

    return dp[n][0];
}

/*
    2，dp状态压缩
        发现，第n行数据，只和第n-1行数据有关，并且每一行数据只有两个，所以用两个变量，保存上一行数据。
*/

int dp_plus(vector<int> &prices) {
    int n = prices.size();
    if(n == 0) return 0;
    //base case
    // dp[i][0] = 0
    int dp_0 = 0;
    // dp[i][1] = INT_MIN
    int dp_1 = INT_MIN;

    //这里i就从0开始取了，prices数组的下标也要改一下

    //要注意的是，在求dp_1的时候，需要使用上一行的 dp_0，
    //而求dp_1的时候，dp_0已经被覆盖成当前行的数据了，所以用一个辅助变量存上一行的 dp_0
    for (int i = 0; i < n; i++) {
        int dp_0_pre = dp_0;
        dp_0 = max( dp_0, dp_1 + prices[i]);
        dp_1 = max( dp_1, dp_0_pre - prices[i]);
    }

    return dp_0;
}

/*
    简单的思路：
        因为交易次数不受限制，所以只要今天的价格，比昨天高，昨天就能买，今天就能卖
*/

int easy(vector<int> &prices) {
    int n = prices.size();
    if(n == 0) return 0;
    
    int ans = 0;
    for(int i = 1; i < n; i++) {
        //比昨天高，就能赚到
        if(prices[i] > prices[i-1])
            ans += prices[i] - prices[i - 1];
    }

    return ans;
}


int main() {
    return 0;
}
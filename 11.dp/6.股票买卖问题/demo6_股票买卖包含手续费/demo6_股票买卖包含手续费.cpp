#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
    题目：leetcode 714
        给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。非负整数 fee 代表了交易股票的手续费用。
        你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。
        注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。

        示例：
            输入: prices = [1, 3, 2, 8, 4, 9], fee = 2
            输出: 8
            解释：能够达到的最大利润:  
                在此处买入 prices[0] = 1
                在此处卖出 prices[3] = 8
                在此处买入 prices[4] = 4
                在此处卖出 prices[5] = 9
                总利润: ((8 - 1) - 2) + ((9 - 4) - 2) = 8.
*/

/*
    k为无数次，那么和demo2类似，每次买入的时候需要付手续费，那么只需要利润减去手续费即可
    状态转移方程为：
        dp[i][0] = max( dp[i-1][0], dp[i-1][1] + prices[i-1])
        dp[i][1] = max( dp[i-1][1], dp[i-1][0] - prices[i-1] - fee)
*/

int dp(vector<int> &prices, int fee) {
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
        dp[i][1] = max( dp[i-1][1], dp[i-1][0] - prices[i - 1] - fee);
    }

    return dp[n][0];
}

int main() {
    return 0;
}
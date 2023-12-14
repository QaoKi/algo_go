#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

/*
    题目：leetcode 188
        给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
        设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。
        注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

        示例：
            输入：k = 2, prices = [2,4,1]
            输出：2
            解释：在第 1 天 (股票价格 = 2) 的时候买入，在第 2 天 (股票价格 = 4) 的时候卖出，
                    这笔交易所能获得利润 = 4-2 = 2 。
*/

/*
    1，dp
        k为给定的整数，根据demo0的状态转移方程
            dp[i][k][0] = max( dp[i-1][k][0], dp[i-1][k][1] + prices[i-1])
            dp[i][k][1] = max( dp[i-1][k][1], dp[i-1][k-1][0] - prices[i-1])

        下面是之前题目的dp解法
                for (int i = 1; i <= n; i++) {
                    dp[i][0] = max( dp[i-1][0], dp[i-1][1] + prices[i-1]);
                    dp[i][1] = max(dp[i - 1][1], -prices[i - 1]);
                }

        之前的题目，只遍历了天数，那是因为之前的题目中，k不再是影响因素，
            而手中是否持有股票，只有0和1两个值，把这两个值都列出来，也就省去了for循环的过程，
            但实质上，都列出来，也是穷举的过程
        本题有三个【状态】，除去可以穷举的手中是否持有股票，还需要用两个for循环把其他两个状态遍历一遍
            
            
*/

int dp(vector<int> &prices, int k) {
    int n = prices.size();
    if(n == 0) return 0;

    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(k + 1, vector<int>(2, 0)));
    //base case
    for(int i = 0; i <= n; i++) {
        dp[i][0][0] = 0;
        dp[i][0][1] = INT_MIN;
    }

    for(int i = 0; i <= k; i++) {
        dp[0][i][0] = 0;
        dp[0][i][1] = INT_MIN;
    }

    //遍历天数和k，将手里是否有股票列出来
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i - 1]);
            dp[i][j][1] = max(dp[i-1][j][1], dp[i-1][j-1][0] - prices[i - 1]);
        }       
    }

    return dp[n][k][0];
}

/*
    2，dp优化，在上面的题解中，k可以是任意整数，但如果k太大，是否就可以说k等于无数次？
        计算当k大于等于多少的时候，可以看到能够买卖无数次
            一次交易由买入和卖出构成，至少需要两天。所以说有效的限制次数 k 应该不超过 n/2，
            如果超过，就没有约束作用了，所以当 k >= n/2 时， k = INT_MAX。
        当k变成无数次，解法就等于demo2
*/

int dp_plus(vector<int> &prices, int k) {
    int n = prices.size();
    if(n == 0) return 0;
    
    if(k >= n / 2) {
        //走demo2的方法
        return dp_demo2(prices);
    }

   vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(k + 1, vector<int>(2, 0)));
    //base case
    for(int i = 0; i <= n; i++) {
        dp[i][0][0] = 0;
        dp[i][0][1] = INT_MIN;
    }

    for(int i = 0; i <= k; i++) {
        dp[0][i][0] = 0;
        dp[0][i][1] = INT_MIN;
    }

    //遍历天数和k，将手里是否有股票列出来
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i - 1]);
            dp[i][j][1] = max(dp[i-1][j][1], dp[i-1][j-1][0] - prices[i - 1]);
        }       
    }

    return dp[n][k][0];
}

int dp_demo2(vector<int> &prices) {
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


int main() {
    vector<int> prices = {3, 3, 5, 0, 0, 3, 1, 4};
    cout << "dp:  " << dp(prices, 2) << endl;
    return 0;
}